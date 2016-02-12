import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import sys

save = False
name = ''
if len(sys.argv) == 2:
	name = sys.argv[1]
	save = True

cc = np.genfromtxt("cc.csv",delimiter=';')
t = np.genfromtxt("lag.csv",delimiter=';')

plt.subplot(1,2,1)
plt.hist(cc,50)
plt.subplot(1,2,2)
plt.hist(t)

if(not save):
	plt.show()
else:
	plt.savefig(name)


