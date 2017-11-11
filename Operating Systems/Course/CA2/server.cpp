#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <unistd.h>

#include <time.h>

#include "utility.h"
#include "pipe.h"

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

	cout << ">>" << path << " - " << all_amount << "<<" << endl;

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

		cout << "::" << path << " - " << amount_string << "::" << endl;
		all_amount += stoll(amount_string);
	}

	pipe << to_string(all_amount);
}

#include <time.h>

int main() {

	Unnamed_pipe p = Unnamed_pipe();
	find_all_in_directory("Data 2", 76767, p);

	string res;
	p >> res;
	cout << "result: " << res << endl;

}