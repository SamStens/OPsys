Producer-Consumer Problem Solution in C/C++

Introduction
------------------------
This repository contains a solution for the classic producer-consumer problem implemented
in C/C++ for Linux/Unix systems. The code demonstrates the use of threads, semaphores,
and shared memory to synchronize the producer and consumer processes.

Requirements
---------------------------
- C/C++ compiler (e.g., GCC)
- Linux/Unix environment
- POSIX Threads (pthread) library
- Semaphore and shared memory support

How to Compile and Run
------------------------------
To compile the producer and consumer programs, follow these steps:
$ gcc producer.c -pthread -lrt -o producer
$ gcc consumer.c -pthread -lrt -o consumer
$ ./producer & ./consumer &


Code Explanation

Producer Program (producer.c):
------------------------------
The producer program generates items and places them in a shared buffer.
It uses semaphores for synchronization, ensuring mutual exclusion.
A separate thread is used to simulate the producer's behavior.

Consumer Program (consumer.c):
-------------------------------
The consumer program picks up items from the shared buffer.
It also uses semaphores and a separate thread for synchronization.
Proper mutual exclusion is maintained to avoid conflicts.
