#include "client_socket.h"
#include "client.h"
#include <cstdlib>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "valid operation: " << argv[0] << " [server address] [server port]\n";
    exit(-1);
  }
  
  ClientSocket socket(string(argv[1]), Tools::mystoi(argv[2]));
  cout << "# connection established\n";
  
  Client client( socket );

  // string line;
  // while (getline(cin, line)) {
  //   if (line == ":q")
  //     break;
  //   socket.send(line);
  //   cout << socket.receive() << endl;
  //   socket.status();
  // }
  
  return 0;
}
