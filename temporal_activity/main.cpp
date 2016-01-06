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
#include "headers/other.h"

// std headers
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
using namespace::std;

int main(int argc, char *argv[])
{
	int N =50;

	int dt = 1000;
	if(argc == 2) {
		try {
			dt = stoi(argv[1]);
		}
		catch(exception& e) {
			cerr << "Unable to cast " << argv[1] << " to int" << endl;
			cerr << "ERROR: " << e.what() << endl;
			return 1;
		}
	}
	int tacorr = dt;
		
	double ti = 10000;
	double tf = ti+dt;

	VecDoub xw(N+N*N);
	Ran r(12345677);
	for(int i=0;i<(N+N*N);++i)  xw[i] = r.doub();
	double alpha = 1e-3;	
	NW nw(alpha,N);

	Output out_0_ti;	
	Output out(dt);

	double atol = 1.e-5;
	double rtol = atol;
	double h1 = 0.01;
	double hmin = 0.0;

	// integrate from 0 to ti
	Odeint<StepperDopr5<NW> > ode_0_ti(xw,0,ti,atol,rtol,h1,hmin,out_0_ti,nw);
	ode_0_ti.integrate();

	// integrate from ti to tf
	Odeint<StepperDopr5<NW> > ode(xw,ti,tf,atol,rtol,h1,hmin,out,nw);
	ode.integrate();

	int tacorr2 = pow2(2*tacorr);
	VecDoub acorr(tacorr,0.0);
	VecDoub acorr_temp(tacorr2,0.0);
	VecDoub acorr_ans(tacorr2,0.0);
	VecDoub acorr_temp_avg(tacorr2,0.0);
	VecDoub acorr_ans_avg(tacorr2,0.0);

	for(int i=0;i<N;++i) {
		for(int t=0;t<tacorr;++t) {
			acorr_temp[t] = out.ysave[i][t];
			acorr_temp_avg[t] += out.ysave[i][t];
		}

		double m = mean(acorr_temp,tacorr);
		add_to_vec(acorr_temp,tacorr,-1.*m);
		correl(acorr_temp,acorr_temp,acorr_ans);
		for(int t=0;t<tacorr;++t) {
			acorr[t] += acorr_ans[t]/acorr_ans[0];
		}
	}
	multiply_vec(acorr,tacorr,1./(double)N);

	multiply_vec(acorr_ans_avg,tacorr,1./(double)N);
	double m = mean(acorr_ans_avg,tacorr);
	add_to_vec(acorr_ans_avg,tacorr,-1.*m);
	correl(acorr_temp_avg,acorr_temp_avg,acorr_ans_avg);
	multiply_vec(acorr_ans_avg,tacorr,acorr_ans_avg[0]);	



	write_matrix(acorr,tacorr,"acorr.csv");
	write_matrix(acorr_ans_avg,tacorr,"acorr_avg.csv");
	write_matrix(out.ysave,dt,N+N*N,"xw.csv");

	return 0;
}
