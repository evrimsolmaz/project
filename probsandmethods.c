#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <grvy.h>
#include <time.h>
#include "funcsandjacs.h"
#include "probsandmethods.h"

// All the solvers are in this function. They all use GSL's RK4, RK2-3 or RK8-9 stepping functions.

int cpmrk4 (float stepSize, int numberofSteps, float tolabs, float tolrel, int debugMode)
{
  FILE *f = fopen("output.dat", "w");
  double w = 5;
  double tao = 5;
  double constants[2] = {w, tao};
  gsl_odeiv2_system sys = { func, jac, 6, &constants }; //The system of equations are defined: func, jac,6 equations, w, tao  
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                 stepSize, tolabs, tolrel); //RK4 stepping function is used
  double t = 0.0; //Starting from t=0
  double y[6] = { 0, 0, 0, 20, 0, 2 };  //Initial conditions. 6 refers to the number of equations present
  int i, s;
  clock_t begin = clock();
  for (i = 0; i < numberofSteps; i++)
    {   
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y); //Solution advances in time with fixed time steps
      if (s != GSL_SUCCESS)
        {   
          printf ("error: driver returned %d\n", s); 
          break;
        }   
      fprintf (f,"%.5e %.5e %.5e %.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2], y[3], y[4], y[5]);
    }
  gsl_odeiv2_driver_free (d);
  clock_t end = clock();
  if (debugMode == 1)
  {
    printf ("Constants: w is %lf and tao is %lf\n", w, tao);
    printf ("The Jacobian is\n0 0 0 1 0 0\n0 0 0 0 1 0\n0 0 0 0 0 1\n0 0 0 (-1/%lf) %lf 0\n0 0 0 -%lf (-1/%lf) 0\n0 0 0 0 0 (-1/%lf)\n", tao, w, w, tao, tao); 
  }
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent to reach the solution is %.5e seconds\n", time_spent);
  return s;
}

int cpmrk23 (float stepSize, int numberofSteps, float tolabs, float tolrel, int debugMode)
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
  clock_t begin = clock();
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
  clock_t end = clock();
  if (debugMode == 1)
  {
    printf ("Constants: w is %lf and tao is %lf\n", w, tao);
    printf ("The Jacobian is\n0 0 0 1 0 0\n0 0 0 0 1 0\n0 0 0 0 0 1\n0 0 0 (-1/%lf) %lf 0\n0 0 0 -%lf (-1/%lf) 0\n0 0 0 0 0 (-1/%lf)\n", tao, w, w, tao, tao); 
  }
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent to reach the solution is %.5e seconds\n", time_spent);
  return s;
}

int cpmrk89 (float stepSize, int numberofSteps, float tolabs, float tolrel, int debugMode)
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
  clock_t begin = clock();
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
  clock_t end = clock();
  if (debugMode == 1)
  {
    printf ("Constants: w is %lf and tao is %lf\n", w, tao);
    printf ("The Jacobian is\n0 0 0 1 0 0\n0 0 0 0 1 0\n0 0 0 0 0 1\n0 0 0 (-1/%lf) %lf 0\n0 0 0 -%lf (-1/%lf) 0\n0 0 0 0 0 (-1/%lf)\n", tao, w, w, tao, tao); 
  }
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent to reach the solution is %.5e seconds\n", time_spent);
  return s;
}

int soderk4 (float stepSize, int numberofSteps, float tolabs, float tolrel, int debugMode)
{
  double mu = 0;
  double e, errorNorm;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                   stepSize, tolabs, tolrel);
  double t = 0.0;
  double y[1] = { 1.0 };
  int i, s;
  clock_t begin = clock();
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);
      if (s != GSL_SUCCESS)
       {
          printf ("error: driver returned %d\n", s);
          break;
        }
      e = exp(t);
      errorNorm = e - y[0];
      printf ("%.5e %.5e exact:%.5e error:%.5e\n", t, y[0], e, errorNorm);
    }
  gsl_odeiv2_driver_free (d);
  clock_t end = clock();
  if (debugMode == 1)
  {
    printf ("The initial condition is 1.\n");
  }
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent to reach the solution is %.5e seconds\n", time_spent);
  return s;
}

