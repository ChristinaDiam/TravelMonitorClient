#valgrind ./travelMonitor –m 10 -b 1000 -s 100000 -i input_dir# set compiler options here
CPPFLAGS=-g -Wall -g3 -std=c++11 -pthread

# set the name of the executable file to compile here
program=MonitorServer

# list object files needed to compile the program
objects=main.o helpmain.o bloomfilter.o citizen.o countries.o hash.o list.o helphelpmain.o skiplist.o cyclicbuf.o thread.o info.o


# this makes the program. 
$(program) : $(objects)
	g++ $(CPPFLAGS) $(objects) -o $(program) 


main.o: helpmain.h
helpmain.o: helpmain.h
bloomfilter.o: bloomfilter.h
citizen.o: citizen.h
countries.o: countries.h
hash.o: hash.h
list.o: list.h
helphelpmain.o: helphelpmain.h
skiplist.o: skiplist.h
cyclicbuf.o: cyclicbuf.h
thread.o: thread.h
info.o: info.h


# this allows to quickly remove all generated files with 'make clean'
clean:
	rm $(program) $(objects)

# run the program with 'make run'.
run: $(program)
	./$(program) $(args)


# run the program with 'valgrind'.
valgrind: $(program)
	valgrind ./$(program) $(args)