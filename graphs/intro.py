import matplotlib.pyplot as plt
import numpy as np

nums = [1, 2, 3, 4]

t2 = np.arange(0.0, 2.0, 0.02)

print(t2)

plt.plot(nums, list(map(lambda x: x*2, nums)), 'r--')
plt.plot(nums, list(map(lambda x: x*3, nums)), 'b--')
plt.plot(nums, list(map(lambda x: x*4, nums)), 'g--')
# plt.plot(t2, np.cos(2*np.pi*t2), 'r-')
plt.plot(t2, np.sin(2*np.pi*t2), 'r-')
plt.ylabel("some numbers")
plt.title("Simple Plot")
plt.show()
