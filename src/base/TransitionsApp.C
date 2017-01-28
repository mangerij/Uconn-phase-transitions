#include "TransitionsApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// Transitions Includes
//#include "BoundaryIntegralFMM.h"

template<>
InputParameters validParams<TransitionsApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

TransitionsApp::TransitionsApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  TransitionsApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  TransitionsApp::associateSyntax(_syntax, _action_factory);
}

TransitionsApp::~TransitionsApp()
{
}

// External entry point for dynamic application loading
extern "C" void TransitionsApp__registerApps() { TransitionsApp::registerApps(); }
void
TransitionsApp::registerApps()
{
  registerApp(TransitionsApp);
}

// External entry point for dynamic object registration
extern "C" void TransitionsApp__registerObjects(Factory & factory) { TransitionsApp::registerObjects(factory); }
void
TransitionsApp::registerObjects(Factory & factory)
{
  //registerUserObject(BoundaryIntegralFMM);
}

// External entry point for dynamic syntax association
extern "C" void TransitionsApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { TransitionsApp::associateSyntax(syntax, action_factory); }
void
TransitionsApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
