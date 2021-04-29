build:
	g++ src/main.cpp src/LinkedList/linked_list.cpp -O3 -o pcthread -pthread -lpthread

delete:
	rm pcthread
	rm threads.log
