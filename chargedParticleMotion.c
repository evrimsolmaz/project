#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <grvy.h>
#include "funcsandjacs.h"
#include "probsandmethods.h"

int
main (void)
{
// Initializing the input variables that come from the input file input.dat:
  int problemNo;
  int solutionMethod;
  float stepSize;
  int numberofSteps;
  int verificationMode;
  int debugMode;
  float tolabs;
  float tolrel;

  grvy_input_fopen("./input.dat");

  if(grvy_input_fread_float("stepSize",&stepSize))
    printf("--> %-10s = %f\n","stepSize",stepSize);

  if(grvy_input_fread_float("tolabs",&tolabs))
    printf("--> %-10s = %f\n","tolabs",tolabs);

  if(grvy_input_fread_float("tolrel",&tolrel))
    printf("--> %-10s = %f\n","tolrel",tolrel);

  if(grvy_input_fread_int("numberofSteps",&numberofSteps))
    printf("--> %-10s = %i\n","numberofSteps",numberofSteps);

  if(grvy_input_fread_int("options/problemNo",&problemNo))
    printf("--> %-10s = %i\n","problemNo",problemNo);

  if(grvy_input_fread_int("options/solutionMethod",&solutionMethod))
    printf("--> %-10s = %i\n","solutionMethod",solutionMethod);

  if(grvy_input_fread_int("options/verificationMode",&verificationMode))
    printf("--> %-10s = %i\n","verificationMode",verificationMode);

  if(grvy_input_fread_int("options/debugMode",&debugMode))
    printf("--> %-10s = %i\n","debugMode",debugMode);

  grvy_log_setlevel(GRVY_INFO);
  grvy_input_fclose();

// Each problemNo & solutionMethod input combination invokes a different solver

  /*charged particle motion with GSL explicit RK4*/
  if (problemNo == 2 && solutionMethod == 1)
  {
    cpmrk4 (stepSize, numberofSteps, tolabs, tolrel, debugMode);
  }

  /*charged particle motion with GSL explicit RK(2,3)*/
  else if (problemNo == 2 && solutionMethod == 2)
  {
    cpmrk23 (stepSize, numberofSteps, tolabs, tolrel, debugMode);
  }

  /*charged particle motion with GSL explicit RK(8,9)*/
  else if (problemNo == 2 && solutionMethod == 3)
  {
    cpmrk89 (stepSize, numberofSteps, tolabs, tolrel, debugMode);
  }

  /*simple ODE with GSL explicit RK4*/
  else if (problemNo == 1 && solutionMethod == 1)
  {
    soderk4 (stepSize, numberofSteps, tolabs, tolrel, debugMode);
  }

  /*simple ODE with GSL explicit RK(2,3)*/
  else if (problemNo == 1 && solutionMethod == 2)
  {
    soderk23 (stepSize, numberofSteps, tolabs, tolrel, debugMode);
  }

  /*simple ODE with GSL explicit RK(8,9)*/
  else if (problemNo == 1 && solutionMethod == 3)
  {
    soderk89 (stepSize, numberofSteps, tolabs, tolrel, debugMode);
  }

// The analytical solution function of the charged particle motion equations (below) is only invoked if verification mode is on

  if (verificationMode == 1)
  {
    analyticalSolution (stepSize, numberofSteps, debugMode);
  }
}
