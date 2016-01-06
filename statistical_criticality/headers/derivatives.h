#ifndef GUARD_derivatives_h
#define GUARD_derivatives_h

struct NW {
	double alpha;
	int N;
	NW(double alphaa,int  NN) :
		alpha(alphaa) , N(NN) {}

	void operator() (const Doub t, VecDoub_I& xw, VecDoub_O& dxwdt)
	{
			for(int i=0;i<N;++i) {
				dxwdt[i] =0;
				for(int j=0;j<N;++j) {
					dxwdt[i] += xw[(1+j)*N+i]*xw[j];
				}
			}
			for(int i=0;i<N;++i) for(int j=0;j<N;++j) {
				dxwdt[i+(j+1)*N] = -1.*alpha*xw[i]*xw[j];
				if(i==j) dxwdt[i+(j+1)*N] += alpha;
			}
	}
};



#endif
