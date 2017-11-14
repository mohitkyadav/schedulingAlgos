import matplotlib.pyplot as plt

with open('outTAT.txt') as f:
    lines = f.read().splitlines()

lin = lines[0].split()

# x axis values
x = [1,2,3,4,5,6,7,8,9,10]
# corresponding y axis values
y = []

for elem in lin:
	y.append(float(elem))

print(y)
plt.scatter(x, y)
plt.xlabel('x - Time slice')
plt.ylabel('y - Awerage Turnaround Time')
plt.title('Q vs TAT')
plt.show()
