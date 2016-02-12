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
		
	double ti = 100000;
	double tf = ti+dt;

	VecDoub xw(N+N*N);
	Ran r(12345677);
	for(int i=0;i<(N+N*N);++i)  xw[i] = r.doub();
	double alpha = 1.e-4;	
	NW nw(alpha,N);

	Output out_0_ti;	
	Output out(dt);

	double atol = 1.e-12;
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

	VecDoub acorr(tacorr,0.0); 		// avg(correl(temp))
	VecDoub temp(tacorr2,0.0);		// xi
	VecDoub acorr_ans(tacorr2,0.0);	// correl(xi)

	VecDoub acorr_abs(tacorr,0.0);	// avg(correl(temp_abs))
	VecDoub temp_abs(tacorr2,0.0);	// abs(xi)
	VecDoub acorr_abs_ans(tacorr2,0.0); // correl(abs(xi))

	VecDoub activity(tacorr2,0.0);		// sum(xi)
	VecDoub activity_abs(tacorr2,0.0);	// sum(abs(xi))

	VecDoub acorr_avg(tacorr2,0.0);		// avg(abs(xi))
	VecDoub acorr_abs_avg(tacorr2,0.0);	// correl(avg(abs(xi)))

	for(int i=0;i<N;++i) {
		for(int t=0;t<tacorr;++t) {
			temp[t] = out.ysave[i][t];
			temp_abs[t] = abs(out.ysave[i][t]);
			activity[t] += out.ysave[i][t];
			activity_abs[t] += abs(out.ysave[i][t]);
		}

		double m = mean(temp,tacorr);
		add_to_vec(temp,tacorr,-1.*m);
		correl(temp,temp,acorr_ans);

		m = mean(temp_abs,tacorr);
		add_to_vec(temp_abs,tacorr,-1.*m);
		correl(temp_abs,temp_abs,acorr_abs_ans);

		for(int t=0;t<tacorr;++t) {
			acorr[t] += acorr_ans[t]/(acorr_ans[0]*N);
			acorr_abs[t] += acorr_abs_ans[t]/(acorr_abs_ans[0]*N);
		}
	}

	write_matrix(activity,tacorr,"activity.csv");
	write_matrix(activity_abs,tacorr,"activity_abs.csv");

	double m = mean(activity,tacorr);
	add_to_vec(activity,tacorr,-1.*m);
	correl(activity,activity,acorr_avg);

	m = mean(activity_abs,tacorr);
	add_to_vec(activity_abs,tacorr,-1.*m);
	correl(activity_abs,activity_abs,acorr_abs_avg);

	double acorr_avg0 = acorr_avg[0];
	double acorr_abs_avg0 = acorr_abs_avg[0];

	for(int t = 0;t<tacorr;++t) {
		acorr_avg[t] /= acorr_avg0;
		acorr_abs_avg[t] /= acorr_abs_avg0;
	}
	
	write_matrix(acorr_avg,tacorr,"acorr_avg.csv");
	write_matrix(acorr_abs_avg,tacorr,"acorr_abs_avg.csv");
	write_matrix(acorr,tacorr,"acorr.csv");
	write_matrix(acorr_abs,tacorr,"acorr_abs.csv");

	return 0;
}
