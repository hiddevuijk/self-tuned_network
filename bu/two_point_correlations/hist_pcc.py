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

print np.std(cc)
exit(0)
plt.hist(cc,50)
if(not save):
	plt.show()
else:
	plt.savefig(name)


