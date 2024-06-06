#include<iostream>

#include "helpmain.h"

using namespace std;

int main(int argc, char *argv[]){

    if(argc<11){

        cout<<"Wrong input (monitor server).";
        return -1;
    }


    int i=1;

    int port;
    int numThreads;
    int socketbufferSize;
    int cyclicBufferSize;
    int sizeOfBloom;

    string paths[argc-11];

    while(i<=9){

        if(!strcmp(argv[i],"-p")){

            port=atoi(argv[i+1]);

        }else if(!strcmp(argv[i],"-t")){

            numThreads=atoi(argv[i+1]);
            
        }else if(!strcmp(argv[i],"-b")){

            socketbufferSize=atoi(argv[i+1]);

        }else if(!strcmp(argv[i],"-c")){

            cyclicBufferSize=atoi(argv[i+1]);

        }else if(!strcmp(argv[i],"-s")){

            sizeOfBloom=atoi(argv[i+1]);

        }else{

            cout<<endl<<"Wrong input (monitorServer)."<<endl;
            return 0;
        }

        i=i+2;
    }
        
    int size=0;
    for(i=0; i<(argc-11); i++){

        paths[i]=string(argv[11+i]);
        size++;
    }

    monitorServer(port,numThreads,socketbufferSize,cyclicBufferSize,sizeOfBloom,paths,size);

    return 0;
}