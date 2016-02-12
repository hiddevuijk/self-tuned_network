#ifndef GUARD_find_max_h
#define GUARD_find_max_h


void find_max_in_range(const VecDoub& v,int N, int r, double& maxt, double& maxc)
{
	maxt = 0;
	maxc = v[0];

	for(int i=1;i<N;++i) {
		if(abs(v[i-1]) > abs(v[i]) ){
			maxt = i-1;
			maxc = v[i-1];
			break;
		}
	}
	for(int i=1;i<N;++i) {
		if(abs(v[N-i]) > abs(v[N-1-i]) ) {
			if(abs(v[N-i]) > abs(maxc) && i < maxt) {
				maxt = i;
				maxc = v[N-i];
			}
			break;
		}
	}


}



#endif
