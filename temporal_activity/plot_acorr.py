import numpy as np
import matplotlib.pyplot as plt
import sys

acorr = np.genfromtxt("acorr.csv",delimiter=';')
acorr_avg = np.genfromtxt("acorr_avg.csv",delimiter=';')

plt.subplot(2,1,1)
plt.plot(acorr[:50])
plt.subplot(2,1,2)
plt.plot(acorr_avg[:50])
plt.show()
