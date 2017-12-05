#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <grvy.h>

int
func (double t, const double y[], double f[],
      void *params)
{
  (void)(t); /* avoid unused parameter warning */
  double *constants = (double *)params;
  double w = constants[0];
  double tao = constants[1];
  f[0] = y[3];
  f[1] = y[4];
  f[2] = y[5];
  f[3] = w*y[4] - (1/tao)*y[3];
  f[4] = -w*y[3] - (1/tao)*y[4];
  f[5] = -(1/tao)*y[5];
  return GSL_SUCCESS;
}

int
jac (double t, const double y[], double *dfdy,
     double dfdt[], void *params)
{
  (void)(t); /* avoid unused parameter warning */
  double *constants = (double *)params;
  double w = constants[0];
  double tao = constants[1];
  int i;
  for (i = 0; i < 36; i++)
	{
		dfdy[i] = 0;
	};
  dfdy[3] = 1;
  dfdy[10] = 1;
  dfdy[17] = 1;
  dfdy[21] = (-1/tao);
  dfdy[22] = w;
  dfdy[27] = -w;
  dfdy[28] = (-1/tao);
  dfdy[35] = (-1/tao);
  return GSL_SUCCESS;
}

int
func2 (double t, const double y[], double f[],
      void *params) 
{
  (void)(t); /* avoid unused parameter warning */
  f[0]=y[0]; //ADDED
  return GSL_SUCCESS;
}

int
jac2 (double t, const double y[], double *dfdy,
     double dfdt[], void *params)
{
  (void)(t); /* avoid unused parameter warning */
  gsl_matrix_view dfdy_mat
  = gsl_matrix_view_array (dfdy, 1, 1); //ADDED
  gsl_matrix * m = &dfdy_mat.matrix; 
  gsl_matrix_set (m, 0, 0, 1); //ADDED
  dfdt[0] = 0.0; //ADDED 
  return GSL_SUCCESS;
}

int
main (void)
{
  int problemNo;
  int solutionMethod;
  float stepSize;
  int verificationMode;
  int debugMode;

  grvy_input_fopen("./input.dat");

  if(grvy_input_fread_float("stepSize",&stepSize))
    printf("--> %-10s = %f\n","stepSize",stepSize);

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
  ///*implicit Euler*/
  //else if (problemNo == 2 && solutionMethod == 2)
  //	{
  //gsl_odeiv2_driver *d =
  //  gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk1imp,
  //                                 stepSize, 1e-8, 1e-8);
  //	}
  ///*implicit RK2*/
  //else if (problemNo == 2 && solutionMethod == 3)
  //	{
  //gsl_odeiv2_driver *d =
  //  gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2imp,
  //                                 stepSize, 1e-8, 1e-8);
  //	}
  double t = 0.0;
  double y[6] = { 0, 0, 0, 20, 0, 2 }; 
  int i, s;
  for (i = 0; i < 10000; i++)
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
  //if(solutionMethod == 1){ //implicit Euler
  //gsl_odeiv2_driver *d =
  //  gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk1imp,
  //                                 stepSize, 1e-8, 1e-8);}
  //if(solutionMethod == 2){ //implicit RK2
  //gsl_odeiv2_driver *d =
  //  gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk2imp,
  //                                 stepSize, 1e-8, 1e-8);}
  double t = 0.0;
  double y[1] = { 1.0 }; 
  int i, s;
  for (i = 0; i < 100; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, stepSize, 1000, y);
  
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
