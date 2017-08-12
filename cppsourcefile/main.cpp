#include "Poco/ByteOrder.h"
#include "Poco/Net/IPAddress.h"
#include  "Poco/Net/ServerSocket.h"
#include  "Poco/Net/TCPServer.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"
#include "Poco/Types.h"
#include <iostream>
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include "Poco/ByteOrder.h"
#pragma comment(lib, "Ws2_32.lib")
typedef Poco::AutoPtr <Poco::Net::TCPServerParams> Ptr;
using namespace std;


//Create new connection for each Incoming Requests
class createconnection : public Poco::Net::TCPServerConnection
{
public:
	 createconnection(const Poco::Net::StreamSocket& s):Poco::Net::TCPServerConnection(s) {}; //functors
	
// Run() method inherited from the runnable class which is a entry point for each thread.
	void run() 
	{
		cout << "New connection from: " << socket().peerAddress().host().toString() << endl << flush;
		bool active = true;
		Poco::Timespan timeOut(100, 0);
		unsigned char Buffer[1000];
		while (active) {
			if (socket().poll(timeOut, Poco::Net::Socket::SELECT_READ) == false) {
				cout << "No string Recieved till Timeout span . Client Active status :"<< active  << flush;
			}
			else {
				cout << " Client Message : "<< flush;
				int recBytes = -1;

				try {
					recBytes = socket().receiveBytes(Buffer, sizeof(Buffer));
				}
				catch (Poco::Exception& exception) {
					//Handle network errors.
					cerr << "Network error: " << exception.displayText() << endl;
					active= false;
				}


				if (recBytes == 0) {
					cout << "Client closes connection!" << endl << flush;
					active = false;
				}
				else {
					cout << "Receiving recBytes: " << recBytes << endl << flush;
					cout <<"String Recieved : " <<Buffer << endl;
				}
			}
		}
		cout << "Connection finished!" << endl << flush;
	}
};
	





int main(int argc, char** argv)
{       //Setting Server IP address 
	//For Windows OS IPAddress("127.0.0.1") might not work hence use of inet_addr is mandatory
        Poco::UInt32 ip = inet_addr("127.0.0.1");
	Poco::Net::IPAddress ip1(&ip, sizeof(ip));
	Poco::Net::SocketAddress ss(ip1, 21);
	Poco::Net::ServerSocket s (ss,20);
	Ptr p = new Poco::Net::TCPServerParams();

	//Setting Server Parameters This will allow scaling .

	p->setMaxThreads(64);
	p->setMaxQueued(64);
	p->setThreadIdleTime(50);

	//Setting TcpServer constructor

	Poco::Net::TCPServer t(new Poco::Net::TCPServerConnectionFactoryImpl<createconnection>(),s,p);

	//Starting TCP Server
	t.start();
	cout << "Server Started" << endl;
	cout << "Ready To Accept the connections" << endl;
	while (1);
	
}
