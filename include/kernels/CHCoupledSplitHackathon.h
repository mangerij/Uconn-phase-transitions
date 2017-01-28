/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  1 October 2015
*
*************************************************************************/

#ifndef CHCOUPLEDSPLITHACKATHON_H
#define CHCOUPLEDSPLITHACKATHON_H

#include "SplitCHCRes.h"

class CHCoupledSplitHackathon;

template<>
InputParameters validParams<CHCoupledSplitHackathon>();

class CHCoupledSplitHackathon : public SplitCHCRes
{
public:
  CHCoupledSplitHackathon(const InputParameters & parameters);

protected:
  virtual Real computeDFDC(PFFunctionType type);
  virtual Real computeHeaviside();
  virtual Real computeDHeavisideDn(unsigned int i);
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  const MaterialProperty<Real> & _c_alpha;
  const MaterialProperty<Real> & _c_beta;

  unsigned int _n_OP_variables;
  std::vector<const VariableValue *> _OP;
  std::vector<unsigned int> _OP_vars;

  Real _factor;

};

#endif //CHCOUPLEDSPLITHACKATHON_H
