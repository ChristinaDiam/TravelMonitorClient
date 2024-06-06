#define PATHLENGTH 13

#include<iostream>
#include<cstdio>
#include<unistd.h>
#include<cstring>
#include<string>
#include<dirent.h>
#include<sys/wait.h>         /* sockets */
#include<sys/types.h>        /* sockets */
#include<sys/socket.h>       /* sockets */
#include<netinet/in.h>       /* internet sockets */
#include<netdb.h>            /* gethostbyaddr */

#include"helpmain.h"


using namespace std;


void monitorServer(int port,int numThreads, int socketbufferSize, int cyclicBufferSize, int sizeofbloom, string *paths, int size){


    int sock;
    int newsock;
    struct sockaddr_in server, client;
    socklen_t clientlen;

    struct sockaddr *serverptr=(struct sockaddr *)&server;
    struct sockaddr *clientptr=(struct sockaddr *)&client;
    

    if((sock=socket(AF_INET, SOCK_STREAM, 0))<0){

        perror("socket");
    }


    server.sin_family=AF_INET;                    /* Internet domain */
    server.sin_addr.s_addr=htonl(INADDR_ANY);
    server.sin_port=htons(port);                  /* The given port */


    //Bind socket to address
    if (bind(sock, serverptr, sizeof(server)) < 0){
        perror("bind");
    }

    //Listen for connections
    if (listen(sock,1) < 0){
        perror("listen");
    }

    printf("Listening for connections to port %d\n", port);
    

    if((newsock=accept(sock, clientptr, &clientlen))<0){

        perror("accept");
    }

    printf("Accepted connection\n");


    list *txtfiles=new list();     //list of txt files

    int i;
    for(i=0; i<size; i++){

        //open the directories
        DIR* dir;
        struct dirent* en;

        dir=opendir(paths[i].c_str());

        if(dir==NULL){

            perror("opendir");
            return;
        }


        //read the directory
        while((en=readdir(dir))!=NULL){

            string path1=paths[i];

            int comp=strcmp(".",en->d_name);
            if(comp==0){

                continue;
            }

            comp=strcmp("..",en->d_name);
            if(comp==0){

                continue;
            }

            string path2(en->d_name);

            path1.append("/");
            path1.append(path2);

            string *p=new string(path1);
            txtfiles->listinsert(p);
        }

    }


    //create threads
    info *inf=new info(cyclicBufferSize,sizeofbloom);
    
    pthread_t *pt=createthread(numThreads,txtfiles,inf);


    //send bloomfilters to parent
    sendblooms(inf->getblooms(),sock,sizeofbloom);




    //destroy threads
    destroythread(numThreads,pt);


    //close sockets
    close(newsock);
    close(sock);
    
}


void sendblooms(list *b, int sock, int bloomsize){

    listnode *lnode=b->gethead();

    while(lnode!=NULL){

        bloomvirus *bv=(bloomvirus*)lnode->getvalue();
        bloomfilter *bf=bv->getbloom();

        //encode bloomfilter to string
        char *s;
        bf->tostring(&s);

        //send bloomfilter to parent
        write(sock,s,bloomsize);

        delete[] s;

        lnode=lnode->getnext();
    }

    write(sock,"done",4);
}

