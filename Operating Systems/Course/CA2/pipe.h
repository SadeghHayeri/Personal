#ifndef __PIPE_H__
#define __PIPE_H__

#include <string>

#define MAX_BUF_SIZE 1000

using namespace std;

class Pipe {
public:
	virtual Pipe& operator<<(const std::string& input) = 0;
	virtual Pipe& operator<<(const int& input) = 0;
	virtual Pipe& operator>>(std::string& output) = 0;
	virtual Pipe& operator>>(int& output) = 0;
};

class Unnamed_pipe : Pipe {
public:
	Unnamed_pipe();
	Unnamed_pipe(const Unnamed_pipe &obj);
	~Unnamed_pipe();

	Unnamed_pipe& operator<<(const std::string& input);
	Unnamed_pipe& operator<<(const int& input);
	Unnamed_pipe& operator>>(std::string& output);
	Unnamed_pipe& operator>>(int& output);

private:
	int p1_fd;
	int p2_fd;
	int main_fd;
};

class Named_pipe : Pipe {
public:
	Named_pipe(std::string _path);

	Named_pipe& operator<<(const std::string& input);
	Named_pipe& operator<<(const int& input);
	Named_pipe& operator>>(std::string& output);
	Named_pipe& operator>>(int& output);
private:
	std::string path;
};

#endif //__PIPE_H__
