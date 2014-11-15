
all: sockets

sockets:
	g++ server.cpp -o server
	g++ client.cpp -o client
	./server&
	./client;
	rm server client;

