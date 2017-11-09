#ifndef __PIPE_H__
#define __PIPE_H__

#include <string>

class Pipe {
public:
	Pipe();

	Pipe& operator<<(const std::string& input);
	Pipe& operator>>(std::string& output);

private:
	int output_fd;
	int input_fd;
};

#endif //__PIPE_H__