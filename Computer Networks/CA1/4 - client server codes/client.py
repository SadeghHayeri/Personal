from socket import *
import sys
import time

def currTime():
    return float(round(time.time()*1000))

for i, ip in enumerate(sys.argv[1:]):
	serverPort = 8000
	clientSocket = socket(AF_INET, SOCK_DGRAM)
	#1 byte
	modifiedMessagege = 'a' 
	t = currTime()
	clientSocket.sendto(modifiedMessagege,(ip, serverPort))
	modifiedMessage, serverAddress = clientSocket.recvfrom(10000)
	print modifiedMessage
	t1 = currTime() - t
	print t1, "ms"
	#10 KB
	modifiedMessagege = 'a' + 9998 * 'c' + 'z'
	t = currTime()
	clientSocket.sendto(modifiedMessagege,(ip, serverPort))
	modifiedMessage, serverAddress = clientSocket.recvfrom(10000)
	print modifiedMessage
	t2 = currTime() - t
	print t2, "ms"
	print 'dif: ', t2 - t1
	clientSocket.close()