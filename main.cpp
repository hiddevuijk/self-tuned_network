// nr3 headers
#include "nr_headers/nr3.h"
#include "nr_headers/ran.h"
#include "nr_headers/fourier.h"
#include "nr_headers/correl.h"
#include "nr_headers/stepper.h"
#include "nr_headers/stepperbs.h"
#include "nr_headers/odeint.h"
#include "nr_headers/stepperdopr853.h"
#include "nr_headers/stepperdopr5.h"
#include "nr_headers/stepperstoerm.h"

// other headers
#include "headers/derivatives.h"

// std headers
#include <iostream>
#include <vector>
#include <string>

using namespace::std;

int main()
{
	int N =40;
	double ti = 0;
	double tf = 100000;

	VecDoub xw(N+N*N);
	Ran r(12345677);
	for(int i=0;i<(N+N*N);++i)  xw[i] = r.doub();
	double alpha = 1e-3;	
	NW nw(alpha,N);

	Output out;	


	double atol = 1.e-9;
	double rtol = atol;
	double h1 = 0.01;
	double hmin = 0.0;

	Odeint<StepperDopr5<NW> > ode(xw,ti,tf,atol,rtol,h1,hmin,out,nw);
	ode.integrate();

	return 0;
}
