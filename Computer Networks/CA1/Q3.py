from mininet.net import Mininet
from mininet.node import Controller
from mininet.cli import CLI
from mininet.log import setLogLevel, info

from mininet.topo import Topo
from mininet.node import CPULimitedHost
from mininet.link import TCLink
from mininet.util import dumpNodeConnections

setLogLevel('info')

net = Mininet(controller=Controller, link=TCLink)

info('*** Adding controller\n')
net.addController('c0')

info('*** Adding hosts\n')
h1 = net.addHost('h1', ip='10.0.0.1')
h2 = net.addHost('h2', ip='10.0.0.2')
h3 = net.addHost('h3', ip='10.0.0.3')
h4 = net.addHost('h4', ip='10.0.0.4')

info('*** Adding switch\n')
s1 = net.addSwitch('s1')
s2 = net.addSwitch('s2')
s3 = net.addSwitch('s3')

info('*** Creating links\n')
net.addLink(h1, s1, bw=5, delay='5ms')
net.addLink(h2, s1, bw=5, delay='5ms')

net.addLink(h3, s3, bw=5, delay='5ms')
net.addLink(h4, s3, bw=5, delay='5ms')

net.addLink(s1, s2, bw=1, delay='50ms')
net.addLink(s3, s2, bw=1, delay='50ms')

info('*** Starting network\n')
net.start()

info('*** Check Connectivity')
net.pingAll()

info('*** Running CLI\n')
CLI(net)

info( '*** Stopping network' )
net.stop()
