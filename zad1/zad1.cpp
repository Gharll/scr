/*
 *
 * Napisać program obsługujący sygnały czasu rzeczywistego
 * minimum to:
 * Wyświetlenie komunikatu: "dostałem sygnał taki i taki"
 * Dodatkowe wymogi
 * musi umieć odebrać dane przekazane od sygnału
 * musi umieć przetwarzać przynajmniej (ale może też więcej) 2 różne sygnały
 * obsługa sygnału ma być osługą synchroniczną (przynajmniej 3 wątki)
 * (ad1. w tym 1 wątek macierzysty i 2 wątki do obsługi sygnału)
 * napisać własną komende kill która umożliwi wysłanie sygnału z danymi
 *
 * sigfill
 * siempty
 * sigaddset
 * sigdelset
 *
 *
 * qnx login: 9
 * top - lista wątek
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

//for handling first signal
void * thread1_func(void * arg){

	sigset_t set;
	siginfo_t info;
	int thread_id = pthread_self();
	int signal = SIGRTMIN + 1;

	sigemptyset(&set);
	sigaddset(&set, signal);

	printf("Thread id %d is listening for signal: %d ...\n", thread_id, signal);
	while(1){
		sigwaitinfo(&set,&info);
	 	printf("Received signal %d, with code = %d, value %d\n", signal, info.si_code, info.si_value.sival_int);
	 	break;
	}

	printf("Thread id %d has been closed", thread_id);

	return NULL;
}

//for handling second signal
void * thread2_func(void * arg){

	sigset_t set;
	siginfo_t info;
	int thread_id = pthread_self();
	int signal = SIGRTMIN + 2;;

	sigemptyset(&set);
	sigaddset(&set, signal);

	printf("Thread id %d is listening for signal: %d ...\n", thread_id, signal);
	while(1){
		sigwaitinfo(&set,&info);
	 	printf("Received signal %d, with code = %d, value %d\n",
	 		signal, info.si_code, info.si_value.sival_int);
	 		break;
	}

	printf("Thread id %d has been closed", thread_id);
	return NULL;
}


int main(void){

	sigset_t set;

   sigemptyset(&set);
   sigaddset(&set, SIGRTMIN + 1);
   sigaddset(&set, SIGRTMIN + 2);

   	pthread_sigmask(SIG_BLOCK, &set, NULL);

	pthread_t thread1, thread2;

	pthread_create(&thread1, NULL, &thread1_func, NULL );
   	pthread_create(&thread2, NULL, &thread2_func, NULL );

    //wait for threads
   	pthread_join(thread1, NULL);
   	pthread_join(thread2, NULL);
	return EXIT_SUCCESS;
}
