#include <stdio.h>
#include <math.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

//with GSL 
//Charged particle motion equations:

//x'=u
//y'=v
//z'=w
//u'=wv-u/tao
//v'=-wu-v/tao
//w'=-w/tao

//w=5, tao=5, ICS: x_0=(0,0,0) and v_0=(20,0,2)

int
func (double t, const double y[], double f[],
      void *params)
{
  (void)(t); /* avoid unused parameter warning */
  //(void *)(params); //ADDED
  double w = *(double *)params;
  double tao = *(double *)params;
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
  gsl_matrix_set (m, 0, 0, 1); //ADDED
  dfdt[0] = 1.0; //ADDED
  return GSL_SUCCESS;
}

int
main (void)
{
  //double mu = 10;
  //double mu = 0; //ADDED
  double w = 5;
  double tao = 5;
  double e; //ADDED
  //gsl_odeiv2_system sys = { func, jac, 2, &mu };
  gsl_odeiv2_system sys = { func, jac, 1, &mu }; //ADDED

  //RK4:
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
      e = exp(t); //ADDED
      //printf ("%.5e %.5e %.5e\n", t, y[0], y[1]);
      printf ("%.5e %.5e exact:%.5e\n", t, y[0],e); //ADDED
    }

  gsl_odeiv2_driver_free (d);
  return s;
}
