#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <grvy.h>
#include "funcsandjacs.h"

// The functions to be solved and the needed Jacobians are defined here
// func refers to the charged particle motion equations, func2 refers to the simple ODE. jac and jac2 are defined in the same manner.

int
func (double t, const double y[], double f[],
      void *params)
{
  (void)(t); /* avoid unused parameter warning */
  double *constants = (double *)params;
  double w = constants[0];
  double tao = constants[1];
  f[0] = y[3]; // y[0] refers to x, y[1] refers to y, y[2] to z, y[3] to u, y[4] to v, y[5] to w
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
  f[0]=y[0]; 
  return GSL_SUCCESS;
}

int
jac2 (double t, const double y[], double *dfdy,
     double dfdt[], void *params)
{
  (void)(t); /* avoid unused parameter warning */
  gsl_matrix_view dfdy_mat
  = gsl_matrix_view_array (dfdy, 1, 1); 
  gsl_matrix * m = &dfdy_mat.matrix; 
  gsl_matrix_set (m, 0, 0, 1); 
  dfdt[0] = 0.0; 
  return GSL_SUCCESS;
}

