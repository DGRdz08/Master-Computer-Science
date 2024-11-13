import subprocess

# Compilación del código C++
compilacion = subprocess.run(["g++", "problema01.cpp", "-o", "prog"], capture_output=True, text=True)

# Verificar si la compilación fue exitosa
if compilacion.returncode != 0:
    print("Error en la compilación:\n", compilacion.stderr)
else:
    print("Compilación exitosa.\nEjecutando el programa...")

    # Número de pruebas
    num_pruebas = 10

    # Bucle para ejecutar el código con cada instancia
    for i in range(1, num_pruebas + 1):
        archivo_entrada = f"instancias400/prueba{i}.txt"
        archivo_salida = f"instancias400/salidas/salida{i}.txt"

        # Ejecuta el programa con la entrada y redirige la salida al archivo correspondiente
        with open(archivo_salida, "w") as salida:
            ejecucion = subprocess.run(["./prog"], stdin=open(archivo_entrada, "r"), stdout=salida, text=True)
        
        # Verificar si la ejecución fue exitosa
        if ejecucion.returncode != 0:
            print(f"Error en la ejecución con prueba {i}: código de salida {ejecucion.returncode}")
            break  # Detener el bucle si hay un error
        else:
            print(f"Ejecución de prueba {i} completada y guardada en {archivo_salida}")

    print("Todas las ejecuciones completadas.")
