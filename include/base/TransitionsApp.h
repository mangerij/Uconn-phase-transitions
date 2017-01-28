#ifndef TRANSITIONSAPP_H
#define TRANSITIONSAPP_H

#include "MooseApp.h"

class TransitionsApp;

template<>
InputParameters validParams<TransitionsApp>();

class TransitionsApp : public MooseApp
{
public:
  TransitionsApp(InputParameters parameters);
  virtual ~TransitionsApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* TRANSITIONSAPP_H */
