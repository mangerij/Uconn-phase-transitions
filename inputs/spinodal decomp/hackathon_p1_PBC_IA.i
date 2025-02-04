#This is an input file for Hackathon 2015 problem 1.

[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 25
  ny = 25
  xmin = 0
  xmax = 200
  ymin = 0
  ymax = 200

  elem_type = QUAD4
[]

[Variables]
  [./c]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = HackathonConcIC
      base_value = 0.5
      epsilon = 0.01
      q1 = '0.105 0.11 0'
      q2 = '0.13 0.087 0'
      q3 = '0.025 0.15 0'
      q4 = '0.07 0.02 0'
      constant = 0
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

[BCs]
  [./Periodic]
    [./all]
      variable = 'c mu'
      auto_direction = 'x y'
    [../]
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
  initial_steps = 3
  max_h_level = 3
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
[]


[Outputs]
  exodus = true
  interval = 10
  csv = true
  file_base = hackathon_p1_square_PBC_IA
  checkpoint = true
 sync_times = '1 5 10 20 50 100 200 500 1000 2000 3000 10000'


  [./console]
    type = Console
    perf_log = true
  [../]
[]