int soderk23 (float stepSize, int numberofSteps, float tolabs, float tolrel, int debugMode)
{
  double mu = 0;
  double e, errorNorm;;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2,
                                   stepSize, tolabs, tolrel);
  double t = 0.0;
  double y[1] = { 1.0 };
  int i, s;
  clock_t begin = clock();
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);
      if (s != GSL_SUCCESS)
       {
          printf ("error: driver returned %d\n", s);
          break;
        }
      e = exp(t);
      errorNorm = e - y[0];
      printf ("%.5e %.5e exact:%.5e error:%.5e\n", t, y[0],e, errorNorm);
    }
  gsl_odeiv2_driver_free (d);
  clock_t end = clock();
  if (debugMode == 1)
  {
    printf ("The initial condition is 1.\n");
  }
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent to reach the solution is %.5e seconds\n", time_spent);
  return s;
}

int soderk89 (float stepSize, int numberofSteps, float tolabs, float tolrel, int debugMode)
{
  double mu = 0;
  double e, errorNorm;;
  gsl_odeiv2_system sys = { func2, jac2, 1, &mu };
  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk8pd,
                                   stepSize, tolabs, tolrel);
  double t = 0.0;
  double y[1] = { 1.0 };
  int i, s;
  clock_t begin = clock();
  for (i = 0; i < numberofSteps; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1, y);
      if (s != GSL_SUCCESS)
       {
          printf ("error: driver returned %d\n", s);
          break;
        }
      e = exp(t);
      errorNorm = e - y[0];
      printf ("%.5e %.5e exact:%.5e error:%.5e\n", t, y[0],e, errorNorm);
    }
  gsl_odeiv2_driver_free (d);
  clock_t end = clock();
  if (debugMode == 1)
  {
    printf ("The initial condition is 1.\n");
  }
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("time spent to reach the solution is %.5e seconds\n", time_spent);
  return s;
}

int analyticalSolution (float stepSize, int numberofSteps, int debugMode)
{
  FILE *f = fopen("outputAnalytical.dat", "w"); //This is where the analytical solution will be stored
  double *y = calloc(3, sizeof (double)); // allocate memory for 3 doubles
  int i;
  double t = 0.0;
  for (i = 0; i < numberofSteps; i++)
    {
      y[0] = (50.0/313.0)*exp(-t/5)*(exp(t/5)+25*sin(5*t)-cos(5*t));
      y[1] = (50.0/313.0)*exp(-t/5)*((-25)*exp(t/5)+sin(5*t)+25*cos(5*t));
      y[2] = 10-10*exp(-t/5); //The analytical solution
      t = t + stepSize;
      fprintf (f,"%.5e %.5e %.5e %.5e\n", t, y[0], y[1], y[2]);
    }
  fclose(f);
  free(y); //to free memory for the memory consuming norm calculations below
  FILE *f0 = fopen("outputAnalytical.dat", "r");
  FILE *f1 = fopen("output.dat", "r");
  FILE *f2 = fopen("norm.dat", "w");
  double *num0 = calloc(4, sizeof (double)); //array consists of time step, x, y, z
  double *num1 = calloc(7, sizeof (double)); //array consists of time step, x, y, z, u, v, w
  double norm = 0.0;
  printf("For easy observation, results from the first 200 time steps is listed below. The full analytical solution is saved in outputAnalytical.dat.\n");
  for (i = 0; i < 200; i++)
  //for (i = 0; i < numberofSteps; i++)
    {
      fscanf(f0, "%lf %lf %lf %lf\n", &num0[0], &num0[1], &num0[2], &num0[3]);
      fscanf(f1, "%lf %lf %lf %lf %lf %lf %lf\n", &num1[0], &num1[1], &num1[2], &num1[3], &num1[4], &num1[5], &num1[6]);
      // Here, the calculated norm is the "two-norm" of the x,y,z coordinates:
      norm = sqrt(pow((num1[1]-num0[1]),2.0)+pow((num1[2]-num0[2]),2.0)+pow((num1[3]-num0[3]),2.0));
      if (debugMode == 1)
        {   
          printf("Analytical soln. at time=%.4e: %.4e %.4e %.4e\n", num0[0], num0[1], num0[2], num0[3]);
          printf("Numerical soln. at time=%.4e: %.4e %.4e %.4e, error norm=%.4e\n", num1[0], num1[1], num1[2], num1[3],  norm);
        }
      else 
        {
	  printf("time=%.5e\tnorm=%.5e\n", num0[0], norm);
        }
      fprintf(f2,"Analytical soln. at time=%.5e: %.5e %.5e %.5e\n", num0[0], num0[1], num0[2], num0[3]);
      fprintf(f2,"Numerical soln. at time=%.5e: %.5e %.5e %.5e, error norm=%.5e\n", num1[0], num1[1], num1[2], num1[3], norm); 
    }
  printf("The difference between numerical and analytical solution (error norm) at each time step are listed above. \n");
  fclose(f0);
  fclose(f1);
  fclose(f2);
  return 0;
}
