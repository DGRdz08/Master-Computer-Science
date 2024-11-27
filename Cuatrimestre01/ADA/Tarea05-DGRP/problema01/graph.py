#https://www.youtube.com/watch?v=4Tb5oD7Do60
#https://stackoverflow.com/questions/19189362/getting-the-r-squared-value-using-curve-fit
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score

# Datos
n_values = np.array([1000, 2000, 3000, 5000, 10000])
times = np.array([0.002621, 0.005551, 0.008787, 0.015833, 0.034017])

# Modelos de ajuste
def linear_model(x, a, b):
    return a * x + b

def exponential_model(x, a, b):
    return a * np.exp(b * x)

def log_model(x, a, b):
    return a * np.log(x) + b

def power_model(x, a, b):
    return a * x**b

# Ajuste de los modelos
popt_linear, _ = curve_fit(linear_model, n_values, times)
popt_power, _ = curve_fit(power_model, n_values, times)

# Predicción con los modelos ajustados
linear_fit = linear_model(n_values, *popt_linear)
power_fit = power_model(n_values, *popt_power)

# Cálculo de R^2
r2_linear = r2_score(times, linear_fit)
r2_power = r2_score(times, power_fit)

# Impresión de resultados
print("Modelo Lineal: t(n) = {:.6f} * n + {:.6f}, R^2 = {:.4f}".format(popt_linear[0], popt_linear[1], r2_linear))
print("Modelo Potencial: t(n) = {:.6e} * n^{:.4f}, R^2 = {:.4f}".format(popt_power[0], popt_power[1], r2_power))

# Gráfica
plt.figure(figsize=(10, 6))
plt.scatter(n_values, times, color='red', label='Datos originales')
plt.plot(n_values, linear_fit, label=f'Modelo Lineal (R²={r2_linear:.4f})', linestyle='--', color='blue')
plt.plot(n_values, power_fit, label=f'Modelo Potencial (R²={r2_power:.4f})', linestyle='-', color='green')

# Personalización de la gráfica
plt.title('R² con ajuste lineal y potencial')
plt.xlabel('Tamaño de entrada (n)')
plt.ylabel('Tiempo (s)')
plt.legend()
plt.grid(True)
plt.show()
