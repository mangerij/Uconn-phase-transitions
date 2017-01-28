/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/

#include "CHCoupledSplitHackathon.h"

/** CHCoupledSplitHackathon handles the conserved order parameter(probably concentration),
 * evolved using the Cahn-Hilliard equation.  It couples to multiple order
 * parameters from multiple Allen-Cahn equations.
 */


template<>
InputParameters validParams<CHCoupledSplitHackathon>()
{
  InputParameters params = validParams<SplitCHCRes>();

  params.addRequiredCoupledVar("OP_var_names", "Array of coupled OP variable names");
  params.addParam<Real>("well_width_factor", 1, "factor to affect free energy well steepness");

  return params;
}

CHCoupledSplitHackathon::CHCoupledSplitHackathon(const InputParameters & parameters):
    SplitCHCRes(parameters),
    _c_alpha(getMaterialProperty<Real>("c_alpha")),
    _c_beta(getMaterialProperty<Real>("c_beta")),
    _n_OP_variables(coupledComponents("OP_var_names")),
    _factor(getParam<Real>("well_width_factor"))
{
  _OP.resize(_n_OP_variables);
  _OP_vars.resize(_n_OP_variables);

  for(unsigned int i=0; i< _n_OP_variables; i++)
  {
    _OP[i] = &coupledValue("OP_var_names", i);
    _OP_vars[i] = coupled("OP_var_names", i);
  }
}

Real
CHCoupledSplitHackathon::computeDFDC(PFFunctionType type)
{
  Real h = computeHeaviside();

  Real f_alpha = 0;
  Real f_beta = 0;

  switch (type)
  {
  case Residual:
    f_alpha = 2*_factor*_factor*(_u[_qp] - _c_alpha[_qp]);
    f_beta = 2*_factor*_factor*(_u[_qp] - _c_beta[_qp]);

    return f_alpha*(1 - h) + f_beta*h;

  case Jacobian:
    f_alpha = 2*_factor*_factor;
    f_beta = 2*_factor*_factor;

    return _phi[_j][_qp]*(f_alpha*(1-h) + f_beta*h);
  }
  mooseError("invalid type passed in");
}

Real
CHCoupledSplitHackathon::computeHeaviside()
{

  Real h = 0;

  for(unsigned int i=0; i<_n_OP_variables; i++)
  {
    Real OP = (*_OP[i])[_qp];
    h += OP*OP*OP*(6*OP*OP - 15*OP + 10);
  }

  return h;
}

Real
CHCoupledSplitHackathon::computeDHeavisideDn(unsigned int i)
{
  Real OP = (*_OP[i])[_qp];

  return 30*OP*OP*(OP*OP - 2*OP + 1);

}

Real
CHCoupledSplitHackathon::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _w_var)
  {
    return -_phi[_j][_qp] * _test[_i][_qp];
  }

  for (unsigned int i=0; i<_n_OP_variables; i++)
  {
    if (jvar == _OP_vars[i])
    {
      Real dhdn = computeDHeavisideDn(i);

      Real f_alpha = 2*_factor*_factor*(_u[_qp] - _c_alpha[_qp]);
      Real f_beta = 2*_factor*_factor*(_u[_qp] - _c_beta[_qp]);

      return _test[_i][_qp]*_phi[_j][_qp]*(dhdn*(f_beta - f_alpha));
    }
  }

  return 0.0;
}
