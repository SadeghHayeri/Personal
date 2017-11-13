void search_on_file(Unnamed_pipe& pipe) {

	string data;
	pipe >> data;
	auto recived_data = Utility::split(data, SEPARATOR);
	string path = recived_data[0];
	int id = stoi(recived_data[1]);

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

	pipe << to_string(all_amount);
	file.close();
}

void find_all_in_directory(Unnamed_pipe& pipe) {

	string data;
	pipe >> data;
	auto recived_data = Utility::split(data, SEPARATOR);
	string path = recived_data[0];
	int id = stoi(recived_data[1]);

	vector<string> files = Utility::get_files(path);
	vector<string> directories = Utility::get_directories(path);

	int num_of_pipe = files.size() + directories.size();
	int pipe_index = 0;
	vector<Unnamed_pipe> pipes(num_of_pipe, Unnamed_pipe());

	for(string directory : directories)
		if(!fork()) {
			pipes[pipe_index] << path + '/' + directory + SEPARATOR + to_string(id);
			find_all_in_directory(pipes[pipe_index]);
			exit(0);
		} else
			pipe_index++;

	for(string file : files)
		if(!fork()) {
			pipes[pipe_index] << path + "/" + file + SEPARATOR + to_string(id);
			search_on_file(pipes[pipe_index]);
			exit(0);
		} else
			pipe_index++;

	for(int i = 0; i < num_of_pipe; i++)
		wait(NULL);

	long long all_amount = 0;
	for(Unnamed_pipe& child_pipe : pipes) {
		string amount_string;
		child_pipe >> amount_string;

		// cout << "::" << path << " - " << amount_string << "::" << endl;
		all_amount += stoll(amount_string);
	}

	pipe << to_string(all_amount);
}

void find_and_send(string path, int id, Named_pipe callback_pipe) {

	Unnamed_pipe pipe = Unnamed_pipe();
	pipe << path + SEPARATOR + to_string(id);
	find_all_in_directory(pipe);

	string result;
	pipe >> result;

	cout << "result search for id " << id << " => " << result << endl;

	callback_pipe << RESULT_READY + SEPARATOR + to_string(id) + SEPARATOR + result + END;
}
