#This is an input file for Hackathon 2015 problem 2.

[Mesh]
  file = input/sphere.e
[]

[GlobalParams]
  block = 2
  well_width_factor = 1.414216
  alpha = 5
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

  [./n1]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      function = 0.1*(cos(1*(acos(z/100))-4)*cos(1.7*(atan2(y,x)))+cos(12*(acos(z/100)))*cos(12*(atan2(y,x)))+1.5*(cos(4.7*(acos(z/100))+4.15*(atan2(y,x)))*cos(3.2*acos(z/100)-0.5*atan2(y,x)))^2)^2
    [../]
  [../]

  [./n2]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      function = 0.1*(cos(2*(acos(z/100))-4)*cos(2.7*(atan2(y,x)))+cos(13*(acos(z/100)))*cos(13*(atan2(y,x)))+1.5*(cos(4.8*(acos(z/100))+4.25*(atan2(y,x)))*cos(3.3*acos(z/100)-0.6*atan2(y,x)))^2)^2
    [../]
  [../]

  [./n3]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      function = 0.1*(cos(3*(acos(z/100))-4)*cos(3.7*(atan2(y,x)))+cos(14*(acos(z/100)))*cos(14*(atan2(y,x)))+1.5*(cos(4.9*(acos(z/100))+4.35*(atan2(y,x)))*cos(3.4*acos(z/100)-0.7*atan2(y,x)))^2)^2
    [../]
  [../]

  [./n4]
    order = FIRST
    family = LAGRANGE
    [./InitialCondition]
      type = FunctionIC
      function = 0.1*(cos(4*(acos(z/100))-4)*cos(4.7*(atan2(y,x)))+cos(15*(acos(z/100)))*cos(15*(atan2(y,x)))+1.5*(cos(5.0*(acos(z/100))+4.45*(atan2(y,x)))*cos(3.5*acos(z/100)-0.8*atan2(y,x)))^2)^2
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

[Postprocessors]
  [./numDOFs]
    type = NumDOFs
  [../]
  [./TotalEnergy]
    type = ElementIntegralVariablePostprocessor
    variable = total_energy
  [../]
  [./mass]
    type = ElementIntegralVariablePostprocessor
    variable = c
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
      refine = 0.25 #0.5
      indicator = GJI_1
    [../]
    [./EFM_2]
      type = ErrorFractionMarker
      coarsen = 0.05
      refine = 0.5 #0.5
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
    dt = 1e-2
    percent_change = 0.05
  [../]

  num_steps = 5000
  dtmin = 1e-3

  solve_type = 'PJFNK'
  petsc_options_iname = '-pc_type -sub_pc_type -sub_ksp_type -pc_asm_overlap'
  petsc_options_value = ' asm      lu           preonly       1'

  timestep_tolerance = 1e-5

  l_max_its = 100
  nl_abs_tol = 1e-11

  timestep_tolerance = 1e-5

[]

[Outputs]
  interval = 10
  csv = true
  file_base = hackathon_p2_sphere_STA
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
