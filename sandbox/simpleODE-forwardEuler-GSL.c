#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_sf_bessel.h>

//Forward Euler with GSL

//The simple first order differential equation to solve is y'(x)=y(x) with the initial condition y(0)=1.

double function(double y)
{
	double f;
	f=y;
	return f;
}

int main()
{
	double h,xn;
	double x,y;
	printf("\nEnter h,xn: ");
	scanf("%lf%lf",&h,&xn);
	x=0;
	y=1;
	printf("\n x\t y\n");
	while(x<=xn)
	{
		y=y+h*function(y);
		x=x+h;
		printf("%0.3f\t%0.3f\n",x,y);
	}
//check analytical solution:
	double e;
	e=exp(xn);
	printf("The analytical solution is %lf\n",e);
	return 0;
}
