/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/
#include "CHSplitHackathon.h"

template<>
InputParameters validParams<CHSplitHackathon>()
{
  InputParameters params = validParams<SplitCHCRes>();

  return params;
}

CHSplitHackathon::CHSplitHackathon(const InputParameters & parameters) :
    SplitCHCRes(parameters),
    _c_alpha(getMaterialProperty<Real>("c_alpha")),
    _c_beta(getMaterialProperty<Real>("c_beta")),
    _w(getMaterialProperty<Real>("w"))
{
}

Real
CHSplitHackathon::computeDFDC(PFFunctionType type)
{
  switch (type)
  {
    case Residual:
      return _w[_qp]*2*((_u[_qp] - _c_alpha[_qp])*(_c_beta[_qp] - _u[_qp])
                      *(_c_alpha[_qp] + _c_beta[_qp] - 2*_u[_qp]) );

    case Jacobian:
      return _phi[_j][_qp]* ( _w[_qp]*2*(6*_u[_qp]*_u[_qp] + _c_alpha[_qp]*_c_alpha[_qp]
                                         + 4*_c_alpha[_qp]*_c_beta[_qp] + _c_beta[_qp]*_c_beta[_qp]
                                         - 6*_u[_qp]*(_c_alpha[_qp] + _c_beta[_qp]) ) );
  }

  mooseError("Invalid type passed in");
}

//Real
//CHSplitHackathon::computeDEDC(PFFunctionType type)
//{
//  return 0;
//}
