#Recuperado de https://www.youtube.com/watch?v=4Tb5oD7Do60
import matplotlib.pyplot as plt
import numpy as np
x=[1,2,3,4,5]
y=[2,3,6,8,11]

plt.scatter(x, y, color='blue')

# Linea tendencia
coef = np.polyfit(x,y,2) 
polinomio=np.polyld(coef)

plt.plot(x,polinomio(x),color='red', label='Linea de tendencia')

plt.scatter(x, y, color='blue')
plt.title('Grafica de puntos')
plt.xlabel('Eje X')
plt.ylabel('Eje Y')
plt.grid(True)
plt.show()