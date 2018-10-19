#!/usr/bin/python
"""
This is the from simple example to showcase Containernet.
Run it bt sudo python /path/to/file/cluster.py
"""
from mininet.net import Containernet
from mininet.node import Controller
from mininet.cli import CLI
from mininet.link import TCLink
from mininet.log import info, setLogLevel
setLogLevel('info')

net = Containernet(controller=Controller)
info('*** Adding controller\n')
net.addController('c0')
info('*** Adding docker containers\n')

# TODO
# create topology here.
# Hint :
s0 = net.addSwitch('S0')
s1 = net.addSwitch('S1')
s2 = net.addSwitch('S2')

d11 = net.addDocker('D11', ip='10.0.0.11', dimage="new-cnp")
d12 = net.addDocker('D12', ip='10.0.0.12', dimage="new-cnp")
d21 = net.addDocker('D21', ip='10.0.0.21', dimage="new-cnp")
d22 = net.addDocker('D22', ip='10.0.0.22', dimage="new-cnp")

info('*** Creating links\n')

# TODO
# create other links
# Hint :
net.addLink(s0, s1, cls=TCLink, delay='5ms', bw=1)
net.addLink(s0, s2, cls=TCLink, delay='5ms', bw=1)

net.addLink(s1, d11, cls=TCLink, delay='10ms', bw=5)
net.addLink(s1, d12, cls=TCLink, delay='10ms', bw=5)
net.addLink(s2, d21, cls=TCLink, delay='10ms', bw=5)
net.addLink(s2, d22, cls=TCLink, delay='10ms', bw=5)

info('*** Starting network\n')
net.start()
info('*** Testing connectivity\n')
# you can test connectivity between nodes with:
net.ping([d21, d22])
net.ping([d11, d22])

info('*** Setup nodes\n')

# start ssh on hosts
for host in net.hosts:
    host.cmd('/usr/sbin/sshd -D &')

# TODO
# By using d1.cmd('command') you can run `command` on container d1
# Run 'export HADOOP_HOSTS="list of comma separated host for example : `10.0.0.1 master, 10.0.0.2 slave1`"' on each host
# to declare nodes of cluster for it and on master node you also need to run 'export MY_ROLE="master"' to define it's role.
# run '/$HADOOP_HOME/etc/hadoop/start.sh > result' on each host to start hadoop on it.
exportVar = 'export HADOOP_HOSTS="10.0.0.11 slave1, 10.0.0.12 slave2, 10.0.0.21 slave3, 10.0.0.22 master"'
d11.cmd(exportVar)
d12.cmd(exportVar)
d21.cmd(exportVar)
d22.cmd(exportVar)  #master

d22.cmd('export MY_ROLE="master"')

runCmd = '/$HADOOP_HOME/etc/hadoop/start.sh > result'
d11.cmd(runCmd)
d12.cmd(runCmd)
d21.cmd(runCmd)
d22.cmd(runCmd)  #master

info('*** Running CLI\n')
CLI(net)
info('*** Stopping network')
net.stop()
