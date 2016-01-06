import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.colors import Normalize

t = np.genfromtxt("t_stat.csv",delimiter=';')
ysave = np.genfromtxt("xw_stat.csv",delimiter=';')
#sau = np.genfromtxt("sau.csv",delimiter=';')

n = ysave.shape[0]
tmax = ysave.shape[1]-1

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
#w = np.asarray([[[0.]*tmax]*N]*N)
xmax = 0
xmin = 0
for ti in range(tmax):
	for i in range(N):
		x[i][ti] = ysave[i][ti]
		if x[i][ti] > xmax:
			xmax = x[i][ti]
		if x[i][ti] < xmin:
			xmin = x[i][ti]

th = 0.3*max(xmax,abs(xmin))
sau2 = [0]*tmax
for ti in range(tmax):
	for i in range(N):
		if abs(x[i][ti]) < th:
			x[i][ti] = 0
		else:
			x[i][ti] = 1
			sau2[ti] = sau2[ti]+1

my_cmap = cm.get_cmap('hot')
plt.subplot(2,1,1)
plt.imshow(x,aspect='auto',cmap=my_cmap,interpolation='nearest')
plt.subplot(2,1,2)
plt.plot(sau2)

plt.show()

