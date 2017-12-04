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
  int problemNo;
  int solutionMethod;
  float stepSize;
  int numberofSteps;
  int verificationMode;
  int debugMode;

  grvy_input_fopen("./input.dat");

  if(grvy_input_fread_float("stepSize",&stepSize))
    printf("--> %-10s = %f\n","stepSize",stepSize);

  if(grvy_input_fread_int("numberofSteps",&numberofSteps))
    printf("--> %-10s = %i\n","numberofSteps",numberofSteps);

  if(grvy_input_fread_int("options/problemNo",&problemNo))
   {printf("simple ODE (1), charged particle motion (2)\n");
    printf("--> %-10s = %i\n","problemNo",problemNo);}

  if(grvy_input_fread_int("options/solutionMethod",&solutionMethod))
    {printf("explitict RK4 (1), implicit Euler (2), implicit RK2 (3)\n");
    printf("--> %-10s = %i\n","solutionMethod",solutionMethod);}

  if(grvy_input_fread_int("options/verificationMode",&verificationMode))
    {printf("verification mode off (0), on (1)\n");
    printf("--> %-10s = %i\n","verificationMode",verificationMode);}

  if(grvy_input_fread_int("options/debugMode",&debugMode))
    {printf("debug mode off (0), on (1)\n");
    printf("--> %-10s = %i\n","debugMode",debugMode);}

  grvy_log_setlevel(GRVY_INFO);
  grvy_input_fclose();

  /*charged particle motion with explicit RK4*/
  if (problemNo == 2 && solutionMethod == 1)
  {
    cpmrk4 (stepSize, numberofSteps);
  }

  /*charged particle motion with explicit RK(2,3)*/
  else if (problemNo == 2 && solutionMethod == 2)
  {
    cpmrk23 (stepSize, numberofSteps);
  }

  /*charged particle motion with explicit RK(8,9)*/
  else if (problemNo == 2 && solutionMethod == 3)
  {
    cpmrk89 (stepSize, numberofSteps);
  }

  /*simple ODE with explicit RK4*/
  else if (problemNo == 1 && solutionMethod == 1)
  {
    //The simple first order differential equation to solve is y'(x)=y(x) with the initial condition y(0)=1.
    soderk4 (stepSize, numberofSteps);
  }

  /*simple ODE with explicit RK(2,3)*/
  else if (problemNo == 1 && solutionMethod == 2)
  {
    soderk23 (stepSize, numberofSteps);
  }

  /*simple ODE with explicit RK(8,9)*/
  else if (problemNo == 1 && solutionMethod == 3)
  {
    soderk89 (stepSize, numberofSteps);
  }
}
