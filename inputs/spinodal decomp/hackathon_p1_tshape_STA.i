#This is an input file for Hackathon 2015 problem 1.

[Mesh]
  file = input/T-shape.e
[]

[Variables]
  [./c]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = HackathonConcIC
      epsilon = 0.01
      base_value = 0.5
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
  initial_steps = 1
  max_h_level = 1
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
    type = SolutionTimeAdaptiveDT
    dt = 1e-1
    percent_change = 0.05
  [../]

  num_steps = 10000
  timestep_tolerance = 1e-5

  solve_type = 'NEWTON'
  
  l_max_its = 100
  nl_abs_tol = 1e-11
 
[]


[Outputs]
  interval = 10
  csv = true
  file_base = hackathon_p1_tshape_STA2
  checkpoint = true
  sync_times = '1 5 10 20 50 100 200 500 1000 2000 3000 10000'

  [./exodus]
    type = Exodus
  [../]

  [./console]
    type = Console
    perf_log = true
  [../]
[]
