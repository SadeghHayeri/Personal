#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <vector>
#include <string>

namespace Utility {
	bool is_regular_file(const std::string& path);
	std::vector<std::string> get_files_and_directories(const std::string& path);
	std::vector<std::string> get_directories(const std::string& path);
	std::vector<std::string> get_files(const std::string& path);
}

#endif //__UTILITY_H__