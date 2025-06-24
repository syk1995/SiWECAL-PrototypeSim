import ROOT
import uproot
import matplotlib.pyplot as plt
import awkward as ak
import numpy as np
plt.style.use('/home/llr/ilc/shi/code/Plot_style/cepc.mplstyle')
DATA_DIR="/data_ilc/flc/shi/TB_2025_3/Comission/Sr90/MC/Sr90"
PLOT_DIR=f"{DATA_DIR}/Plot"
PAR="Sr90"
input_root = f"{DATA_DIR}/{PAR}.edm4hep.root"
input_tree = "events"
input_branch = "SiEcalCollection"
print(f"Read root: {input_root}\n")
print(f"Read tree: {input_tree}\n")
print(f"Read branch: {input_branch}\n")

# Open the ROOT file
with uproot.open(input_root) as file:
    tree = file[input_tree]  # Read the TTree
    
    # Check the Branch structure
    print(tree.keys())  # Print all branch names to confirm "SiEcalCollection" exists

    # Read "SiEcalCollection.position.y"
    try:
        x_positions = tree[f"{input_branch}.position.x"].array()
        y_positions = tree[f"{input_branch}.position.y"].array()
    except KeyError as e:
        print(f"Error: {e} not found in '{input_tree}'.")
        exit()

# Convert to a NumPy array (flatten if it's a JaggedArray)
y_positions = ak.flatten(y_positions)
x_positions = ak.flatten(x_positions)
y_positions = ak.to_numpy(y_positions)
x_positions = ak.to_numpy(x_positions)
print("Size of y_positions:", len(y_positions))
print("Size of x_positions:", len(x_positions))

# Plot histogram
CellSize = 5.5
CellNo = 32
plt_name = "position_xy"
range_x = (-CellNo*CellSize/2, CellNo*CellSize/2)
range_y = (-CellNo*CellSize/2, CellNo*CellSize/2)
figure_posxy,ax = plt.subplots(1,1,figsize=(8,8))
hb=ax.hist2d(x_positions,y_positions,bins=(CellNo,CellNo),range=[range_x,range_y],cmap="GnBu")
ax.set_xlim(range_x)
ax.set_ylim(range_y)
ax.set_xlabel("X[mm]")
ax.set_ylabel("Y[mm]")
figure_posxy.colorbar(ax.collections[0],ax=ax,label="Number of hits")
plt.subplots_adjust(left=0.2)
figure_posxy.show()


print("The program has finished executing, press Enter to exit...")
input()  # The program will pause here until the user presses Enter
plt.close('all')