FROM ubuntu:22.04
RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY promedio.cpp /app
RUN g++ -o promedio promedio.cpp

# Asegura permisos de lectura en el volumen compartido
RUN mkdir -p /shared_memory && chmod 777 /shared_memory

CMD ["sh", "-c", "sleep 5 && test -f /shared_memory/datos.txt && ./promedio < /shared_memory/datos.txt"]