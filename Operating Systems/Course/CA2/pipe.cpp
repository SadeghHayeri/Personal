#include "pipe.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#include <string>

#include "structs.h"

using namespace std;

Pipe::Pipe() {
	int fd[2];
	pipe(fd);
	this->input_fd = fd[0];
	this->output_fd = fd[1];
}

Pipe& Pipe::operator<<(const string& input) {
    write(this->output_fd, input.c_str(), input.size());
    return *this;
}

Pipe& Pipe::operator>>(string& output) {
    char buf[MAX_BUF_SIZE];
    read(this->input_fd, buf, MAX_BUF_SIZE);
    output = string(buf);
    return *this;
}