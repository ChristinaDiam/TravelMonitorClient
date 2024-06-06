#ifndef INFO
#define INFO

#include<iostream>
#include<string>
#include<cstring>

#include"cyclicbuf.h"
#include"list.h"
#include"bloomfilter.h"

using namespace std;


class info
{
private:

    list *citizens;
    list *blooms;
    list *skipvacc;
    list *skipnotvacc;

    int bloomsize;

    cyclicbuf *cyclicb;

public:

    info(int cyclicBufferSize, int bloomsize);
    ~info();

    list* getcitizens();
    list* getblooms();
    list* getskipvacc();
    list* getskipnotvacc();

    int getbloomsize();

    cyclicbuf* getcyclicbuf();

    void printblooms();

};

#endif //INFO