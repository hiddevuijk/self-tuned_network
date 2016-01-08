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
N = int(max(sau))
Psau = [0]*(N+1)
for i in range(len(sau)):
	n = int(sau[i])
	Psau[n] = Psau[n] + 1./len(sau)


plt.plot(Psau)
plt.yscale('log')
plt.title("distribution of simultaniously active units")
if not save:
	plt.show()
else:
	plt.savefig(name)

