#ifndef CHILD
#define CHILD

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

#include "list.h"

using namespace std;

pid_t createchild(list *paths, int port, int numThreads, int socketBufferSize, int cyclicBufferSize, int sizeOfBloom);

#endif //CHILD