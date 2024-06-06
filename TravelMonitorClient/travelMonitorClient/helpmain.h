#ifndef HELPMAIN
#define HELPMAIN


#include"child.h"
#include"list.h"
#include"bloomfilter.h"

using namespace std;

void travelmonitor(int numMonitors, int socketbufferSize, int bloomSize, string inputDirectory,int cyclicbuffersize,int numThreads);

void readbloom(list *b, int *sockarray, int numMonitors, int bloomsize);

#endif //HELPMAIN