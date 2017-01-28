/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/
#include "HackathonCHACEnergy.h"

template<>
InputParameters validParams<HackathonCHACEnergy>()
{
  InputParameters params = validParams<AuxKernel>();

  params.addRequiredCoupledVar("OP_var_names", "Array of coupled OP variable names");
  params.addRequiredCoupledVar("CH_var", "Cahn-Hilliard variable eg concentration");
  params.addParam<Real>("well_width_factor", 1, "factor to affect free energy well steepness");
  params.addParam<Real>("alpha", 1, "factor affecting order parameter barrier term");

  return params;
}

HackathonCHACEnergy::HackathonCHACEnergy(const InputParameters & parameters) :
    AuxKernel(parameters),
    _c_alpha(getMaterialProperty<Real>("c_alpha")),
    _c_beta(getMaterialProperty<Real>("c_beta")),
    _w(getMaterialProperty<Real>("w")),
    _kappa_CH(getMaterialProperty<Real>("kappa_CH")),
    _kappa_AC(getMaterialProperty<Real>("kappa_AC")),
    _factor(getParam<Real>("well_width_factor")),
    _alpha(getParam<Real>("alpha")),
    _n_OP_vars(coupledComponents("OP_var_names")),
    _c(coupledValue("CH_var")),
    _grad_c(coupledGradient("CH_var"))
{
  _OP.resize(_n_OP_vars);
  _grad_OP.resize(_n_OP_vars);

  for(unsigned int i=0; i< _n_OP_vars; i++)
  {
    _OP[i] = &coupledValue("OP_var_names", i);
    _grad_OP[i] = &coupledGradient("OP_var_names", i);
  }
}

Real
HackathonCHACEnergy::computeValue()
{
  Real f_alpha = _factor*_factor*(_c[_qp] - _c_alpha[_qp])*(_c[_qp] - _c_alpha[_qp]);
  Real f_beta =  _factor*_factor*(_c_beta[_qp] - _c[_qp])*(_c_beta[_qp] - _c[_qp]);

  Real g = computeDoubleWell();
  Real h = computeHeaviside();

  Real f_bulk = f_alpha*(1-h) + f_beta*(h) + _w[_qp]*g;

  Real f_grad = 0.5*(_kappa_CH[_qp]*_grad_c[_qp].size_sq());

  for (unsigned int i = 0; i< _n_OP_vars; i++)
  {
    f_grad += 0.5*(_kappa_AC[_qp]*( (*_grad_OP[i])[_qp].size_sq() ));
  }

  return f_bulk + f_grad;
}

Real
HackathonCHACEnergy::computeHeaviside()
{
  Real h = 0;

  for(unsigned int i=0; i<_n_OP_vars; i++)
  {
    Real OP = (*_OP[i])[_qp];
    h += OP*OP*OP*(6*OP*OP - 15*OP + 10);
  }

  return h;
}

Real
HackathonCHACEnergy::computeDoubleWell()
{
  Real g = 0;
  Real sum = 0;

  for (unsigned int i = 0; i<_n_OP_vars; i++)
  {
    Real OP = (*_OP[i])[_qp];

    g += OP*OP*(1-OP)*(1-OP);

    for (unsigned int j = i+1; j < _n_OP_vars; j++)
    {
      Real OP_j = (*_OP[j])[_qp];
      sum += (OP*OP)*(OP_j)*(OP_j);
    }
  }

  return g + _alpha*sum;
}
