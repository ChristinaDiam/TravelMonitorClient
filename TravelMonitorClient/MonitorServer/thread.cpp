#include<iostream>
#include<unistd.h>

#include"thread.h"


using namespace std;


pthread_t *createthread(int numThreads, list *txtfiles, info *inf){

    pthread_t *threads=new pthread_t[numThreads];

    int i;
    for(i=0; i<numThreads; i++){

        int pc=pthread_create(&threads[i],0, consumer,inf);

        if(pc!=0){

            cout<<strerror(pc)<<endl;
        }
    }

    producer(txtfiles,inf);

    return threads;
}


void *consumer(void* c){

    info *inf=(info*)c;

    cyclicbuf *cyclic=inf->getcyclicbuf();

    while(cyclic->getcount() > 0){

		string str=cyclic->getpath();

        pthread_mutex_t mtx=cyclic->getmtx();
        pthread_mutex_lock(&mtx);

        readfile(inf,str);

        pthread_mutex_unlock(&mtx);

        pthread_cond_t cnonfull=cyclic->getcond_nonfull();

		pthread_cond_signal(&cnonfull);
		usleep(500000);
	}

	pthread_exit(0);
}


void producer(list *txtpaths, info *inf){

    cyclicbuf *cyclic=inf->getcyclicbuf();

    listnode *lnode=txtpaths->gethead();

	while(lnode!=NULL){

        string str=*((string*)lnode->getvalue());
        cyclic->setpath(str);
		
        pthread_cond_t cnonempty=cyclic->getcond_nonempty();

		pthread_cond_signal(&cnonempty);
		usleep(1000);

        lnode=lnode->getnext();
	}
	
}


void destroythread(int numThreads, pthread_t *threads){

    int i;
    for(i=0; i<numThreads; i++){

        pthread_join(threads[i], 0);
    }
}


void readfile(info *inf, string filename){

    FILE *fp;

    fp=fopen(filename.c_str(),"r");        //open file

    if(fp==NULL){

        printf("File could not be opened.\n");
        exit(EXIT_FAILURE);
    }


    char id[20],fn[20],ln[20],country[20],age[4],virName[20],yes_no[4],date[15];

    string temp[8];

    list *skipvaccinated=inf->getskipvacc();
    list *skipnotvaccinated=inf->getskipnotvacc();
    list *citizens=inf->getcitizens();
    list *blooms=inf->getblooms();

    int bloomsize=inf->getbloomsize();


    while(fscanf(fp, "%s%s%s%s%s%s%s", id, fn, ln, country, age, virName, yes_no)!=EOF){

        temp[0]=string(id);
        temp[1]=string(fn);
        temp[2]=string(ln);
        temp[3]=string(country);
        temp[4]=string(age);
        temp[5]=string(virName);
        temp[6]=string(yes_no);

        char ch=fgetc(fp);

        if(ch==' '){
            fscanf(fp, "%s",date);
            temp[7]=string(date);
        }else{
            temp[7]="";
        }

        if((temp[6]=="NO" && temp[7]=="") || (temp[6]=="YES" && temp[7]!="")){

            if(temp[7]==""){

                temp[7]="-";
            }

            insertCitizenRecord(temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],
            temp[7],skipvaccinated,skipnotvaccinated,citizens,blooms,bloomsize);

        }else{

            //wrong citizen record (wrong information about date and yes/no)
            cout<<"ERROR IN RECORD "<<temp[0]<<endl;
        }
    }

    fclose(fp);
}