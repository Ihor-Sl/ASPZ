FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN gcc stack_example.c -O0 -o stack_example

CMD ["/bin/bash", "-c", "\
    echo '$ prlimit --stack=100000:100000 ./stack_example'; prlimit --stack=100000:100000 ./stack_example"]