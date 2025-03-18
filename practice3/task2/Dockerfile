FROM debian:latest

RUN apt-get update && apt-get install -y \
    linux-perf \
    && rm -rf /var/lib/apt/lists/*

CMD ["/bin/bash", "-c", "\
    echo '$ perf --version'; perf --version; \
    echo '$ perf stat echo Hello World'; perf stat echo Hello World!;"]