/******************************************************
 *
 *   Welcome to Hackathon!
 *
 *   CHiMaD (ANL/Northwestern University)
 *
 *   Developer: Andrea Jokisaari
 *
 *   3 February 2016
 *
 *****************************************************/

#include "IsotropicACInterface.h"

template<>
InputParameters validParams<IsotropicACInterface>()
{
  InputParameters params = validParams<KernelGrad>();

  return params;
}

IsotropicACInterface::IsotropicACInterface(const InputParameters & parameters) :
      KernelGrad(parameters),
      _L(getMaterialProperty<Real>("AC_mobility")),
      _kappa_AC(getMaterialProperty<Real>("kappa_AC"))
{
}

RealGradient
IsotropicACInterface::precomputeQpResidual()
{
  return _kappa_AC[_qp]*_L[_qp]*(_grad_u[_qp]);
}

RealGradient
IsotropicACInterface::precomputeQpJacobian()
{
  return _kappa_AC[_qp]*_L[_qp]*(_grad_phi[_j][_qp]);
}
