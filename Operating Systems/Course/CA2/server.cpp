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

using namespace std;

void search_on_file(string path, int id, Unnamed_pipe& pipe) {
	fstream file;
	file.open(path);

	long long all_amount = 0;
	while(!file.eof()) {
		int tmp_id;
		string tmp_date;
		long long tmp_amount;

		file >> tmp_id >> tmp_date >> tmp_amount;

		if(tmp_id == id)
			all_amount += tmp_amount;
	}

	pipe << to_string(all_amount);
	file.close();
}

void find_all_in_directory(string path, int id, Unnamed_pipe& pipe) {
	vector<string> files = Utility::get_files(path);
	vector<string> directories = Utility::get_directories(path);

	int num_of_pipe = files.size() + directories.size();
	int pipe_index = 0;
	vector<Unnamed_pipe> pipes(num_of_pipe, Unnamed_pipe());

	for(string directory : directories)
		if(!fork()) {
			find_all_in_directory(path + '/' + directory, id, pipes[pipe_index]);
			exit(0);
		} else
			pipe_index++;

	for(string file : files)
		if(!fork()) {
			search_on_file(path + "/" + file, id, pipes[pipe_index]);
			exit(0);
		} else
			pipe_index++;

	for(int i = 0; i < num_of_pipe; i++)
		wait(NULL);

	long long all_amount = 0;
	for(Unnamed_pipe& child_pipe : pipes) {
		string amount_string;
		child_pipe >> amount_string;

		// cout << "::" << path << " - " << amount_string << "::" << endl;
		all_amount += stoll(amount_string);
	}

	pipe << to_string(all_amount);
}

void find_and_send(string path, int id, Named_pipe callback_pipe) {

	Unnamed_pipe pipe = Unnamed_pipe();
	find_all_in_directory(path, id, pipe);

	string result;
	pipe >> result;

	cout << "result search for id " << id << " => " << result << endl;

	callback_pipe << RESULT_READY + SEPARATOR + to_string(id) + SEPARATOR + result + END;
}

void main_p2(int ipc_fd, Named_pipe& named_pipe) {
	vector< pair<int,int> > requests_queue;

	string input;
	do {

		string buf;
		named_pipe >> buf;
		input += buf;

		// cout << "buf: " << input << endl;

		bool end_found = input.find(END) != -1;
		if(!end_found)
			continue;

		string msg = input.substr(0, input.find(END));
		input = input.substr(input.find(END) + END.size());

		// New msg!
		cout << "::" << msg << endl;
		auto data = Utility::split(msg, SEPARATOR);

		if(data[0] == NEW_FD_COMMAND) {
			int id = stoi(data[1]);
			int fd = Utility::recv_fd(ipc_fd);

			requests_queue.push_back( make_pair(id,fd) );
		}

		if(data[0] == RESULT_READY) {
			int id = stoi(data[1]);
			string result = data[2];

			for (int i = 0; i < requests_queue.size(); i++) {
				if(requests_queue[i].first == id) {
					send(requests_queue[i].second, result.c_str(), result.size(), 0);
					close(requests_queue[i].second);
					requests_queue.erase(requests_queue.begin() + i--);
				}
			}
		}

		if(data[0] == EXIT_COMMAND) {
			cout << "P2 terminated!" << endl;
			exit(0);
		}

	} while(true);
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
	// wait(NULL);

}

void quit(int status) {
	Named_pipe p = Named_pipe(NAMED_PIPE_PATH);
	p << EXIT_COMMAND + END;	// send terminate
	wait(NULL);
	exit(status); //close server!
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
