#include<iostream>
#include<string>
#include<cstring>
#include<cstdlib>
#include<cstdio>

#include "child.h"

using namespace std;

pid_t createchild(list *paths, int port, int numThreads, int socketBufferSize, int cyclicBufferSize, int sizeOfBloom){

    pid_t childpid;
    childpid=fork();

    if(childpid==-1){

        perror("Failed to fork");
        return -1;
    }


    if(childpid==0){

        int i;

        string p=to_string(port);
        string nThreads=to_string(numThreads);
        string sbuffersize=to_string(socketBufferSize);
        string cbuffersize=to_string(cyclicBufferSize);
        string sofbloom=to_string(sizeOfBloom);

        char *cmd="../MonitorServer/MonitorServer";

        char *argv[12+paths->getcounter()];
        argv[0]="../MonitorServer/MonitorServer";

        argv[1]="-p";

        char port_c[p.size()+1];
        strcpy(port_c,p.c_str());
        argv[2]=port_c;

        argv[3]="-t";

        char threads_c[nThreads.size()+1];
        strcpy(threads_c,nThreads.c_str());
        argv[4]=threads_c;

        argv[5]="-b";

        char sbsize_c[sbuffersize.size()+1];
        strcpy(sbsize_c,sbuffersize.c_str());
        argv[6]=sbsize_c;

        argv[7]="-c";

        char cbsize_c[cbuffersize.size()+1];
        strcpy(cbsize_c,cbuffersize.c_str());
        argv[8]=cbsize_c;

        argv[9]="-s";

        char bloom_c[sofbloom.size()+1];
        strcpy(bloom_c,sofbloom.c_str());
        argv[10]=bloom_c;

        listnode *temp=paths->gethead();
        for(i=0; i<paths->getcounter(); i++){

            string *s=(string*)temp->getvalue();

            char *s_c=new char[s->size()+1];
            strcpy(s_c,s->c_str());
            argv[11+i]=s_c;

            temp=temp->getnext();
        }

        argv[11+paths->getcounter()]=NULL;

        execvp(cmd, argv);

        exit(1);
    }

    return childpid;
}

