/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/
#ifndef HACKATHONCHENERGY_H
#define HACKATHONCHENERGY_H

#include "AuxKernel.h"

//Forward Declarations
class HackathonCHEnergy;

template<>
InputParameters validParams<HackathonCHEnergy>();

class HackathonCHEnergy : public AuxKernel
{
public:
  HackathonCHEnergy(const InputParameters & parameters);

protected:
  virtual Real computeValue();

private:
  const MaterialProperty<Real> & _c_alpha;
  const MaterialProperty<Real> & _c_beta;
  const MaterialProperty<Real> & _w;
  const MaterialProperty<Real> & _kappa_CH;

  const VariableValue & _c;
  const VariableGradient & _grad_c;

};

#endif //HACKATHONCHENERGY_H
