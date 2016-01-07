import numpy as np
import matplotlib.pyplot as plt
import sys
N=50
save = False
name = ''
if len(sys.argv) == 2:
	name = sys.argv[1]
	save = True


sau = np.genfromtxt("sau.csv",delimiter=';')
plt.hist(sau,log=True,normed=True,bins = np.arange(min(sau),max(sau)+1,1))
plt.title("distribution of simultaniously active units")
if not save:
	plt.show()
else:
	plt.savefig(name)

