/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/

#ifndef CHSPLITHACKATHON_H
#define CHSPLITHACKATHON_H

#include "SplitCHCRes.h"

//forward declarations
class CHSplitHackathon;

template<>
InputParameters validParams<CHSplitHackathon>();

class CHSplitHackathon : public SplitCHCRes
{
public:
  CHSplitHackathon(const InputParameters & parameters);

protected:
  virtual Real computeDFDC(PFFunctionType type);
//virtual Real computeDEDC(PFFunctionType type);

  const MaterialProperty<Real> & _c_alpha;
  const MaterialProperty<Real> & _c_beta;
  const MaterialProperty<Real> & _w;

private:

};

#endif //CHSPLITHACKATHON_H
