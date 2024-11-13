#crear archivos de prueba
def crear_n_archivos(n):
    for i in range(n):
        f = open('problema02/pruebas/prueba'+str(i+1)+'.txt', 'w')
        f.close()

crear_n_archivos(10)