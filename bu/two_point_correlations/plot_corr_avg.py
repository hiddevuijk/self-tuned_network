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
corr = np.genfromtxt("corr.csv",delimiter=';')

c = np.append(corr[len(corr)/2:],corr[:len(corr)/2])
t = np.linspace(-len(corr)/2,len(corr)/2,len(corr))

plt.plot(t,c)

if(not save):
	plt.show()
else:
	plt.savefig(name)



