#This is an input file for Hackathon 2015 problem 1.

[Mesh]
  file = input/sphere.e
[]

[Variables]
  [./c]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      function = 0.5+0.05*(cos(8*(acos(z/100)))*cos(15*atan2(y,x))+(cos(12*(acos(z/100)))*cos(10*(atan2(y,x))))^2+(cos(2.5*(acos(z/100))-1.5*(atan2(y,x)))*cos(7*(acos(z/100))-2*(atan2(y,x)))))
    [../]
  [../]

  [./mu]
    order = FIRST
    family = LAGRANGE
  [../]
[]

[AuxVariables]
  [./total_energy]
    order = CONSTANT
    family = MONOMIAL
  [../]
[]

[Preconditioning]
  [./SMP]
    type = SMP
    full = true
  [../]
[]

[Kernels]
  [./mu_residual]
    type = SplitCHWRes
    variable = mu
    mob_name = CH_mobility
  [../]

  [./dcdt]
    type = CoupledTimeDerivative
    variable = mu
    v = c
  [../]

  [./c_residual]
    type = CHSplitHackathon
    variable = c
    w = mu
    kappa_name = kappa_CH
  [../]
[]

[AuxKernels]
   [./total_energy_calc]
      type = HackathonCHEnergy
      variable = total_energy
      CH_var = c
   [../]
[]

[Materials]
  [./generic]
    type = HackathonMaterial
    CH_mobility = 5
    w = 5
    kappa_CH = 2
    c_alpha = 0.3
    c_beta = 0.7
    concentration = c
  [../]
[]

[Postprocessors]
  [./numDOFs]
    type = NumDOFs
  [../]
  [./TotalEnergy]
    type = ElementIntegralVariablePostprocessor
    variable = total_energy
  [../]
  [./dt]
    type = TimestepSize
  [../]
  [./NL_iter]
    type = NumNonlinearIterations
  [../]
  [./L_evals]
    type = NumResidualEvaluations
  [../]
  [./nodes]
    type = NumNodes
  [../]

[]

[Adaptivity]
  initial_steps = 2
  max_h_level = 2
  marker = combo
  [./Markers]
    [./EFM_1]
      type = ErrorFractionMarker
      coarsen = 0.02
      refine = 0.25
      indicator = GJI_1
    [../]
    [./EFM_2]
      type = ErrorFractionMarker
      coarsen = 0.05
      refine = 0.5
      indicator = GJI_2
    [../]
    [./combo]
      type = ComboMarker
      markers = 'EFM_1 EFM_2'
    [../]
  [../]

  [./Indicators]
    [./GJI_1]
     type = GradientJumpIndicator
     variable = c
    [../]
    [./GJI_2]
     type = GradientJumpIndicator
     variable = mu
    [../]
  [../]
[]

[Executioner]
  type = Transient

  [./TimeStepper]
    type = IterationAdaptiveDT
    dt = 1e-1
    cutback_factor = 0.25
    growth_factor = 1.05
    optimal_iterations = 5
    iteration_window = 1
    linear_iteration_ratio = 100
  [../]
  
  num_steps = 5000
  dtmin = 1e-2
  
  timestep_tolerance = 1e-4


  solve_type = 'NEWTON'

  l_max_its = 100
  nl_abs_tol = 1e-11
  nl_max_its = 20

[]

[Outputs]
  interval = 10
  csv = true
  file_base = hackathon_p1_sphere_IA2
  checkpoint = true
  sync_times = '1 5 10 20 50 100 200 500 1000 2000 3000 10000'
  
  [./console]
    type = Console
    perf_log = true
  [../]

  [./my_exodus]
    type = Exodus
    use_problem_dimension = false
  [../]
[]