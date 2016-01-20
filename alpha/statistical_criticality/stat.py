import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.colors import Normalize
import sys

save = False
name = ''
if len(sys.argv) == 2:
	save=True
	name = sys.argv[1]


t = np.genfromtxt("t_stat.csv",delimiter=';')
ysave = np.genfromtxt("xw_stat.csv",delimiter=';')

n = ysave.shape[0]
tmax = ysave.shape[1]

N1 =(-1+np.sqrt(1+4*n))/2
N2 =(-1-np.sqrt(1+4*n))/2
if N1>0 and N2<0:
	N=N1
if N1<0 and N2>0:
	N=N2
if (N1<0 and N2<0) or (N1>0 and N2>0):
	print "-----------------"
	print "can not find N"
	print "-----------------"
N = int(N)
x= np.asarray([[0.]*tmax]*N)
print "read inut 1"
xmax=0
xmin=0
for ti in range(tmax):
	for i in range(N):
		x[i][ti] = ysave[i][ti]
		if x[i][ti] > xmax:
			xmax = x[i][ti]
		if x[i][ti] < xmin:
			xmin = x[i][ti]

th = 0.5*max(xmax,abs(xmin))

for ti in range(tmax):
	for i in range(N):
		if abs(x[i][ti]) < th:
			x[i][ti] = 0
		else:
			x[i][ti] = 1
sau = np.asarray([0]*tmax)

for t in range(tmax):
	for i in range(N):
		sau[t] = sau[t] + x[i][t]

print "calculated sau"

s=np.genfromtxt("sau.csv",delimiter=';')
print "read sau.csv"
print len(s), ' sau.csv'
print len(sau), ' sau'
print sum(s-sau)
plt.hist(sau,log=True,normed=True)

if not save:
	plt.show()
else:
	plt.savefig(name+'.pdf')


