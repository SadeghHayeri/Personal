#!/bin/bash

# create hosts
ip netns add h1
ip netns add h2

# create switches
ovs-vsctl add-br s1
ovs-vsctl add-br s2

# set IP for h1 and h2
ip netns exec h1 ip addr add 10.0.0.1/24 dev h1-eth0
ip netns exec h2 ip addr add 10.0.0.2/24 dev h2-eth0


ip netns exec h1 ip link set h1-eth0 up
ip netns exec h2 ip link set h2-eth0 up

# enable lo for h1 and h2
ip netns exec h1 ip link set lo up
ip netns exec h2 ip link set lo up


# create switch ports
ovs-vsctl add-port s1 s1-eth1
ovs-vsctl add-port s1 s1-eth2
ip link set s1-eth1 up
ip link set s1-eth2 up

ovs-vsctl add-port s2 s2-eth1
ovs-vsctl add-port s2 s2-eth2
ip link set s2-eth1 up
ip link set s2-eth2 up

# connect links
ip link add s1-eth1 type veth peer name s2-eth1

ip link add s1-eth2 type veth peer name h1-eth0
ip link add s2-eth2 type veth peer name h2-eth0

# change interfaces
ip link set h1-eth0 netns h1
ip link set h2-eth0 netns h2

# h1 ping h2
echo ""
echo ">>>>>>> h1 try loopback ping <<<<<<<<"
ip netns exec h1 ping 127.0.0.1 -c 3
echo "--======================--"
echo ""
echo ">>>>>>> h1 ping h2 <<<<<<<<"
ip netns exec h1 ping 10.0.0.2 -c 3
echo "--======================--"
echo ""

# h2 ping h1
echo ">>>>>>> h2 try loopback ping <<<<<<<<"
ip netns exec h2 ping 127.0.0.1 -c 3
echo "--======================--"
echo ""
echo ">>>>>>> h2 ping h1 <<<<<<<<"
ip netns exec h2 ping 10.0.0.1 -c 3
echo "--======================--"
echo ""