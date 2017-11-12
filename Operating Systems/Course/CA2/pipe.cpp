#include "pipe.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

#include <string>

using namespace std;

Unnamed_pipe::Unnamed_pipe() {
	int fd[2];
	pipe(fd);
	this->p1_fd = fd[0];
	this->p2_fd = fd[1];
    this->main_fd = -1;
}

Unnamed_pipe::Unnamed_pipe(const Unnamed_pipe &obj) {
    int fd[2];
    pipe(fd);
    this->p1_fd = fd[0];
    this->p2_fd = fd[1];
    this->main_fd = -1;
}

Unnamed_pipe::~Unnamed_pipe() {
    close(p1_fd);
    close(p2_fd);
}

Unnamed_pipe& Unnamed_pipe::operator<<(const string& input) {

    if(main_fd == -1) {
        main_fd = p2_fd;
    }

    write(p2_fd, input.c_str(), input.size());
    return *this;
}

Unnamed_pipe& Unnamed_pipe::operator>>(string& output) {

    if(main_fd == -1) {
        main_fd = p1_fd;
    }

    char buf[MAX_BUF_SIZE];
    memset(buf, '\0', MAX_BUF_SIZE);
    read(p1_fd, buf, MAX_BUF_SIZE);
    output = string(buf);
    return *this;
}


Unnamed_pipe& Unnamed_pipe::operator<<(const int& input) {
	operator<<(to_string(input));
    return *this;
}

Unnamed_pipe& Unnamed_pipe::operator>>(int& output) {
	string res;
	operator>>(res);
	output = stoi(res);
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
    memset(buf, '\0', MAX_BUF_SIZE);
    read(fd, buf, MAX_BUF_SIZE);
    output = string(buf);
    close(fd);
    return *this;
}

Named_pipe& Named_pipe::operator<<(const int& input) {
	operator<<(to_string(input));
    return *this;
}

Named_pipe& Named_pipe::operator>>(int& output) {
	string res;
	operator>>(res);
	output = stoi(res);
    return *this;
}
