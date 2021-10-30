import matplotlib.pyplot as plt
from matplotlib.path import Path
import matplotlib.patches as patches
import numpy as np
import matplotlib.animation as animation

screenX = 800
screenY = 600

verts = [
   (-1 * screenX * .5, 0.0),   # P0
   (screenX * 3, screenY * 3),  # P1
   (-1 * screenX * .25, 200.0), # P200),  # P2
   (screenX * 0.5, 450.0),  # P3
]

codes = [
    Path.MOVETO,
    Path.CURVE4,
    Path.CURVE4,
    Path.CURVE4,
]

path = Path(verts, codes)

fig, ax = plt.subplots()
patch = patches.PathPatch(path, facecolor='none', lw=2)
ax.add_patch(patch)

xs, ys = zip(*verts)
ax.plot(xs, ys, 'x--', lw=2, color='black', ms=10)

# ax.text(-0.05, -0.05, 'P0')
# ax.text(0.15, 1.05, 'P1')
# ax.text(1.05, 0.85, 'P2')
# ax.text(0.85, -0.05, 'P3')

# ax.set_xlim(-0.1, 1.1)
# ax.set_ylim(-0.1, 1.1)
plt.grid()
plt.show()
