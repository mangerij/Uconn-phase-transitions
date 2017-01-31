#This is an input file for Hackathon 2015 problem 2.

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

[GlobalParams]
  well_width_factor = 1.414216
  alpha = 5
[]

[Variables]
  [./c]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = HackathonConcIC
      epsilon = 0.05
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

  [./n1]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = HackathonEtaIC
      epsilon = 0.1
      q1 = '0.01 0.017 0'
      q2 = '0.12 0.12 0'
      q3 = '0.047 0.0415 0'
      q4 = '0.032 0.005 0'
      h = 1.5
    [../]
  [../]

  [./n2]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = HackathonEtaIC
      epsilon = 0.1
      q1 = '0.02 0.027 0'
      q2 = '0.13 0.13 0'
      q3 = '0.048 0.0425 0'
      q4 = '0.033 0.006 0'
      h = 1.5
    [../]
  [../]

  [./n3]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = HackathonEtaIC
      epsilon = 0.1
      q1 = '0.03 0.037 0'
      q2 = '0.14 0.14 0'
      q3 = '0.049 0.0435 0'
      q4 = '0.034 0.007 0'
      h = 1.5
    [../]
  [../]

  [./n4]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = HackathonEtaIC
      epsilon = 0.1
      q1 = '0.04 0.047 0'
      q2 = '0.15 0.15 0'
      q3 = '0.05 0.0445 0'
      q4 = '0.035 0.008 0'
      h = 1.5
    [../]
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
    type = CHCoupledSplitHackathon
    variable = c
    w = mu
    kappa_name = kappa_CH
    OP_var_names = 'n1 n2 n3 n4'
  [../]

  [./ACBulk_n1]
    type = ACBulkPolyCoupledHackathon
    variable = n1
    OP_var_names = 'n1 n2 n3 n4'
    OP_number = 1
    coupled_CH_var = c
  [../]

  [./deta1dt]
    type = TimeDerivative
    variable = n1
  [../]

  [./ACinterface1]
    type = IsotropicACInterface
    variable = n1
  [../]
#####
  [./ACBulk_n2]
    type = ACBulkPolyCoupledHackathon
    variable = n2
    OP_var_names = 'n1 n2 n3 n4'
    OP_number = 2
    coupled_CH_var = c
  [../]

  [./deta2dt]
    type = TimeDerivative
    variable = n2
  [../]

  [./ACinterface2]
    type = IsotropicACInterface
    variable = n2
  [../]
#####
  [./ACBulk_n3]
    type = ACBulkPolyCoupledHackathon
    variable = n3
    OP_var_names = 'n1 n2 n3 n4'
    OP_number = 3
    coupled_CH_var = c
  [../]

  [./deta3dt]
    type = TimeDerivative
    variable = n3
  [../]

  [./ACinterface3]
    type = IsotropicACInterface
    variable = n3
  [../]
#####
  [./ACBulk_n4]
    type = ACBulkPolyCoupledHackathon
    variable = n4
    OP_var_names = 'n1 n2 n3 n4'
    OP_number = 4
    coupled_CH_var = c
  [../]

  [./deta4dt]
    type = TimeDerivative
    variable = n4
  [../]

  [./ACinterface4]
    type = IsotropicACInterface
    variable = n4
  [../]
[]

[AuxKernels]
   [./total_energy_calc]
      type = HackathonCHACEnergy
      variable = total_energy
      CH_var = c
      OP_var_names = 'n1 n2 n3 n4'
   [../]
[]

[Materials]
  [./generic]
    type = HackathonMaterial
    CH_mobility = 5
    AC_mobility = 5
    w = 1
    kappa_CH = 3
    kappa_AC = 3
    c_alpha = 0.3
    c_beta = 0.7
    concentration = c
  [../]
[]

[BCs]
  [./Periodic]
    [./all]
      variable = 'c mu n1 n2 n3 n4'
      auto_direction = 'x y'
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
    dt = 1e-2
    cutback_factor = 0.25
    growth_factor = 1.05
    optimal_iterations = 5
    iteration_window = 1
    linear_iteration_ratio = 100
  [../]

  num_steps = 5000
  dtmin = 1e-3

  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -sub_pc_type -sub_ksp_type -pc_asm_overlap'
  petsc_options_value = ' asm      lu           preonly       1'

  timestep_tolerance = 1e-5

  l_max_its = 100
  nl_abs_tol = 1e-11

[]

[Outputs]
  exodus = true
  interval = 10
  csv = true
  file_base = hackathon_p2_PBC_IA
  checkpoint = true
  sync_times = '1 5 10 20 50 100 200 500 1000 2000 3000 10000'

  [./console]
    type = Console
    perf_log = true
  [../]
[]
