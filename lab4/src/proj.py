import matplotlib.pyplot as plt
import numpy as np

with open(r'c:\Users\AimerYoung\OneDrive\USTC\大三下\计算方法\Lab\lab4\src\iris.txt') as file:
    data = []
    for line in file.readlines():
        temp = []
        line = line.strip().split(',')
        for i in line:
            temp.append(float(i))
        data.append(temp)
# print(data)

e = np.array([[[0.605926,-0.619615,0.491633,0.0850165,0],[0.666206,0.736359,0.0947871,0.0704234,0]],
        [[0.686724,0.305347,0.623663,0.214984,0],[-0.669089,0.567465,0.343327,0.335305,0]],
         [[0.741017,0.203288,0.627892,0.123775,0],[-0.165259,0.748643,-0.169428,0.619288,0]]])

x = np.zeros((3,50))
y = np.zeros((3,50))

for i in range(3):
    for j in range(50):
        x[i][j] = np.dot(e[i][0],data[50*i+j])
        y[i][j] = np.dot(e[i][1],data[50*i+j])


fig, ax = plt.subplots(figsize=(8, 6))

colors = ['r', 'g', 'b']

for i in range(3):
    ax.scatter(x[i], y[i], c=colors[i], label=f"tag =  {i}")

ax.set_title('PCA of Iris')
ax.set_xlabel('X-axis')
ax.set_ylabel('Y-axis')
ax.legend()

plt.show()