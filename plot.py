import numpy as np
import matplotlib.pyplot as plt
import sys

sau = np.genfromtxt("sau.csv",delimiter=';')
plt.hist(sau,log=True,normed=True)
plt.show()

