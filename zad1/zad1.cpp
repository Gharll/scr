/*
 *
 * Napisa� program obs�uguj�cy sygna�y czasu rzeczywistego
 * minimum to:
 * Wy�wietlenie komunikatu: "dosta�em sygna� taki i taki"
 * Dodatkowe wymogi
 * musi umie� odebra� dane przekazane od sygna�u
 * musi umie� przetwarza� przynajmniej (ale mo�e te� wi�cej) 2 r�ne sygna�y
 * obs�uga sygna�u ma by� os�ug� synchroniczn� (przynajmniej 3 w�tki)
 * (ad1. w tym 1 w�tek macierzysty i 2 w�tki do obs�ugi sygna�u)
 * napisa� w�asn� komende kill kt�ra umo�liwi wys�anie sygna�u z danymi
 *
 * sigfill
 * siempty
 * sigaddset
 * sigdelset
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

const int SIG_THREAD1 = SIGRMIN + 1;
const int SIG_THREAD2 = SIGRMIN + 2;

//for handling first signal
void * thread1_func(void * arg){
	
	sigset_t set;
	siginfo_t info;
	int thread_id = pthread_self();
	int signal = SIG_THREAD1;
	
	sigemptyset(&fun1);
	sigaddset(&fun1, signal);
	
	printf("Thread id %d is listening for signal: %d .../n", thread_id, signal);
	while(1){
		sigwaitinfo(&set,&info);
	 	printf("Received signal %d, with code = %d, value %d\n",
        	signo, info->si_code, info->si_value.sival_int);
	}

	
	//return NULL;
}

//for handling second signal
void * thread2_func(void * arg){
	
	sigset_t set;
	siginfo_t info;
	int thread_id = pthread_self();
	int signal = SIG_THREAD2;
	
	sigemptyset(&fun1);
	sigaddset(&fun1, signal);
	
	printf("Thread id %d is listening for signal: %d .../n", thread_id, signal);
	while(1){
		sigwaitinfo(&set,&info);
	 	printf("Received signal %d, with code = %d, value %d\n",
        	signo, info->si_code, info->si_value.sival_int);
	}
	
	
	//return NULL;
}


int main(void){
		
	sigset_t set;
   
   sigemptyset(&set);
   sigaddset(&set, SIG_THREAD1);
   sigaddset(&set, SIG_THREAD2);
   
   	pthread_sigmask(SIG_BLOCK, &set, NULL)
	
	pthread_t thread1, thread2;
	pthread_create(&t1, NULL, &thread1_func, NULL );
   	pthread_create(&t2, NULL, &thread2_func, NULL );
   
   
    //wait for threads
   	pthread_join(thread1, NULL);
   	pthread_join(thread2, NULL);
	return EXIT_SUCCESS;
}
