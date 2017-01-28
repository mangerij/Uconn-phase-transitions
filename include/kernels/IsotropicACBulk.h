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

#ifndef ISOTROPICACBULK_H
#define ISOTROPICACBULK_H

#include "KernelValue.h"

//forward declarations
class IsotropicACBulk;

template<>
InputParameters validParams<IsotropicACBulk>();

class IsotropicACBulk : public KernelValue
{
public:
  IsotropicACBulk(const InputParameters & parameters);

protected:
  enum PFFunctionType
  {
    Jacobian,
    Residual
  };

  virtual Real precomputeQpResidual();
  virtual Real precomputeQpJacobian();
   virtual Real computeDFDOP(PFFunctionType type);

  const MaterialProperty<Real> & _L;

private:

};

#endif //ISOTROPICACBULK_H
