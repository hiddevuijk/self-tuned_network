import numpy as np
import matplotlib.pyplot as plt
import sys
N=50
save = False
name = ''
if len(sys.argv) == 2:
	name = sys.argv[1]
	save = True


avs = np.genfromtxt("avs.csv",delimiter=';')
N = int(max(avs))
Pavs = [0]*(N)
n0 = 0
for i in range(len(avs)):
	if avs[i]==0:
		break
	n0 = n0 + 1
	n = int(avs[i]) - 1
	Pavs[n] = Pavs[n] + 1.

for i in range(len(Pavs)):
	Pavs[i] = Pavs[i]/n0


plt.plot(Pavs)
plt.yscale('log')
plt.xscale('log')
plt.title("distribution of avalanche size")
if not save:
	plt.show()
else:
	plt.savefig(name)

