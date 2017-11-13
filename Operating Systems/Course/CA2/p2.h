void main_p2(int ipc_fd, Named_pipe& named_pipe) {
	vector< pair<int,int> > requests_queue;

	string input;
	do {

		string buf;
		named_pipe >> buf;
		input += buf;

		// cout << "buf: " << input << endl;

		bool end_found = input.find(END) != -1;
		if(!end_found)
			continue;

		string msg = input.substr(0, input.find(END));
		input = input.substr(input.find(END) + END.size());

		// New msg!
		cout << "::" << msg << endl;
		auto data = Utility::split(msg, SEPARATOR);

		if(data[0] == NEW_FD_COMMAND) {
			int id = stoi(data[1]);
			int fd = Utility::recv_fd(ipc_fd);

			requests_queue.push_back( make_pair(id,fd) );
		}

		if(data[0] == RESULT_READY) {
			int id = stoi(data[1]);
			string result = data[2];

			for (int i = 0; i < requests_queue.size(); i++) {
				if(requests_queue[i].first == id) {
					send(requests_queue[i].second, result.c_str(), result.size(), 0);
					close(requests_queue[i].second);
					requests_queue.erase(requests_queue.begin() + i--);
				}
			}
		}

		if(data[0] == EXIT_COMMAND) {
			cout << "P2 terminated!" << endl;
			exit(0);
		}

	} while(true);
}
