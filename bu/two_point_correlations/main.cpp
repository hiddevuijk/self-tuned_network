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


	int tcorr2 = 2*pow2(dt);
	VecDoub a(tcorr2,0.0);
	VecDoub b(tcorr2,0.0);
	VecDoub corr(tcorr2,0.0);
	VecDoub corr_avg(tcorr2,0.0);
	vector<double> corr_coef;

	int i1 = r.int64() % (N-1);
	int i2 = r.int64() % (N-1);
	int j1 = r.int64() % (N-1);
	int j2 = r.int64() % (N-1);
	int i3 = r.int64() % (N-1);
	int j3 = r.int64() % (N-1);


	for(int i=0;i<N;++i) {
		for(int k=0;k<dt;++k){
			a[k] = out.ysave[i][k];
		}
		normal_form(a,dt);	
		for(int j=0;j<N;++j)if(i!=j) {
			
			for(int k=0;k<dt;++k){
				b[k] = out.ysave[j][k];
			}
			normal_form(b,dt);	
			correl(a,b,corr);
			multiply_vec(corr,tcorr2,1/(double)dt);
			if(i==i1 and j==j1)
				write_matrix(corr,tcorr2,"corr_1.csv");
			if(i==i2 and j==j2)
				write_matrix(corr,tcorr2,"corr_2.csv");
			if(i==i3 and j==j3)
				write_matrix(corr,tcorr2,"corr_3.csv");

			for(int k=0;k<tcorr2;++k)
				corr_avg[k] = corr[k]/((double)N*(N-1));
			if(i<j){
				corr_coef.push_back(corr[0]);
			}
		}
	}
	


	write_matrix(corr_coef,corr_coef.size(),"cc.csv");
	write_matrix(corr_avg,tcorr2,"corr.csv");

	
	return 0;
}
