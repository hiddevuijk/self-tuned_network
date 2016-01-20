import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import sys

save = False
name = ''
if len(sys.argv) == 2:
	name = sys.argv[1]
	save = True



corr1 = np.genfromtxt("corr_1.csv",delimiter=';')
corr2 = np.genfromtxt("corr_2.csv",delimiter=';')
corr3 = np.genfromtxt("corr_2.csv",delimiter=';')


t = np.linspace(-len(corr1)/2,len(corr1)/2,len(corr1))
c1 = np.append(corr1[len(corr1)/2:],corr1[:len(corr1)/2])
c2 = np.append(corr2[len(corr1)/2:],corr2[:len(corr1)/2])
c3 = np.append(corr3[len(corr1)/2:],corr3[:len(corr1)/2])


plt.subplot(3,1,1)
plt.plot(t,c1)

plt.subplot(3,1,2)
plt.plot(t,c2)

plt.subplot(3,1,3)
plt.plot(t,c3)

if(not save):
	plt.show()
else:
	plt.savefig(name)



