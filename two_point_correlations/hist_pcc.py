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

plt.hist(cc,50)
if(not save):
	plt.show()
else:
	plt.savefig(name)


