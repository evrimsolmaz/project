#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <grvy.h>
#include "funcsandjacs.h"

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
  FILE *f = fopen("output.dat", "w");
  double w = 5;
  double tao = 5;
  double constants[2] = {w, tao};
  gsl_odeiv2_system sys = { func, jac, 6, &constants }; 
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                 stepSize, 1e-8, 1e-8);
  double t = 0.0;
  double y[6] = { 0, 0, 0, 20, 0, 2 }; 
  int i, s;
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);
      if (s != GSL_SUCCESS)
        {
          printf ("error: driver returned %d\n", s);
          break;
        }
      fprintf (f,"%.5e %.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4], y[5]);
    }
  gsl_odeiv2_driver_free (d);
  return s;
  }

  /*charged particle motion with explicit RK(2,3)*/
  else if (problemNo == 2 && solutionMethod == 2)
  {
  FILE *f = fopen("output.dat", "w");
  double w = 5;
  double tao = 5;
  double constants[2] = {w, tao};
  gsl_odeiv2_system sys = { func, jac, 6, &constants };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2,
                                 stepSize, 1e-8, 1e-8);
  double t = 0.0;
  double y[6] = { 0, 0, 0, 20, 0, 2 };
  int i, s;
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);
      if (s != GSL_SUCCESS)
        {
          printf ("error: driver returned %d\n", s);
          break;
        }
      fprintf (f,"%.5e %.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4], y[5]);
    }
  gsl_odeiv2_driver_free (d);
  return s;
  }

  /*charged particle motion with explicit RK(8,9)*/
  else if (problemNo == 2 && solutionMethod == 3)
  {
  FILE *f = fopen("output.dat", "w");
  double w = 5;
  double tao = 5;
  double constants[2] = {w, tao};
  gsl_odeiv2_system sys = { func, jac, 6, &constants };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
                                 stepSize, 1e-8, 1e-8);
  double t = 0.0;
  double y[6] = { 0, 0, 0, 20, 0, 2 };
  int i, s;
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);
      if (s != GSL_SUCCESS)
        {
          printf ("error: driver returned %d\n", s);
          break;
        }
      fprintf (f,"%.5e %.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4], y[5]);
    }
  gsl_odeiv2_driver_free (d);
  return s;
  }

  /*simple ODE with explicit RK4*/
  else if (problemNo == 1 && solutionMethod == 1)
  {
  //The simple first order differential equation to solve is y'(x)=y(x) with the initial condition y(0)=1.
  double mu = 0; 
  double e; 
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu }; 
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                   stepSize, 1e-8, 1e-8);
  double t = 0.0;
  double y[1] = { 1.0 }; 
  int i, s;
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);
  
      if (s != GSL_SUCCESS)
       {
          printf ("error: driver returned %d\n", s);
          break;
        }
      e = exp(t); 
      printf ("%.5e %.5e exact:%.5e\n", t, y[0],e); 
    }
  gsl_odeiv2_driver_free (d);
  return s;
  }

  /*simple ODE with explicit RK(2,3)*/
  else if (problemNo == 1 && solutionMethod == 2)
  {
  double mu = 0;
  double e;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2,
                                   stepSize, 1e-8, 1e-8);
  double t = 0.0;
  double y[1] = { 1.0 };
  int i, s;
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);

      if (s != GSL_SUCCESS)
       {
          printf ("error: driver returned %d\n", s);
          break;
        }
      e = exp(t);
      printf ("%.5e %.5e exact:%.5e\n", t, y[0],e);
    }
  gsl_odeiv2_driver_free (d);
  return s;
  }

  /*simple ODE with explicit RK(8,9)*/
  else if (problemNo == 1 && solutionMethod == 3)
  {
  double mu = 0;
  double e;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
                                   stepSize, 1e-8, 1e-8);
  double t = 0.0;
  double y[1] = { 1.0 };
  int i, s;
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);

      if (s != GSL_SUCCESS)
       {
          printf ("error: driver returned %d\n", s);
          break;
        }
      e = exp(t);
      printf ("%.5e %.5e exact:%.5e\n", t, y[0],e);
    }
  gsl_odeiv2_driver_free (d);
  return s;
  }

}
