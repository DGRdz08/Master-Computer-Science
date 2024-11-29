import time
import subprocess

# Iniciar el temporizador en la máquina host
start_time = time.time()

# Iniciar los contenedores (suponiendo que uses docker-compose)
subprocess.run(["docker-compose", "up", "--build"])

# Esperar hasta que los contenedores hayan terminado su ejecución
# (Asegúrate de que los contenedores terminen antes de continuar)

# Detener el temporizador
end_time = time.time()

# Calcular el tiempo total
total_time = end_time - start_time
print(f"Tiempo total desde la máquina host: {total_time:.5f} segundos")