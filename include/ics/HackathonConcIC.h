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

#ifndef HACKATHONCONCIC_H
#define HACKATHONCONCIC_H

#include "InitialCondition.h"

// Forward Declarations
class HackathonConcIC;
namespace libMesh { class Point; }

template<>
InputParameters validParams<HackathonConcIC>();

class HackathonConcIC : public InitialCondition
{
public:
  HackathonConcIC(const InputParameters & parameters);
  virtual Real value(const Point & p);

protected:

private:
  Real _epsilon;
  Real _base_value;

  Point _q1;
  Point _q2;
  Point _q3;
  Point _q4;

  Real _k;
};

#endif //HACKATHONCONCIC_H
