#include<iostream>
#include<cstdio>
#include<dirent.h>
#include <sys/wait.h>         /* sockets */
#include <sys/types.h>         /* sockets */
#include <sys/socket.h>         /* sockets */
#include <netinet/in.h>         /* internet sockets */
#include <netdb.h>             /* gethostbyaddr */
#include<cstring>

#include "helpmain.h"

using namespace std;


void travelmonitor(int numMonitors, int socketbufferSize, int bloomSize, string inputDirectory,int cyclicbuffersize,int numThreads){

    //list of paths
    list *paths=new list();

    //open the directory
    DIR* dir;
    struct dirent* en;

    // ../input_dir
    string inputD="../";
    inputDirectory=inputD.append(inputDirectory);

    dir=opendir(inputDirectory.c_str());

    if(dir==NULL){

        perror("opendir");
        return;
    }


    //read the directory
    while((en=readdir(dir))!=NULL){

        int comp=strcmp(".",en->d_name);
        if(comp==0){

            continue;
        }

        comp=strcmp("..",en->d_name);
        if(comp==0){

            continue;
        }

        //making the path name: ../input_dir/<subdirectory>
        string *str1=new string(inputDirectory);
        
        string str2="/";
        str1->append(str2);

        string subdirectory(en->d_name);
        str1->append(subdirectory);

        //insert path to list
        paths->listinsert(str1);

    }

    //close the directory
    closedir(dir);


    //array of path lists
    list *arrayofpaths[numMonitors];

    int i=0;

    for(i=0; i<numMonitors; i++){

        arrayofpaths[i]=new list();
    }

    int count=0;
    listnode *tmp=paths->gethead();

    while(tmp!=NULL){

        string *curpath=(string*)tmp->getvalue();
        arrayofpaths[count]->listinsert(curpath);

        count=(count+1)%numMonitors;

        tmp=tmp->getnext();
    }


    pid_t childID[numMonitors];

    int port=50000;

    //create child
    i=0;
    while(i<numMonitors){

        childID[i]=createchild(arrayofpaths[i],port,numThreads,socketbufferSize,cyclicbuffersize,bloomSize);

        i++;
        port++;
    }


    //create sockets
    int portarray[numMonitors], sockarray[numMonitors];
    struct sockaddr_in serverarray[numMonitors];

    struct sockaddr *serverptrarray[numMonitors];
    for(i=0; i<numMonitors; i++){

        serverptrarray[i]=(struct sockaddr*)&serverarray[i];
    }
    

    struct hostent *rem;
    
    char hostname[100];
    gethostname(hostname,99);

    rem=gethostbyname(hostname);

    portarray[0]=50000;
    for(i=1; i<numMonitors; i++){

        portarray[i]=portarray[i-1]+1;
    }


    for(i=0; i<numMonitors; i++){

        serverarray[i].sin_family=AF_INET;                          /* Internet domain */
        memcpy(&serverarray[i].sin_addr, rem->h_addr, rem->h_length);
        serverarray[i].sin_port=htons(portarray[i]);                /* Server port */
    }

    //sleep for five seconds
    sleep(5);

    for(i=0; i<numMonitors; i++){

        sockarray[i]=socket(AF_INET, SOCK_STREAM, 0);

        if(connect(sockarray[i], serverptrarray[i],sizeof(serverarray[i]))<0){

            perror("connect");

        }else{

            cout<<"Connection successful."<<endl;
        }
    }


    //read bloomfilters from child
    list *bloomf=new list();

    readbloom(bloomf,sockarray,numMonitors,bloomSize);





    //close sockets
    for(i=0; i<numMonitors; i++){

        close(sockarray[i]);
    }


    //wait for child processes before destroy the pipes
    for(i=0; i<numMonitors; i++){

        pid_t result=waitpid(childID[i],NULL,0);

        if(result==-1){

            perror("Failed to waitpid");
        }
    }

}


void readbloom(list *b, int *sockarray, int numMonitors, int bloomsize){

    int i;
    for(i=0; i<numMonitors; i++){

        char *message=new char[bloomsize+1];

        *message=0;

        while(1){

            //read message from child
            read(sockarray[i],message,bloomsize);

            if(!strcmp(message,"done")){

                break;
            }

            bloomfilter *bv=new bloomfilter(bloomsize);

            //decode message from string to bloomfilter
            bv->fromstring(&message);

            b->listinsert(bv);
        }

        delete[] message;
    }
}
