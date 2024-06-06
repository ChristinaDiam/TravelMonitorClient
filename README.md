# TravelMonitorClient #

This Project named travelMonitorClient, is about a program which receives requests from citizens who want to travel to other countries, checks whether they have made the appropriate vaccinations, and approves whether a traveler is allowed to enter a country.


**The Project consists of two parts:**
	
The first part is about the parent process (TravelMonitorClient) and contains the following files: main.cpp, bloomfilter.cpp, bloomfilter.h, hash.cpp, hash.h,
helpmain.cpp, helpmain.h, list.cpp, list.h, child.cpp, countries.cpp, countires.h, child.h and a Makefile.

The second part is for the child process (MonitorServer) and contains the following files: main.cpp, bloomfilter.cpp, bloomfilter.h, hash.cpp, hash.h,
citizen.cpp, citizen.h, helpmain.cpp, helpmain.h, helphelpmain.cpp, helphelpmain.h list.cpp, list.h, skiplist.cpp, skiplist.h,
countries.cpp, countires.h, thread.cpp, thread.h, info.cpp, info.h, cyclic.cpp, cyclic.h and a Makefile.

**A few things about the program**

The program, by calling the travelmonitorClient function ,in the parent process part, creates a list of paths for the files, which will then be used to initialize the citizens. Then it creates the child and sockets for communication with the child process, reads and stores the bloomfilter sent by the child.
At the end it closes the sockets.

The child process part, via the monitorServer function, creates the sockets on its own side for communication with the parent. Then, it builds a list of the completed path for each text file, which it will use for initializing the citizens.
Then creates the threads through which it initializes the citizens that gets from the text files. After that, it sends the bloomfilter to the parent.
Finally, destroys the threads that created and closes the sockets.


### Compile and running ###

There is a Makefile for each part of the program, and a bash script which joins these two Makefiles and makes it easier to compile and run the program.

To compile the program type: **bash TheBigMake.sh make**.

To run the program type: **bash TheBigMake.sh make run**.  
*(the bash script will automatically run the program using standard data).*

To clean up the temporary files type: **bash TheBigMake.sh make clean**.