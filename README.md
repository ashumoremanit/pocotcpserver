# pocotcpserver
A Multithreaded TCP Server using Poco C++ library  

The TCPServer is capable of handling multiple connections concurrently using 
thread pools . The incoming connections are first placed to the Queue then
Each connection from Queue is assigned a separate thread from the pool.




