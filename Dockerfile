FROM ubuntu:20.04

RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    openssh-server \
    openssh-client \
    sshpass \
    mpich \
    libomp-dev \
    nano \
    iputils-ping && \
    mkdir /var/run/sshd && \
    echo 'root:root' | chpasswd && \
    sed -i 's/#\?PermitRootLogin.*/PermitRootLogin yes/' /etc/ssh/sshd_config && \
    sed -i 's/#\?PasswordAuthentication.*/PasswordAuthentication yes/' /etc/ssh/sshd_config

COPY node-entrypoint.sh /node-entrypoint.sh
RUN chmod +x /node-entrypoint.sh

WORKDIR /app
COPY src /app

# Automatically compile main.c during build
RUN mpicc -fopenmp -o main /app/main.c

CMD ["/node-entrypoint.sh"]