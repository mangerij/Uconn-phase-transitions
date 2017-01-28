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

#include "IsotropicACBulk.h"

template<>
InputParameters validParams<IsotropicACBulk>()
{
  InputParameters params = validParams<KernelValue>();
 
  return params;
}

IsotropicACBulk::IsotropicACBulk(const InputParameters & parameters) :
    KernelValue(parameters),
    _L(getMaterialProperty<Real>("AC_mobility"))
{
}

Real
IsotropicACBulk::precomputeQpResidual()
{
  Real dFdEta = computeDFDOP(Residual);

  return _L[_qp]*(dFdEta);
}

Real
IsotropicACBulk::precomputeQpJacobian()
{
  Real dFdEta = computeDFDOP(Jacobian);

  return _L[_qp]*(dFdEta);
}

Real
IsotropicACBulk::computeDFDOP(PFFunctionType type)
{
  return 0;
}
