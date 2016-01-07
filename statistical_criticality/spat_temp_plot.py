import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.colors import Normalize
import sys

save = False
name = ''
if len(sys.argv) == 2:
	save = True
	name = sys.argv[1]

th = 2.5

ysave = np.genfromtxt("xw.csv",delimiter=';')

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

sau2 = [0]*tmax
for ti in range(tmax):
	for i in range(N):
		if abs(ysave[i][ti]) < th:
			x[i][ti] = 0
		else:
			x[i][ti] = 1
			sau2[ti] = sau2[ti]+1
my_cmap = cm.get_cmap('hot')
plt.subplot(2,1,1)
plt.imshow(x,aspect='auto',cmap=my_cmap,interpolation='nearest')
plt.subplot(2,1,2)
plt.plot(sau2)

if not save:
	plt.show()
else:
	plt.savefig(name)


