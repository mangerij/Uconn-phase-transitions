/******************************************************
 *
 *   Welcome to Hackathon!
 *
 *   CHiMaD (ANL/Northwestern University)
 *
 *   Developer: Andrea Jokisaari
 *
 *   19 February 2016
 *
 *****************************************************/

#ifndef HACKATHONETAIC_H
#define HACKATHONETAIC_H

#include "InitialCondition.h"

// Forward Declarations
class HackathonEtaIC;
namespace libMesh { class Point; }

template<>
InputParameters validParams<HackathonEtaIC>();

class HackathonEtaIC : public InitialCondition
{
public:
  HackathonEtaIC(const InputParameters & parameters);
  virtual Real value(const Point & p);

protected:

private:
  Real _epsilon;
  Real _base_value;

  Point _q1;
  Point _q2;
  Point _q3;
  Point _q4;

  Real _h;

};

#endif //HACKATHONETAIC_H
