#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

//GSL - explicit RK4 
//The simple first order differential equation to solve is y'(x)=y(x) with the initial condition y(0)=1.

int
func (double t, const double y[], double f[],
      void *params)
{
  (void)(t); /* avoid unused parameter warning */
  (void *)(params); //ADDED
  //double mu = *(double *)params;
  //f[0] = y[1];
  //f[1] = -y[0] - mu*y[1]*(y[0]*y[0] - 1);
  f[0]=y[0]; //ADDED
  return GSL_SUCCESS;
}

int
jac (double t, const double y[], double *dfdy,
     double dfdt[], void *params)
{
  (void)(t); /* avoid unused parameter warning */
  //double mu = *(double *)params;
  (void *)(params); //ADDED
  gsl_matrix_view dfdy_mat
    //= gsl_matrix_view_array (dfdy, 2, 2);
  = gsl_matrix_view_array (dfdy, 1, 1); //ADDED
  gsl_matrix * m = &dfdy_mat.matrix;
  //gsl_matrix_set (m, 0, 0, 0.0);
  //gsl_matrix_set (m, 0, 1, 1.0);
  //gsl_matrix_set (m, 1, 0, -2.0*mu*y[0]*y[1] - 1.0);
  //gsl_matrix_set (m, 1, 1, -mu*(y[0]*y[0] - 1.0));
  //dfdt[0] = 0.0;
  //dfdt[1] = 0.0;
  gsl_matrix_set (m, 0, 0, 1);
  dfdt[0] = 1.0; //ADDED
  return GSL_SUCCESS;
}

int
main (void)
{
  //double mu = 10;
  double mu = 0; //ADDED
  double e;
  //gsl_odeiv2_system sys = { func, jac, 2, &mu };
  gsl_odeiv2_system sys = { func, jac, 1, &mu }; //ADDED

  gsl_odeiv2_driver *d =
    gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_rk4,
                                   1e-3, 1e-8, 1e-8);

  double t = 0.0;
  //double y[2] = { 1.0, 0.0 };
  double y[1] = { 1.0 }; //ADDED
  int i, s;

  for (i = 0; i < 100; i++)
    {
      s = gsl_odeiv2_driver_apply_fixed_step (d, &t, 1e-3, 1000, y);

      if (s != GSL_SUCCESS)
        {
          printf ("error: driver returned %d\n", s);
          break;
        }
      e = exp(t);
      //printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
      printf ("%.5e %.5e exact:%.5e\n", t, y[0],e); //ADDED
    }

  gsl_odeiv2_driver_free (d);
  return s;
}
