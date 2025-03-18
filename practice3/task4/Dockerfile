FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN gcc numbers_generator.c -o numbers_generator

CMD ["/bin/bash", "-c", "\
    echo '$ prlimit --cpu=1:2 ./numbers_generator'; prlimit --cpu=1:2 ./numbers_generator"]