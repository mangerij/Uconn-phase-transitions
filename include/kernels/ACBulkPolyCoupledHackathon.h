/*************************************************************************
*
*  Welcome to Hackathon!
*  Andrea M. Jokisaari
*
*  1 October 2015
*
*************************************************************************/
#ifndef ACBULKPOLYCOUPLEDHACKATHON_H
#define ACBULKPOLYCOUPLEDHACKATHON_H

#include "IsotropicACBulk.h"

// Forward Declaration
class ACBulkPolyCoupledHackathon;

template<>
InputParameters validParams<ACBulkPolyCoupledHackathon>();

/**
 * ACBulkPolyCoupledHackathon couples the bulk Allen-Cahn equation term with order parameter eta
 * to the conserved field variable term from the Cahn-Hilliard equation.  It also couples
 * with multiple order parameters.  It uses a new materials class I haven't coded yet.
 */


class ACBulkPolyCoupledHackathon : public IsotropicACBulk
{
public:
  ACBulkPolyCoupledHackathon(const InputParameters & parameters);

protected:
  virtual Real computeDFDOP(PFFunctionType type);
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  unsigned int _n_OP_vars;
  unsigned int _OP_number;

  const VariableValue & _c;
  unsigned int _c_var;

  const MaterialProperty<Real> & _c_alpha;
  const MaterialProperty<Real> & _c_beta;
  const MaterialProperty<Real> & _w;

  Real _factor;
  Real _alpha;

  std::vector<const VariableValue *> _OP;
  std::vector<unsigned int> _OP_vars;

  Real _dhdn;
  Real _d2hdn2;

  Real _dgdn;
  Real _d2gdn2;

private:

};


#endif //ACBULKPOLYCOUPLEDHACKATHON_H
