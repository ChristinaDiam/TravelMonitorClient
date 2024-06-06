#include<iostream>

#include"cyclicbuf.h"


using namespace std;


cyclicbuf::cyclicbuf(int cyclicBufferSize){

    this->parray=new string[cyclicBufferSize];

    this->size=cyclicBufferSize;
    this->count=0;
    this->start=0;
    this->end=-1;
}


cyclicbuf::~cyclicbuf(){

    delete[] this->parray;
}


string* cyclicbuf::getparray(){

    return this->parray;
}


int cyclicbuf::getsize(){

    return this->size;
}


int cyclicbuf::getcount(){

    return this->count;
}


string cyclicbuf::getpath(){

    string data="";

    pthread_mutex_lock(&(this->mtx));

    while(this->count <= 0){

        printf(">> Found Buffer Empty \n");
        pthread_cond_wait(&(this->cond_nonempty), &(this->mtx));
    }

    data=this->parray[this->start];
    this->start=(this->start + 1) % this->size;
    this->count--;

    pthread_mutex_unlock(&(this->mtx));

    return data;
}


void cyclicbuf::setpath(string p){

    pthread_mutex_lock(&(this->mtx));

    while(this->count>=this->size){

        printf(">> Found Buffer Full \n");
        pthread_cond_wait(&(this->cond_nonfull), &(this->mtx));
    }

    this->end=(this->end + 1) % this->size;
    this->parray[this->end]=p;
    this->count++;

    pthread_mutex_unlock(&(this->mtx));
}


pthread_mutex_t cyclicbuf::getmtx(){

    return this->mtx;
}


pthread_cond_t cyclicbuf::getcond_nonfull(){

    return this->cond_nonfull;
}


pthread_cond_t cyclicbuf::getcond_nonempty(){

    return this->cond_nonempty;
}


void cyclicbuf::setcount(int c){

    this->count=c;
}
    

void cyclicbuf::setstart(int s){

    this->start=s;
}

   
void cyclicbuf::setend(int e){

    this->end=e;
}


int cyclicbuf::getstart(){

    return this->start;
}

  
int cyclicbuf::getend(){

    return this->end;
}