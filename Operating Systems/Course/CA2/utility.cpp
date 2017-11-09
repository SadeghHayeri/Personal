#include "utility.h"

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <algorithm>
#include <iterator>

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
	    	if(	(strcmp(dp->d_name, ".") != 0) &&
	    		(strcmp(dp->d_name, "..") != 0))
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
}