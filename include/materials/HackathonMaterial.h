/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  22 February 2016
*
*************************************************************************/

#ifndef HACKATHONMATERIAL_H
#define HACKATHONMATERIAL_H

#include "Material.h"

//forward declarations
class HackathonMaterial;

template<>
InputParameters validParams<HackathonMaterial>();

class HackathonMaterial : public Material
{
public:
  HackathonMaterial(const InputParameters & parameters);

protected:
  virtual void computeQpProperties();

  MaterialProperty<Real> & _M;
  MaterialProperty<Real> & _kappa_CH;
  MaterialProperty<Real> & _L;
  MaterialProperty<Real> & _kappa_AC;

  MaterialProperty<Real> & _w;
  MaterialProperty<Real> & _c_alpha;
  MaterialProperty<Real> & _c_beta;

  MaterialProperty<Real> & _fbulk;
  MaterialProperty<Real> & _dfbulkdc;

  //these store the values from the input file.
  Real _M_param;
  Real _kappa_CH_param;

  Real _L_param;
  Real _kappa_AC_param;

  Real _w_param;
  Real _c_alpha_param;
  Real _c_beta_param;

  const VariableValue & _c;


private:

};

#endif //HACKATHONCHMATERIAL_H
