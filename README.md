# Threads-And-Numbers
A program that orders numbers with the help of threads.
The producer thread reads the input data from a given array of randomly generated numbers, and puts it into a buffer (a queue accessed with a mutex by each thread), from where the consumer thread will read it and do a sorted insert into a custom linked list.

