#ifndef THREAD
#define THREAD

#include<pthread.h>
#include<iostream>
#include<string>
#include<cstring>

#include"info.h"
#include"helphelpmain.h"

using namespace std;

pthread_t *createthread(int numThreads, list *txtfiles, info *inf);

void *consumer(void* c);

void producer(list *txtpaths, info *inf);

void destroythread(int numThreads, pthread_t *threads);

void readfile(info *inf, string filename);

#endif //THREAD