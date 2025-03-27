#!/bin/bash

service ssh start
service ssh restart

if [ ! -f ~/.ssh/id_rsa ]; then
    ssh-keygen -t rsa -b 4096 -N "" -f ~/.ssh/id_rsa
fi

mkdir -p ~/.ssh
echo -e "Host *\n    StrictHostKeyChecking no\n    UserKnownHostsFile=/dev/null" > ~/.ssh/config
chmod 600 ~/.ssh/config

NODES=("node1" "node2" "node3")
MY_HOSTNAME=$(hostname)

for node in "${NODES[@]}"; do
    if [ "$node" != "$MY_HOSTNAME" ]; then
        sshpass -p root ssh root@$node "mkdir -p ~/.ssh && cat >> ~/.ssh/authorized_keys && chmod 600 ~/.ssh/authorized_keys" < ~/.ssh/id_rsa.pub
    fi
done

if [ "$MY_HOSTNAME" = "node1" ]; then
    sleep 5
    mpirun -np 6 -host node1,node2,node3 ./main
fi

tail -f /dev/null