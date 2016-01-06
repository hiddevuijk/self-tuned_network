import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.colors import Normalize

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
for ti in range(tmax):
	for i in range(N):
		x[i][ti] = ysave[i][ti]


my_cmap = cm.get_cmap('hot')
plt.subplot(2,1,1)
plt.imshow(x,aspect='auto',cmap=my_cmap,interpolation='nearest')
plt.subplot(2,1,2)
plt.plot(x[1])
plt.show()

