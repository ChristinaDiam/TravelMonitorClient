#ifndef HELPMAIN
#define HELPMAIN

#include<string>
#include<cstring>

#include"list.h"
#include"countries.h"
#include"helphelpmain.h"
#include"info.h"
#include"thread.h"
#include"bloomfilter.h"

using namespace std;


void monitorServer(int port,int numThreads, int socketbufferSize, int cyclicBufferSize, int sizeofbloom, string *paths,int size);

void sendblooms(list *b, int sock, int bloomsize);


#endif //HELPMAIN