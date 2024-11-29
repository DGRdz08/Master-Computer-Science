FROM ubuntu:22.04
RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY promedio.cpp /app
COPY watcher.sh /app
RUN g++ -o promedio promedio.cpp && chmod +x /app/watcher.sh

RUN mkdir -p /shared_memory && chmod 777 /shared_memory

CMD ["sh", "/app/watcher.sh"]
