/*
 * alphabetcountmulthreads.c - this file implements the alphabetcountmulthreads function.
 */

/**
  The alphabetcountmulthreads function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite. Different with programming assignment#0, you need to implement the program using mutithreading.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z, which should be already up-to-date;
      num_threads - number of the threads running in parallel to process the files
      
       
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Requirements:
1)	Multiple threads are expected to run in parallel to share the workload, i.d. suppose 3 threads to process 30 files, then each thread should process 10 files;
2)	When a thread is created, a message should be print out showing which files this thread will process, for example:
Thread id = 274237184 starts processing files with index from 0 to 10!
3)	When a file is being processed, a message should be print out showing which thread (thread_id = xxx) is processing this file, for example:
Thread id = 265844480 is processing file input_11.txt
4)	When a thread is done with its workload, a message should be print out showing which files this thread has done with work, for example:
      Thread id = 274237184 is done !
5)	The array: long alphabetfreq[ ] should always be up-to-date, i.d. it always has the result of all the threads counted so far.  [You may need to use mutexes to protect this critical region.]


You should have the screen printing should be similar as follows:

 Thread id = 274237184 starts processing files with index from 0 to 10!
 Thread id = 265844480 starts processing files with index from 11 to 22!
 Thread id = 257451776 starts processing files with index from 23 to 31!

 Thread id = 265844480 is processing file input_11.txt
 Thread id = 257451776 is processing file input_22.txt
 Thread id = 274237184 is processing file input_00.txt
  ? ? 

 Thread id = 274237184 is done !
 Thread id = 265844480 is done !
 Thread id = 257451776 is done !

 The results are counted as follows:
 a -> 2973036
 b -> 556908
 c -> 765864
 ?  ? 
*/

#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include "count.h"
#include <dirent.h>
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

pthread_mutex_t mtex = PTHREAD_MUTEX_INITIALIZER;
int indexfile = 0;
char *_path; 
long tmparray[ALPHABETSIZE] = {0};

struct datafile {
    char file [256];           
};

typedef struct param_thread { 
     struct datafile* d; // threads will get array from datafiles
     int n;    // num of elements
} 
thread_param_t;


void *thread(void *param) { 
    thread_param_t* thread_paramater = (thread_param_t*)param; //initializes data needed 
    int k;
    for(k = 0; k < thread_paramater->n; k++) { //loops through num elements
        char pa[256];
        struct datafile *temp = thread_paramater->d + k;
        strcpy(pa, _path); 
        strcat(pa, "/");
        strcat(pa, temp->file);
        FILE *f = fopen(pa, "r");
        if(f == NULL) { //file cannot be opened
            return 0;
        }
        printf("Thread id = %ld is processing  %s\n", pthread_self(), temp->file); //prints that file is processing
        int cha = fgetc(f); //grabs first char
        while(!feof(f)) {
            if((cha >= 65) && (cha <= 90)) //changes from uppercase to lowercase
                cha = cha + 32;
            if((cha >= 97) && (cha <= 122)) { 
                pthread_mutex_lock(&mtex); 
                tmparray[cha - 97] = (long) tmparray[cha - 97] + 1; //cha-97 is for each lowercase letter
                pthread_mutex_unlock(&mtex);
            }
            cha = fgetc(f); //initializes again for next char in loop
        }
        fclose(f);
    }

    printf("Thread id = %ld is done!\n", pthread_self()); //prints that statement is done
    pthread_exit(NULL);

}


void alphabetcountmulthreads(char *path, char *filetowrite, long alphabetfreq[], int num_threads) 
{
	DIR *d;
    char *fname;
    char *fil;
    int begin = 0; 
    int ends = 0;
    struct dirent *dir; 
    d = opendir(path); //opens directory
    struct datafile fil_names[255];
    _path = path;
    while((dir = readdir(d)) != NULL)
    {
            char *fname = dir->d_name;
            size_t tx = strlen(fname) - 3; //checks for .txt extentsion
                int cntr = 0;
                while(tx < strlen(fname)) {
                    if(!(fname[tx] == 't' || fname[tx] == 'x'))
                        continue;
                    else {
                        cntr++; 
                    }
                    tx++;
                }
                if(cntr == 3) {
                    fil = dir->d_name; //immediately stores file to be processed
                    strcpy(fil_names[indexfile
                ].file, fil); // store file into fil_names array;
                    indexfile
                ++;   
                }
    }

    pthread_t th_array[num_threads]; //initializes num of threads needed
    thread_param_t thread_paramater[num_threads];
    int thread_counter = 0;

    int sets = indexfile
 / num_threads; // num of files for threads
    int i;

    for(i = 0; i < num_threads - 1; i++) { // creates threads
       thread_paramater[i].n = sets; //element numbers set to sets
       thread_paramater[i].d = fil_names + sets * i; //grabs correct data correspoding to thread
       ends = begin + thread_paramater[i].n - 1; //sets correct ends index for the first process
       pthread_create(&th_array[i], NULL, thread, thread_paramater + i); //initialize thread
       printf("Thread id = %ld is processing indexes %d to %d!\n", th_array[i], begin, ends); //prints thread index
       begin = ends + 1; //aligns begin correctly after the first pass
    }
    thread_paramater[i].n = indexfile
 - sets * i; //grabs extra files and adds them to thread count
    thread_paramater[i].d = fil_names + sets * i;
    ends = begin + thread_paramater[i].n - 1;
    pthread_create(&th_array[i], NULL, thread, thread_paramater + i); 
    printf("Thread id = %ld is processing indexes %d to %d!\n", th_array[i], begin, ends);

    for(int i = 0; i< num_threads; i++) { //joins threads
        pthread_join(th_array[i], NULL);
    }
    for (int i = 0; i < 26; i++) { //copies results from threads 
        alphabetfreq[i] = tmparray[i];
    }
    
    FILE *get = fopen(filetowrite, "w"); //opens result for formatting
    for(int i = 0; i < 26; i++) { 
        fprintf(get, "%c -> %ld\n", (char)(i+97), alphabetfreq[i]); //writing format
    }  
    fclose(get); //closes file write
    closedir(d); //closes directory  		
}