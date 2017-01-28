/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/
#ifndef HACKATHONCHACENERGY_H
#define HACKATHONCHACENERGY_H

#include "AuxKernel.h"

//Forward Declarations
class HackathonCHACEnergy;

template<>
InputParameters validParams<HackathonCHACEnergy>();

class HackathonCHACEnergy : public AuxKernel
{
public:
  HackathonCHACEnergy(const InputParameters & parameters);

protected:
  virtual Real computeValue();
  virtual Real computeHeaviside();
  virtual Real computeDoubleWell();

private:
  const MaterialProperty<Real> & _c_alpha;
  const MaterialProperty<Real> & _c_beta;
  const MaterialProperty<Real> & _w;
  const MaterialProperty<Real> & _kappa_CH;
  const MaterialProperty<Real> & _kappa_AC;

  Real _factor;
  Real _alpha;


  unsigned int _n_OP_vars;
  std::vector<const VariableValue *> _OP;
  std::vector<const VariableGradient *> _grad_OP;
  const VariableValue & _c;
  const VariableGradient & _grad_c;
};

#endif //TOTALHACKATHONFREEENERGY_H
