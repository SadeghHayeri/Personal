#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <unistd.h>

#include <time.h>

#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <iostream>

#include <stdio.h>
#include <utility>


#include "network.h"
#include "utility.h"
#include "pipe.h"
#include "structs.h"

#include "p1.h"
#include "p2.h"

using namespace std;


void quit(int status) {
	Named_pipe p = Named_pipe(NAMED_PIPE_PATH);
	p << EXIT_COMMAND + END;	// send terminate command to P2
	wait(NULL);
	exit(status); //close server!
}

void request_handler(string data_path, int ipc_fd, int id, char* ip, char* req) {

	if(!fork()) {

		Named_pipe n_pipe = Named_pipe(NAMED_PIPE_PATH);
		n_pipe << NEW_FD_COMMAND + SEPARATOR + req + END;

		bool is_send_success = Utility::send_fd(ipc_fd, id);
		if(is_send_success)
			cout << "FD sended!" << endl;
		else
			cout << "error sending FD to P2" << endl;

		find_and_send(data_path, stoi(string(req)), n_pipe);

		exit(0); // and this is my zombie :D

	}
	
}

void listen_for_clients(string data_path, int ipc_fd, int listener, char* listener_port) {
	fd_set master;    // master file descriptor list
    fd_set read_fds;  // temp file descriptor list for select()
    int fdmax;        // maximum file descriptor number

    socklen_t addrlen;
    struct sockaddr_storage remoteaddr; // client address
    int newfd;        // newly accept()ed socket descriptor
    char remoteIP[INET6_ADDRSTRLEN];
    char buf[MAX_DATA_SIZE];    // buffer for client data
    memset(buf, '\0', MAX_DATA_SIZE);
    int nbytes;

    // clear the master and temp sets
    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    // add the listener to the master set
    FD_SET(listener, &master);
	FD_SET(STDIN, &master);

    // keep track of the biggest file descriptor
    fdmax = listener; // so far, it's this one

    // main loop
    for(;;) {
        read_fds = master; // copy it
        if (select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1) {
            exit(4);
        }

        // run through the existing connections looking for data to read
        for(int i = 0; i <= fdmax; i++) {
            if (FD_ISSET(i, &read_fds)) { // we got one!!
				if (i == STDIN) {

					string input;
					cin >> input;

					quit(0);

					// if(input == QUIT)
					// 	quit(0);

				} else if (i == listener) {
                    // handle new connections
                    addrlen = sizeof remoteaddr;
                    newfd = accept(listener,
                        (struct sockaddr *)&remoteaddr,
                        &addrlen);

                    if (newfd == -1) {
						cerr << "accept" << endl;
                    } else {
                        FD_SET(newfd, &master); // add to master set
                        if (newfd > fdmax) {    // keep track of the max
                            fdmax = newfd;
                        }
                    }
                } else {
                    // handle data from a client
                    if ((nbytes = recv(i, buf, sizeof buf, 0)) <= 0) {
                        // got error or connection closed by client
                        if (nbytes == 0) {
                            // connection closed
                            printf("selectserver: socket %d hung up\n", i);
                        } else {
							cerr << "recv" << endl;
                            // error("recv");
                        }
                        close(i); // bye!
                        FD_CLR(i, &master); // remove from master set
                    } else {

                        char* ip = (char*)inet_ntop(remoteaddr.ss_family,
                            get_in_addr((struct sockaddr*)&remoteaddr),
                            remoteIP, INET6_ADDRSTRLEN);

                        request_handler(data_path, ipc_fd, i, ip, buf);
                        memset(buf, '\0', MAX_DATA_SIZE);

                    }
                } // END handle data from client
            } // END got new incoming connection
        } // END looping through file descriptors
    } // END for(;;)--and you thought it would never end!
}

int main(int argc, char *argv[]) {

    if (!(argc == 3)) {
		cout << "usage: ./server data_path port" << endl;
        exit(1);
    }
	char* data_path = argv[1];
	char* listener_port = argv[2];

	int ipc_fd[2];	// use for IPC (Server -> P2)
	socketpair(AF_LOCAL, SOCK_STREAM, 0, ipc_fd);
	Named_pipe named_pipe = Named_pipe(NAMED_PIPE_PATH);

	// create P2 proc
	if(!fork()) {
		close(ipc_fd[0]);
		main_p2(ipc_fd[1], named_pipe);
		exit(0);
	} else {
		close(ipc_fd[1]);

		int listener = create_listener_fd(listener_port);
		// int new_fd = accept_client(listener);

		listen_for_clients(data_path, ipc_fd[0], listener, listener_port);

		wait(NULL);
	}

}
