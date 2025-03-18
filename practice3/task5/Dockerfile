FROM debian:latest

RUN apt-get update && apt-get install -y \
    gcc \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . .

RUN gcc file_copy.c -o file_copy 

CMD ["/bin/bash", "-c", "\
    echo '$ ./file_copy input.txt outpux.txt'; ./file_copy input.txt outpux.txt; \
    echo 'Contents of outpux.txt:'; \
    cat outpux.txt"]