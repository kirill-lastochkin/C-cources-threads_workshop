#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "pthr.h"

int shop[SHOPSNUMBER];
pthread_mutex_t mshop[SHOPSNUMBER];

int main(void)
{
    int i,j[BUYERSNUMBER];
    pthread_t buyer[BUYERSNUMBER],loader;
    for(i=0;i<SHOPSNUMBER;i++)
    {
        pthread_mutex_init(&mshop[i],NULL);
        shop[i]=150+(rand()%101-50);
    }
    printf("workshop starts\n");
    for(i=0;i<BUYERSNUMBER;i++)
    {
        j[i]=i;
        pthread_create(&buyer[i],NULL,buyerf,&j[i]);
    }
    pthread_create(&loader,NULL,loaderf,NULL);
    for(i=0;i<BUYERSNUMBER;i++)
    {
        pthread_join(buyer[i],NULL);
    }
    printf("workshop finished\n");
    return 0;
}

