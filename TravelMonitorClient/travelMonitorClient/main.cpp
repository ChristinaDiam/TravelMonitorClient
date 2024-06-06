#include<iostream>
#include<cstring>

#include "helpmain.h"

using namespace std;

int main(int argc, char *argv[]){

    int i=1;
    int numMonitors;
    int socketbufferSize;
    int sizeOfBloom;
    int numThreads;
    int cyclicBufferSize;
    
    string input_dir;

    if(argc==13){

        while(i<12){

            if(!strcmp(argv[i],"-m")){

                numMonitors=atoi(argv[i+1]);

            }else if(!strcmp(argv[i],"-b")){

                socketbufferSize=atoi(argv[i+1]);

            }else if(!strcmp(argv[i],"-s")){

                sizeOfBloom=atoi(argv[i+1]);

            }else if(!strcmp(argv[i],"-i")){

                input_dir=argv[i+1];

            }else if(!strcmp(argv[i],"-c")){

                cyclicBufferSize=atoi(argv[i+1]);

            }else if(!strcmp(argv[i],"-t")){

                numThreads=atoi(argv[i+1]);

            }else{

                cout<<endl<<"Wrong input1."<<endl;
                return 0;
            }
            
            i=i+2;      
        }

    }else{

        cout<<endl<<"Wrong input2."<<endl;
        return 0;
    }

    travelmonitor(numMonitors,socketbufferSize,sizeOfBloom,input_dir,cyclicBufferSize,numThreads);

    return 0;
}