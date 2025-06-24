import numpy as np
import matplotlib.pyplot as plt
plt.style.use('/home/llr/ilc/shi/code/Plot_style/cepc.mplstyle')

data = np.loadtxt("Sr90_Spectrum.dat")  
x, y = data[:, 0], data[:, 1]  

fig_Sr90=plt.figure(figsize=(8, 5))
plt.plot(x, y, marker='o', linestyle='-', color='b', label="Sr-90 Spectrum")
plt.xlabel("Energy (MeV)")  
plt.ylabel("Intensity (Arbitrary Units)")  
plt.title("Sr-90 Beta Spectrum")  
plt.legend()
plt.grid(True)
fig_Sr90.show()
print("The program has finished executing, press Enter to exit...")
input()  # The program will pause here until the user presses Enter
plt.close('all')