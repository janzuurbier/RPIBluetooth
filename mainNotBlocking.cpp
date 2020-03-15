#include "BluetoothSocket.h"
#include <unistd.h>
#include <cstdlib>
using namespace std;

int main() {
	//maak het device discoverable voor beperkte tijd.
	//zodat het gevonden kan worden in een device-scan
	system("sudo hciconfig hci0 piscan");
	
	BluetoothServerSocket serversock(2, 1);  //2 is het channel-number
	cout << "listening" << endl;
	while(true) {
		BluetoothSocket* clientsock = serversock.accept();
		cout << "accepted from " << clientsock->getForeignAddress().getAddress() << endl;
		MessageBox& mb = clientsock->getMessageBox();
			
		string input;
		while(mb.isRunning()) {
			input = mb.readMessage();  //blokkeert niet
			if(input != "") cout << endl << input << endl;
			//doe andere dingen.
			cout << ".";
			cout.flush();
			usleep(500000); // wacht 500 ms
		}	
		
		clientsock->close();
			
	}
}
	