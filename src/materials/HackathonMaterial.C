/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/

#include "HackathonMaterial.h"

template<>
InputParameters validParams<HackathonMaterial>()
{
  InputParameters params = validParams<Material>();

  params.addRequiredParam<Real>("CH_mobility", "isotropic Cahn-Hilliard kinetic coefficient");
  params.addRequiredParam<Real>("kappa_CH", "gradient energy coefficient for c");
  params.addParam<Real>("AC_mobility", 0, "isotropic Allen-Cahn kinetic coefficient");
  params.addParam<Real>("kappa_AC", 0, "gradient energy coefficient for eta");

  params.addRequiredCoupledVar("concentration", "conserved variable");
  params.addRequiredParam<Real>("c_alpha", "atomic fraction of alpha phase well");
  params.addRequiredParam<Real>("c_beta", "atomic fraction of beta phase well");
  params.addRequiredParam<Real>("w", "parameter controlling height of double well barrier");

  return params;
}

HackathonMaterial::HackathonMaterial(const InputParameters & parameters) :
    Material(parameters),
    _M(declareProperty<Real>("CH_mobility")),
    _kappa_CH(declareProperty<Real>("kappa_CH")),
    _L(declareProperty<Real>("AC_mobility")),
    _kappa_AC(declareProperty<Real>("kappa_AC")),

    _w(declareProperty<Real>("w")),
    _c_alpha(declareProperty<Real>("c_alpha")),
    _c_beta(declareProperty<Real>("c_beta")),

     _fbulk(declareProperty<Real>("f_bulk")),
    _dfbulkdc(declareProperty<Real>("df_bulk_dOP")),
    _M_param(getParam<Real>("CH_mobility")),
    _kappa_CH_param(getParam<Real>("kappa_CH")),
    _L_param(getParam<Real>("AC_mobility")),
    _kappa_AC_param(getParam<Real>("kappa_AC")),

    _w_param(getParam<Real>("w")),
    _c_alpha_param(getParam<Real>("c_alpha")),
    _c_beta_param(getParam<Real>("c_beta")),
    _c(coupledValue("concentration"))
{
}

void
HackathonMaterial::computeQpProperties()
{
  _M[_qp] = _M_param;
  _kappa_CH[_qp] = _kappa_CH_param;

  _L[_qp] = _L_param;
  _kappa_AC[_qp] = _kappa_AC_param;

  _w[_qp] = _w_param;
  _c_alpha[_qp] = _c_alpha_param;
  _c_beta[_qp] = _c_beta_param;



  //chemical free energy
  _fbulk[_qp] = _w_param*( (_c[_qp] - _c_alpha_param)*(_c[_qp] - _c_alpha_param)*(_c_beta_param -_c[_qp])*(_c_beta_param -_c[_qp]));

  _dfbulkdc[_qp] = 2*_w_param*((_c[_qp] - _c_alpha_param)*(_c_beta_param -_c[_qp])*(_c_alpha_param + _c_beta_param -2*_c[_qp]));
}
