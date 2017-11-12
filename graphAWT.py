
# importing the required module
import matplotlib.pyplot as plt

with open('outAWT.txt') as f:
    lines = f.read().splitlines()

lin = lines[0].split()

# x axis values
x = [1,2,3,4,5,6,7,8,9,10]
# corresponding y axis values
y = []

for elem in lin:
	y.append(float(elem))

print(y)
plt.plot(x, y)
plt.xlabel('x - Time slice')
plt.ylabel('y - Awerage Waiting Time')
plt.title('Q vs AWT')
plt.show()
