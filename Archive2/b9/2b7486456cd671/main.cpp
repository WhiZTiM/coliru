#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t se, so;

void print_sem()
{
    int ve, vo;
    sem_getvalue(&se, &ve);
    sem_getvalue(&so, &vo);
    cout << "sem_even: " << ve << " sem_odd: " << vo << endl;
}

void *even(void *threadid)
{
   long tid;
   tid = (long)threadid;
   cout << "Thread ID, " << tid << endl;
   
   int i = 0;
   while (i<=10)
   {
       sem_wait(&se);
       print_sem();
       cout << i << endl;
       i+=2;
       sem_post(&so);
   }
   
   pthread_exit(NULL);
}

void *odd(void *threadid)
{
   long tid;
   tid = (long)threadid;
   cout << "Thread ID, " << tid << endl;
  
   int i = 1;
   while (i<=9)
   {
       sem_wait(&so);
       print_sem();
       cout << i << endl;
       i+=2;
       sem_post(&se);
   }
   
   pthread_exit(NULL);
}

int main ()
{
   pthread_t te, to;
   
   cout << "main() : creating thread - odd" << endl;
   pthread_create(&to, NULL, odd, NULL);
   
   cout << "main() : creating thread - even" << endl;
   pthread_create(&te, NULL, even, NULL);
   
   sem_init(&se, 0, 1);
   sem_init(&so, 0, 0);
   
   pthread_exit(NULL);
}