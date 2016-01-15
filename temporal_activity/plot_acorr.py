import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import sys

save = False
name = ''
if len(sys.argv) == 2:
	name = sys.argv[1]
	save = True


nmax = 50

acorr = np.genfromtxt("acorr.csv",delimiter=';')
acorr_abs = np.genfromtxt("acorr_abs.csv",delimiter=';')
acorr_abs_avg = np.genfromtxt("acorr_abs_avg.csv",delimiter=';')
acorr_avg = np.genfromtxt("acorr_avg.csv",delimiter=';')

def expf(x,c):
	return np.exp(-x*c)


x0=[0]*nmax

n = len(acorr)
X = np.linspace(0.,n,n)

plt.ylim([-.2,1])

plt.subplot(2,4,1)
plt.plot(acorr[:nmax],color='black')
plt.plot(x0,color='black')
popt, pcov = curve_fit(expf,X,acorr[:n])
plt.plot(X[:nmax],expf(X[:nmax],*popt),color='blue')
plt.title("acorr")

plt.subplot(2,4,5)
xF = np.fft.fft(acorr)
N = len(xF)
xF = xF[:N/2]
fr = np.linspace(0,0.5,N/2)
plt.plot(fr,abs(xF)**2)
plt.yscale('log')
plt.xscale('log')


plt.subplot(2,4,2)
plt.plot(acorr_abs[:nmax],color='black')
plt.plot(x0,color='black')
popt, pcov = curve_fit(expf,X,acorr_abs[:n])
plt.plot(X[:nmax],expf(X[:nmax],*popt),color='blue')
plt.title("acorr_abs")

plt.subplot(2,4,6)
xF = np.fft.fft(acorr_abs)
N = len(xF)
xF = xF[:N/2]
fr = np.linspace(0,0.5,N/2)
plt.plot(fr,abs(xF)**2)
plt.yscale('log')
plt.xscale('log')


plt.subplot(2,4,3)
plt.plot(acorr_avg[:nmax],color='black')
plt.plot(x0,color='black')
popt, pcov = curve_fit(expf,X,acorr_avg[:n])
plt.plot(X[:nmax],expf(X[:nmax],*popt),color='blue')
plt.title("acorr_avg")

plt.subplot(2,4,7)
xF = np.fft.fft(acorr_avg)
N = len(xF)
xF = xF[:N/2]
fr = np.linspace(0,0.5,N/2)
plt.plot(fr,abs(xF)**2)
plt.yscale('log')
plt.xscale('log')

plt.subplot(2,4,4)
plt.plot(acorr_abs_avg[:nmax],color='black')
plt.plot(x0,color='black')
popt, pcov = curve_fit(expf,X,acorr_abs_avg[:n])
plt.plot(X[:nmax],expf(X[:nmax],*popt),color='blue')
plt.title("acorr_abs_avg")

plt.subplot(2,4,8)
xF = np.fft.fft(acorr_abs_avg)
N = len(xF)
xF = xF[:N/2]
fr = np.linspace(0,0.5,N/2)
plt.plot(fr,abs(xF)**2)
plt.yscale('log')
plt.xscale('log')


plt.tight_layout()

if not save:
	plt.show()
else:
	plt.savefig(name)
