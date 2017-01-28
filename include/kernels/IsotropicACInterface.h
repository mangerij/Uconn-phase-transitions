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

#ifndef ISOTROPICACINTERFACE_H
#define ISOTROPICACINTERFACE_H

#include "KernelGrad.h"

class IsotropicACInterface;

template<>
InputParameters validParams<IsotropicACInterface>();

class IsotropicACInterface : public KernelGrad
{
public:
  IsotropicACInterface(const InputParameters & parameters);

  virtual RealGradient precomputeQpResidual();
  virtual RealGradient precomputeQpJacobian();

protected:

  const MaterialProperty<Real> & _L;
  const MaterialProperty<Real> & _kappa_AC;

private:

};



#endif //ISOTROPICACINTERFACE_H
