# pocotcpserver
A Multithreaded TCP Server using Poco C++ library  

The TCPServer is capable of handling multiple connections concurrently using 
thread pools . The incoming connections are first placed to the Queue then
Each connection from Queue is assigned a separate thread from the pool.
The concurrency framework is implemented using TCPConnectionFactory ,which
creates the TCPServerConnection object using TCPServerConnectionImpl <class template> 
 template defined by the developer which also inherits the TCPServerConnection class 
 and override the Run Method which serves as the entry point for each thread .
 The functionality which each thread performs is defined in this method only .
 
The TcpServer is scalable as it allows to change the Max queue connections and Max 
thread connections parameters using TcpServerParams class while declaring the TCPServer
constructors .Once the start method is for defined TCPServer object runs ,it starts the 
TCPServer,and  creates the separate thread for listening incoming connections .




