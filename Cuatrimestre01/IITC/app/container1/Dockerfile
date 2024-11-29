FROM ubuntu:22.04
RUN apt-get update && apt-get install -y g++ && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY LCG.cpp /app

RUN g++ -o LCG LCG.cpp

RUN mkdir -p /shared_memory && chmod 777 /shared_memory

CMD ["./LCG"]
