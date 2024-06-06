#ifndef CYCLICBUF
#define CYCLICBUF

#include<pthread.h>
#include<iostream>
#include<string>
#include<cstring>

using namespace std;


class cyclicbuf
{
private:

    string *parray;

    int size;       //cyclicbuffer size
    int count;
    int start;
    int end;

    pthread_mutex_t mtx;
    pthread_cond_t cond_nonempty;
    pthread_cond_t cond_nonfull;

public:

    cyclicbuf(int cyclicBufferSize);
    ~cyclicbuf();

    string* getparray();
    int getsize();
    int getcount();
    int getstart();
    int getend();

    pthread_mutex_t getmtx();
    pthread_cond_t getcond_nonfull();
    pthread_cond_t getcond_nonempty();

    string getpath();
    void setpath(string p);

    void setcount(int c);
    void setstart(int s);
    void setend(int e);
};


#endif //CYCLICBUF