#ifndef __PIPE_H__
#define __PIPE_H__

#include <string>

class Pipe {
public:
	virtual Pipe& operator<<(const std::string& input) = 0;
	virtual Pipe& operator>>(std::string& output) = 0;	
};

class Unamed_pipe : Pipe {
public:
	Unamed_pipe();
	~Unamed_pipe();

	Unamed_pipe& operator<<(const std::string& input);
	Unamed_pipe& operator>>(std::string& output);	

private:
	int input_fd;	
	int output_fd;
};

class Named_pipe : Pipe {
public:
	Named_pipe(std::string _path);

	Named_pipe& operator<<(const std::string& input);
	Named_pipe& operator>>(std::string& output);
private:
	std::string path;
};

#endif //__PIPE_H__