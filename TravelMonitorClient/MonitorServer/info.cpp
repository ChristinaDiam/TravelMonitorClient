#include<iostream>

#include"info.h"


using namespace std;


info::info(int cyclicBufferSize, int bloomsize){

    this->citizens=new list();
    this->blooms=new list();
    this->skipvacc=new list();
    this->skipnotvacc=new list();

    this->bloomsize=bloomsize;

    this->cyclicb=new cyclicbuf(cyclicBufferSize);

}


info::~info(){

    delete this->citizens;
    delete this->blooms;
    delete this->skipvacc;
    delete this->skipnotvacc;

    delete this->cyclicb;

}



list* info::getcitizens(){

    return this->citizens;
}


list* info::getblooms(){

    return this->blooms;
}


list* info::getskipvacc(){

    return this->skipvacc;
}


list* info::getskipnotvacc(){

    return this->skipnotvacc;
}


int info::getbloomsize(){

    return this->bloomsize;
}


cyclicbuf* info::getcyclicbuf(){

    return this->cyclicb;
}


void info::printblooms(){

    listnode *lnode=this->blooms->gethead();

    while(lnode!=NULL){

        bloomvirus *bv=(bloomvirus*)lnode->getvalue();

        cout<<bv->getvname()<<endl;

        lnode=lnode->getnext();
    }
    
}