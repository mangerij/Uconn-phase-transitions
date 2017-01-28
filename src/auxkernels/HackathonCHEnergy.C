/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/
#include "HackathonCHEnergy.h"

template<>
InputParameters validParams<HackathonCHEnergy>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("CH_var", "Cahn-Hilliard variable eg concentration");

  return params;
}

HackathonCHEnergy::HackathonCHEnergy(const InputParameters & parameters) :
    AuxKernel(parameters),
    _c_alpha(getMaterialProperty<Real>("c_alpha")),
    _c_beta(getMaterialProperty<Real>("c_beta")),
    _w(getMaterialProperty<Real>("w")),
    _kappa_CH(getMaterialProperty<Real>("kappa_CH")),
    _c(coupledValue("CH_var")),
    _grad_c(coupledGradient("CH_var"))
{
}

Real
HackathonCHEnergy::computeValue()
{
  Real f_alpha = (_c[_qp] - _c_alpha[_qp])*(_c[_qp] - _c_alpha[_qp]);
  Real f_beta = (_c_beta[_qp] - _c[_qp])*(_c_beta[_qp] - _c[_qp]);

  Real f_bulk = f_alpha*f_beta*_w[_qp];

  Real f_grad = 0.5*(_kappa_CH[_qp]*_grad_c[_qp].size_sq());

  return f_bulk + f_grad;
}
