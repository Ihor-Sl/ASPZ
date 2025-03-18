FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m user
USER user

WORKDIR /app
COPY . .

RUN gcc server_load.c -o server_load

CMD ["/bin/bash", "-c", "\
    echo '$ ulimit -u 80'; ulimit -u 80; \
    echo '$ ./server_load'; ./server_load"]