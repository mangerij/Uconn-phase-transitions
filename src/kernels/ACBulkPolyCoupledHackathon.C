/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/

#include "ACBulkPolyCoupledHackathon.h"

/**
 * ACBulkPolyCoupledHackathon couples the bulk Allen-Cahn equation term with order parameter eta
 * to the conserved field variable term from the Cahn-Hilliard equation.  It also couples
 * with multiple order parameters.  It uses the [XYZ] materials class.
 */

template<>
InputParameters validParams<ACBulkPolyCoupledHackathon>()
{
  InputParameters params = validParams<IsotropicACBulk>();

  params.addRequiredCoupledVar("coupled_CH_var", "The concentration to be coupled to the AC equation");
  params.addRequiredCoupledVar("OP_var_names", "Array of coupled OP variable names");
  params.addRequiredParam<int>("OP_number","# of the order parameter for this kernel, starting from 1");

  params.addParam<Real>("well_width_factor", 1, "factor to affect free energy well steepness");
  params.addParam<Real>("alpha", 1, "factor affecting order parameter barrier term");


  return params;
}

ACBulkPolyCoupledHackathon::ACBulkPolyCoupledHackathon(const InputParameters & parameters)
    : IsotropicACBulk(parameters),
      _n_OP_vars(coupledComponents("OP_var_names")),
      _OP_number(getParam<int>("OP_number")),
      _c(coupledValue("coupled_CH_var")),
      _c_var(coupled("coupled_CH_var")),
      _c_alpha(getMaterialProperty<Real>("c_alpha")),
      _c_beta(getMaterialProperty<Real>("c_beta")),
      _w(getMaterialProperty<Real>("w")),
      _factor(getParam<Real>("well_width_factor")),
      _alpha(getParam<Real>("alpha")),
      _dhdn(0),
      _d2hdn2(0),
      _dgdn(0),
      _d2gdn2(0)
{
  _OP.resize(_n_OP_vars);
  _OP_vars.resize(_n_OP_vars);

  for(unsigned int i=0; i< _n_OP_vars; i++)
  {
    //I think telling a human to index from 0 is not great for an input file,
    //so the if statement  is for when the coupled OP is actually the OP this kernel works on (not coupled)
    if(i == _OP_number-1)
    {
      _OP[i] = NULL;
      _OP_vars[i] = -1;
    }
    else
    {
      _OP[i] = &coupledValue("OP_var_names", i);
      _OP_vars[i] = coupled("OP_var_names", i);
    }
  }
}

Real
ACBulkPolyCoupledHackathon::computeDFDOP(PFFunctionType type)
{
  //compute f_alpha and f_beta
  Real f_alpha = _factor*_factor*(_c[_qp] - _c_alpha[_qp])*(_c[_qp] - _c_alpha[_qp]);
  Real f_beta = _factor*_factor*( _c_beta[_qp] - _c[_qp])*( _c_beta[_qp] - _c[_qp]);

  Real sum = 0;

  for(unsigned int i=0; i<_n_OP_vars; i++)
  {
    if(i != _OP_number-1)
    {
      sum += ((*_OP[i])[_qp])*((*_OP[i])[_qp]);
    }
  }

  Real dhdn = 30*_u[_qp]*_u[_qp]*(_u[_qp] - 1)*(_u[_qp] - 1);

  Real dgdn = 2*_u[_qp]*(1 - 3*_u[_qp] + 2*_u[_qp]*_u[_qp] + _alpha*sum);

  Real d2hdn2 = 60*_u[_qp]*(1 - 3*_u[_qp] + 2*_u[_qp]*_u[_qp]);

  Real d2gdn2 = 2*(1 - 6*_u[_qp] + 6*_u[_qp]*_u[_qp] + _alpha*sum);

  switch(type)
  {
  case Residual:
    return (f_beta -f_alpha)*dhdn + _w[_qp]*dgdn;

  case Jacobian:
    return _phi[_j][_qp]*( (f_beta - f_alpha)*d2hdn2 + _w[_qp]*d2gdn2);

  }
  mooseError("Invalid type passed in");
}

Real
ACBulkPolyCoupledHackathon::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _c_var)
  {
    Real f_alpha = 2*_factor*_factor*(_c[_qp] - _c_alpha[_qp]);
    Real f_beta = 2*_factor*_factor*( _c_beta[_qp] - _c[_qp]);

    Real dhdn = 30*_u[_qp]*_u[_qp]*(_u[_qp] - 1)*(_u[_qp] - 1);

    return _L[_qp]*_phi[_j][_qp]*_test[_i][_qp]*(dhdn*(f_beta - f_alpha));
  }

  for (unsigned int i=0; i<_n_OP_vars; i++)
  {
    if (jvar == _OP_vars[i])
    {
      return _L[_qp]*_phi[_j][_qp]*_test[_i][_qp]*(_alpha*2*_u[_qp]*2*(*_OP[i])[_qp]);
    }
  }
  return 0;

}