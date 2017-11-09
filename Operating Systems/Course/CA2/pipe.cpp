#include "pipe.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <string>

#include "structs.h"

using namespace std;

Unamed_pipe::Unamed_pipe() {
	int fd[2];
	pipe(fd);
	this->input_fd = fd[0];
	this->output_fd = fd[1];
}

Unamed_pipe::~Unamed_pipe() {
    close(this->input_fd);
    close(this->output_fd);
}

Unamed_pipe& Unamed_pipe::operator<<(const string& input) {
    write(this->output_fd, input.c_str(), input.size());
    return *this;
}

Unamed_pipe& Unamed_pipe::operator>>(string& output) {
    char buf[MAX_BUF_SIZE];
    read(this->input_fd, buf, MAX_BUF_SIZE);
    output = string(buf);
    return *this;
}

///////////////////////

Named_pipe::Named_pipe(string _path) {
    mkfifo(_path.c_str(), 0666);
    this->path = _path;
}


Named_pipe& Named_pipe::operator<<(const string& input) {
    int fd = open(this->path.c_str(), O_WRONLY);
    write(fd, input.c_str(), input.size());
    close(fd);
    return *this;
}

Named_pipe& Named_pipe::operator>>(string& output) {
    int fd = open(this->path.c_str(), O_RDONLY);
    char buf[MAX_BUF_SIZE];
    read(fd, buf, MAX_BUF_SIZE);
    output = string(buf);
    close(fd);
    return *this;
}