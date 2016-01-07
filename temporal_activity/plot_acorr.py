import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import sys

save = False
name = ''
if len(sys.argv) == 2:
	name = sys.argv[1]
	save = True


nmax = 30

acorr = np.genfromtxt("acorr.csv",delimiter=';')
acorr_abs = np.genfromtxt("acorr_abs.csv",delimiter=';')

def expf(x,c):
	return np.exp(-x*c)


x0=[0]*nmax
X = np.linspace(0.,nmax,nmax)

plt.ylim([-.2,1])

plt.subplot(2,1,1)
plt.plot(acorr[:nmax],color='black')
plt.plot(x0,color='black')
popt, pcov = curve_fit(expf,X,acorr[:nmax])
plt.plot(X,expf(X,*popt),color='blue')
plt.title("acorr")

plt.subplot(2,1,2)
plt.plot(acorr_abs[:nmax],color='black')
plt.plot(x0,color='black')
popt, pcov = curve_fit(expf,X,acorr_abs[:nmax])
plt.plot(X,expf(X,*popt),color='blue')
plt.title("acorr_abs")

plt.tight_layout()

if not save:
	plt.show()
else:
	plt.savefig(name)
