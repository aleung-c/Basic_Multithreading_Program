# Basic_Multithreading_Program
A small program that uses the pthread lib.

This small program is a test program for using the pthreadlib. Indeed, it uses several functions from the lib to make some 
senseless calculations.
If you launch the program, you will notice that the threads are locked by a mutex, which make each thread work one after 
the other.

In this way, the threads are indeed useless. However, the point was to have control over the threads behavior. 


Removing the mutex in this code give more meaning to the program, as all the calculations are made in parallel, which is faster. 
However, the order of the threads then become uncontrolled, and the program makes the so called "data race", 
which can lead to elusive errors and behavior.

Then again, this program was a way for me to work with and understand threaded programming.
