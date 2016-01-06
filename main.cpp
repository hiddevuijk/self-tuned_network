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
#include "headers/write_matrix.h"

// std headers
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace::std;

int main()
{
	int N =50;
	int dt = 1000000;

	double ti = 10000;
	double tf = ti+dt;

	VecDoub xw(N+N*N);
	Ran r(12345677);
	for(int i=0;i<(N+N*N);++i)  xw[i] = r.doub();
	double alpha = 1e-3;	
	NW nw(alpha,N);

	Output out_0_ti;	
	Output out(dt);

	double atol = 1.e-9;
	double rtol = atol;
	double h1 = 0.01;
	double hmin = 0.0;

	// integrate from 0 to ti
	Odeint<StepperDopr5<NW> > ode_0_ti(xw,0,ti,atol,rtol,h1,hmin,out_0_ti,nw);
	ode_0_ti.integrate();

	// integrate from ti to tf
	Odeint<StepperDopr5<NW> > ode(xw,ti,tf,atol,rtol,h1,hmin,out,nw);
	ode.integrate();

	double xmax=0;
	double xmin=0;
	for(int t=0;t<dt;++t){
		for(int i=0;i<N;++i) {
			if(out.ysave[i][t] > xmax)
				xmax = out.ysave[i][t];
			if(out.ysave[i][t] < xmin)
				xmin = out.ysave[i][t];
		}
	}

	double th = 0.5;
	if(xmax > abs(xmin)) {
		th *= xmax;
	} else {
		th *= -1*xmin;
	}

	vector<int> sau(dt,0);
	for(int t=0;t<dt;++t){
		for(int i=0;i<N;++i) {
			if(out.ysave[i][t] > th)
				++sau[t];
		}
	}

	write_matrix(sau,dt,"sau.csv");
	write_matrix(out.xsave,dt,"t_stat.csv");
	write_matrix(out.ysave,N+N*N,dt,"xw_stat.csv");
	return 0;
}
