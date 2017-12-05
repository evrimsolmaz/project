#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <grvy.h>
#include "funcsandjacs.h"
#include "probsandmethods.h"

int cpmrk4 (float stepSize, int numberofSteps, float tolabs, float tolrel)
{
  FILE *f = fopen("output.dat", "w");
  double w = 5;
  double tao = 5;
  double constants[2] = {w, tao};
  gsl_odeiv2_system sys = { func, jac, 6, &constants };  
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                 stepSize, tolabs, tolrel);
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

int cpmrk23 (float stepSize, int numberofSteps, float tolabs, float tolrel)
{
  FILE *f = fopen("output.dat", "w");
  double w = 5;
  double tao = 5;
  double constants[2] = {w, tao};
  gsl_odeiv2_system sys = { func, jac, 6, &constants };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2,
                                 stepSize, tolabs, tolrel);
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

int cpmrk89 (float stepSize, int numberofSteps, float tolabs, float tolrel)
{
  FILE *f = fopen("output.dat", "w");
  double w = 5;
  double tao = 5;
  double constants[2] = {w, tao};
  gsl_odeiv2_system sys = { func, jac, 6, &constants };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
                                 stepSize, tolabs, tolrel);
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

int soderk4 (float stepSize, int numberofSteps, float tolabs, float tolrel)
{
  double mu = 0;
  double e;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                   stepSize, tolabs, tolrel);
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

int soderk23 (float stepSize, int numberofSteps, float tolabs, float tolrel)
{
  double mu = 0;
  double e;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2,
                                   stepSize, tolabs, tolrel);
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

int soderk89 (float stepSize, int numberofSteps, float tolabs, float tolrel)
{
  double mu = 0;
  double e;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
                                   stepSize, tolabs, tolrel);
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

int analyticalSolution (float stepSize, int numberofSteps)
{
  //double w = 5;
  //double tao = 5;
  FILE *f = fopen("outputAnalytical.dat", "w");
  double y[numberofSteps][4];
  int i;
  double t = 0.0;
  for (i = 0; i < numberofSteps; i++)
    {
      y[i][0] = (50/113)*exp(-t/5)*(exp(t/5)+25*sin(5*t)-cos(5*t));
      y[i][1] = (50/113)*exp(-t/5)*((-25)*exp(t/5)+sin(5*t)+25*cos(5*t));
      y[i][2] = 10-10*exp(-t/5);
      fprintf (f,"%.5e %.5e %.5e %.5e\n", t, y[i][0], y[i][1], y[i][2]);
      t = t + stepSize;
    }
  return 0;
}





