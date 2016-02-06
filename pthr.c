#include "pthr.h"

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ENOUGH 500

extern int shop[SHOPSNUMBER];
extern pthread_mutex_t mshop[SHOPSNUMBER];

void* buyerf(void* arg)
{
    int amount=0,i,check,*num;
    num=(int*)arg;
    while(amount<ENOUGH)
    {
        for(i=0;i<SHOPSNUMBER;i++)
        {
            check=pthread_mutex_trylock(&mshop[i]);
            if(check!=0) continue;
            else
            {
                if(shop[i]!=0)
                {
                    amount+=shop[i];
                    printf("buyer %d: consumed %d from shop %d,total amount is %d\n",*num+1,shop[i],i+1,amount);
                    shop[i]=0;
                }
                pthread_mutex_unlock(&mshop[i]);
                if(amount>=ENOUGH) break;
                sleep(2);
            }
        }
    }
    printf("ok, for buyer %d its enough!\n",*num+1);
    return NULL;
}

void* loaderf(void* arg)
{
    int check,i;
    while(1)
    {
        for(i=0;i<SHOPSNUMBER;i++)
        {
            check=pthread_mutex_trylock(&mshop[i]);
            if(check!=0) continue;
            else
            {
                if(shop[i]==0)
                {
                    shop[i]=150+(rand()%101-50);
                    printf("loader : shop %d now has %d\n",i+1,shop[i]);
                }
                pthread_mutex_unlock(&mshop[i]);
                sleep(1);
            }
        }
    }
    return NULL;

}
