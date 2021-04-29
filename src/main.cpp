#include <iostream>
#include <pthread.h>
#include <chrono>
#include <queue>
#include <vector>
#include <fstream>
#include "LinkedList/linked_list.hpp"
#include<unistd.h>


// -------- Global variables --------
pthread_mutex_t g_mutex;
std::queue<int> g_buffer;	// shared buffer between the 2 threads
const int g_buffer_limit = 10;	// max number of elements to store in the buffer
unsigned g_sleep = 1;	// sleep duration in seconds
std::vector<int> g_input_data = {1, 6, 124, 691, -12, -142, 1242, 1514, 12566, 1205, -2144, 51324, 9141, -2481, 4124};
LinkedList g_output_data;
bool g_prod_done = false;
std::ofstream g_log_file;

// -------- Consumer thread function --------
void* consumer(void* ptr) {
	while (true) {
		if (g_prod_done && g_buffer.empty()) return NULL;

		 //if the buffer is empty, wait for the producer to add some more data to it
		while (g_buffer.empty())
			sleep(g_sleep);
		
		// Acquire lock to read from the shared buffer
		pthread_mutex_lock(&g_mutex);
		int data = g_buffer.front(); // read the first element from the queue
		g_buffer.pop();	// and remove it
		g_log_file << "Consumed: " << data << std::endl;
		pthread_mutex_unlock(&g_mutex); // the lock is no longer needed as we're not accessing shared resources anymore

		g_output_data.sortedInsert(data);
	}
}

// -------- Producer thread function --------
void* producer(void* ptr) {
	while (true) {
		if (g_input_data.size() == 0) { 
			g_prod_done = true;
			return NULL;
		}

		pthread_mutex_lock(&g_mutex);
		int data = g_input_data.front();
		g_buffer.push(data); // read the first element from the input vector
		g_input_data.erase( g_input_data.begin() );	// and remove it
		g_log_file << "Produced: " << data << std::endl;
		pthread_mutex_unlock(&g_mutex);


		// if the buffer is full, wait for the consumer to take some data out of it
		while (g_buffer.size() >= g_buffer_limit)
			sleep(g_sleep);
	}
}

// -------- Main thread function --------
int main() {
	g_log_file.open("threads.log");

	pthread_t thread1, thread2;

	std::cout << "Input data: " << std::endl;
	for (auto it = g_input_data.begin(); it != g_input_data.end(); it++) std::cout << *it << " ";
	std::cout << std::endl << std::endl;

	pthread_create(&thread1, NULL, producer, NULL);
	std::cout << "S-a creat firul producer " << std::endl;
	pthread_create(&thread2, NULL, consumer, NULL);
	std::cout << "S-a creat firul consumer " << std::endl;
	
	pthread_join(thread1, NULL);
	
	pthread_join(thread2, NULL);
	
	
	std::cout << "Output data: " << std::endl;
	g_output_data.print();
	std::cout << std::endl;

	pthread_exit(NULL);
	g_log_file.close();
	return 0;
}
