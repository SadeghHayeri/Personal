#include "utility.h"

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <iterator>

#include <sys/socket.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

namespace Utility {
	bool is_regular_file(const string& path) {
		struct stat path_stat;
	    stat(path.c_str(), &path_stat);
	    return S_ISREG(path_stat.st_mode);
	}

	vector<string> get_files_and_directories(const string& path) {
		vector<string> result;
	    DIR* dirp = opendir(path.c_str());
	    struct dirent * dp;
	    while ((dp = readdir(dirp)) != NULL)
	    	if(	dp->d_name[0] != '.')
	        	result.push_back(dp->d_name);
	    closedir(dirp);
	    return result;
	}

	vector<string> get_directories(const string& path) {
		vector<string> result;
		vector<string> all = get_files_and_directories(path);
		for(const string& s : all)
			if(!is_regular_file(path + '/' + s))
				result.push_back(s);
		return result;
	}

	vector<string> get_files(const string& path) {
		vector<string> result;
		vector<string> all = get_files_and_directories(path);
		for(string s : all)
			if(is_regular_file(path + '/' + s))
				result.push_back(s);
		return result;
	}

	bool send_fd(int sock_fd, int fd) {
		char buf[16];
		ssize_t buflen = sizeof(buf);

		ssize_t     size;
		struct msghdr   msg;
		struct iovec    iov;
		union {
				struct cmsghdr  cmsghdr;
				char        control[CMSG_SPACE(sizeof (int))];
		} cmsgu;
		struct cmsghdr  *cmsg;

		iov.iov_base = buf;
		iov.iov_len = buflen;

		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;

		if (fd != -1) {
				msg.msg_control = cmsgu.control;
				msg.msg_controllen = sizeof(cmsgu.control);

				cmsg = CMSG_FIRSTHDR(&msg);
				cmsg->cmsg_len = CMSG_LEN(sizeof (int));
				cmsg->cmsg_level = SOL_SOCKET;
				cmsg->cmsg_type = SCM_RIGHTS;

				printf ("passing fd %d\n", fd);
				*((int *) CMSG_DATA(cmsg)) = fd;
		} else {
				msg.msg_control = NULL;
				msg.msg_controllen = 0;
				printf ("not passing fd\n");
		}

		size = sendmsg(sock_fd, &msg, 0);

		if (size < 0)
				perror ("sendmsg");
		return size;
	}

	int recv_fd(int sock_fd) {
		char buf[16];
		ssize_t bufsize = sizeof(buf);
    ssize_t     size;

    struct msghdr   msg;
    struct iovec    iov;
    union {
        struct cmsghdr  cmsghdr;
        char        control[CMSG_SPACE(sizeof (int))];
    } cmsgu;
    struct cmsghdr  *cmsg;

    iov.iov_base = buf;
    iov.iov_len = bufsize;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsgu.control;
    msg.msg_controllen = sizeof(cmsgu.control);
    size = recvmsg (sock_fd, &msg, 0);
    if (size < 0) {
        perror ("recvmsg");
        exit(1);
    }
    cmsg = CMSG_FIRSTHDR(&msg);
    if (cmsg && cmsg->cmsg_len == CMSG_LEN(sizeof(int))) {
        if (cmsg->cmsg_level != SOL_SOCKET) {
            fprintf (stderr, "invalid cmsg_level %d\n",
                 cmsg->cmsg_level);
            exit(1);
        }
        if (cmsg->cmsg_type != SCM_RIGHTS) {
            fprintf (stderr, "invalid cmsg_type %d\n",
                 cmsg->cmsg_type);
            exit(1);
        }

				return *((int *) CMSG_DATA(cmsg));
    } else
        return -1;
	}
}
