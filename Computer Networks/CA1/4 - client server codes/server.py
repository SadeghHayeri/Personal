from socket import *
serverPort = 8000
serverSocket = socket(AF_INET, SOCK_DGRAM)
serverSocket.bind(('', serverPort))
print "The server is ready to receive khers"
while True:
    message, clientAddress = serverSocket.recvfrom(10000)
    print message, clientAddress
    modifiedMessage = message.upper()
    serverSocket.sendto('ACK', clientAddress)