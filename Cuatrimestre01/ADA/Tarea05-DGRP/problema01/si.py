import random

def generar_archivo_prueba(nombre_archivo, cantidad_lugares):
    with open(nombre_archivo, 'w') as archivo:
        # Escribir la cantidad de lugares
        archivo.write(f"{cantidad_lugares}\n")
        
        # Generar cada lugar con valores aleatorios para X y Y
        for i in range(1, cantidad_lugares + 1):
            lugar = f"lugar{i}"
            x = random.randint(0, 10**9)
            y = random.randint(0, 10**9)
            archivo.write(f"{lugar} {x} {y}\n")

# Ejemplo de uso
generar_archivo_prueba("10prueba1000.txt", 10000)