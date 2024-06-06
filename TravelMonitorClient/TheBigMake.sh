#!/bin/bash

if [[ ($# -eq 1 || $# -eq 2 ) ]];
then
    
    if [ $1 == "make" ];
    then

        #if we have only one argument (command is "make")
        if [ $# -eq 1 ];
        then

            cd travelMonitorClient
            make
            cd ../
            cd MonitorServer
            make
            cd ../

        #else we have two arguments (command is "make run", "make clean" or "make valgrind")
        else

            if [ $2 == "run" ];
            then

                cd travelMonitorClient
                make run
                cd ../
            
            elif [ $2 == "clean" ]
            then

                cd travelMonitorClient
                make clean
                cd ../
                cd MonitorServer
                make clean
                cd ../

            elif [ $2 == "valgrind" ]
            then

                cd travelMonitorClient
                make valgrind
                cd ../

            else
                echo "Wrong input.\n"
                exit 0
            fi
        fi

    else
        echo "Wrong input.\n"
        exit 0
    fi

else
    echo "Wrong input.\n"
    exit 0
fi