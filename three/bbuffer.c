

#include <stdio.h> 
#include <stdlib.h> 
#include "bbuffer.h"
#include <semaphore.h>

//semaphores are declared
sem_t mutex; 
sem_t full;
sem_t empty;

void initilization()
{
    sem_init(&empty, 0, BUFFER_SIZE); //full and empty semaphores created
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    buffer.next_in = 0; //insert/remove pointers reset
    buffer.next_out = 0;
}

/* *
 * insert_item - thread safe(?) function to insert items to the bounded buffer
 * @param item the value to be inserted
 * @return 0 in case of sucess -1 otherwise
 */
  
int insert_item(int item, long int id)
{
    sem_wait(&empty); //waits for empty status
    sem_wait(&mutex); //lock set up
    if(buffer.next_in < BUFFER_SIZE) { 
        buffer.value[buffer.next_in] = item; //adds item
        printf("producer %ld: inserted item %d into buffer index %d\n", id, item, buffer.next_in);
        if(buffer.next_in == (BUFFER_SIZE - 1)) 
            buffer.next_in = 0;
        else
            buffer.next_in = (buffer.next_in + 1) % BUFFER_SIZE; //increment to next buffer
    }
    else //if can't insert, abort
        return -1;
    sem_post(&mutex); //unlocks 
    sem_post(&full);   //increments full
    return 0;
}

/**
 * remove_item - thread safe(?) function to remove items to the bounded buffer
 * @param item the address of the variable that the removed value will be written
 * @return 0 in case of sucess -1 otherwise
 */
int remove_item(int *item, long int id)
{
    sem_wait(&full); //waits for full status
    sem_wait(&mutex); //lock setup
    if(buffer.next_out > -1) { 
        *item = buffer.value[buffer.next_out]; //stores item in order to print
        buffer.value[buffer.next_out] = -1;    //prints statement
        printf("consumer %ld: removed item %d from buffer index %d\n", id, *item, buffer.next_out); 
        if(buffer.next_out == (BUFFER_SIZE - 1)) //resets index to 0
            buffer.next_out = 0;
        else 
            buffer.next_out = (buffer.next_out + 1) % BUFFER_SIZE; // increment to next buffer
    }
    else //otherwise can't remove, abort procedure
        return -1;
    sem_post(&mutex); //unlocks 
    sem_post(&empty); //increments empty
    return 0;
}

/**
 * producer - will iterate PRODUCER_ITERATION times and call the corresponding
 * function to insert an integer to the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple producer threads
 * @return nothing
 */
void * producer(void *param)
{
    int item, i;
    long int id = (long int)param;

    printf("producer %d started!\n", id);
    i = PRODUCER_ITERATIONS;
    while (i--) {
	  sleep(rand() % 3);

	item = rand() % 10000;
	if (insert_item(item, id))
	    printf("Error while inserting to buffer\n");
    }

    pthread_exit(0);
}

/**
 * consumer - will iterate CONSUMER_ITERATION times and call the corresponding
 * function to remove an integer from the bounded buffer
 * @param param an integer id of the producer used to distinguish between the
 * multiple consumer threads
 * @return nothing
 */
void * consumer(void *param)
{
    int item, i;
    long int id = (long int)param;

    printf("consumer %d started!\n", id);
    i = CONSUMER_ITERATIONS;
    while (i--) {
	sleep(rand() % 3);

	if (remove_item(&item, id))
	    printf("Error while removing from buffer\n");
    }
    pthread_exit(0);
}