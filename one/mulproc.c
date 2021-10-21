/*
 This program will fork two child processes running the two programs generated in programming zero in parallel.
 Hint: You mant need to use fork(), exec() family, wait(), exit(), getpid() and etc ...
 
 Requirements:
 
 1) Exactly two child processes are created, one to run testspecial program and the other is to run testalphabet program;
 2) When a program starts to run, print a message to the output screen showing which process (with PID) is running which program, for example:
    "CHILD <16741> process is executing testalphabet program!"
    
 3) When a program is done, the process exits and at the same time, a message should be print to the output screen showing which  process (with PID) is done with the program, for example:
    "CHILD <16741> process has done with testalphabet program !"
    
 4) The messages should match the real execution orders, i.e. when the testspecial program starts/ends, the right message should be print out. So you need to figure out how to get the starting/ending time of each 
 process.
   
   
 The expected screen print out should be similar as follows:
 
 CHILD <16741> process is executing testalphabet program!
 CHILD <16742> process is executing testspecial program!
, -> 745668
. -> 798072
... ...

CHILD <16742> process has done with testspecial program !
a -> 2973036
b -> 556908
... ...

CHILD <16741> process has done with testalphabet program !
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>       
#include <sys/types.h>  
#include <sys/wait.h>  

// int main(void) {		    
//     /* Child processes  arguments*/ 
// 	int status;
//     char *argsAlpha [] = {"../zero/testalphabet", NULL}; 
//     char *argSpec [] = {"../zero/testspecial", NULL};
//     pid_t childpid1, childpid2;

 
// if(!(childpid1 = fork()))    //if no error in fork, testalphabet process executes
//     {
//         printf("CHILD <PID: %d> process is executing /.testspecial program!\n", getpid());
//         execv(argsAlpha[0], argsAlpha);
//       	exit(1);
//     }
// else if(!(childpid2 = fork())) //if no error in fork, testspecial process executes
//     {
//         printf("CHILD <PID: %d> process is executing /.testalphabet program!\n", getpid());
//         execv(argSpec[0], argSpec);
//       	exit(1);
//     } 
// else {    // parent code  
//         //waits for children to terminate so message can print for the correct process
//         childpid1 = wait(NULL); 

//         printf ("CHILD <PID: %d>: Process has done with /.testalphabet program! See the results above!\n", childpid1);
// 		childpid2 = wait(NULL);  

//         printf ("CHILD <PID: %d>: Process has done with /.testspecial program! See the results above!\n", childpid2);
//     }
// 	return 0;	
// }
int main(void) {
			    
    /* Child processes  arguments*/ 
	int status;
    char *argSpec [] = {"../zero/testspecial", NULL}; 
    char *argsAlpha [] = {"../zero/testalphabet", NULL};
    pid_t child1_pid, child2_pid;
    if(!(child1_pid = fork())) //if fork() runs without error, then execute testspecial child process
    {
    printf("CHILD <PID: %d> process is executing testspecial program!\n", getpid());
    execv(argSpec[0], argSpec);
    exit(1);
    }
    if(!(child2_pid = fork()))    //if fork() runs without error, then execute testalphabet child process
    {
    printf("CHILD <PID: %d> process is executing testalphabet program!\n", getpid());
    execv(argsAlpha[0], argsAlpha);
    exit(1);
    }
    else {    // Parent code
        /*
        * Waits the two chiildren terminate to to print a message and
        * make the terminal prompt available again.   
        */ 
         child1_pid = wait(NULL); 

         printf ("CHILD <PID: %d>: Process has done with testspecial program! See the results above!\n", child2_pid);
		child2_pid = wait(NULL);  

        printf ("CHILD <PID: %d>: Process has done with testalphabet program! See the results above!\n", child1_pid);
    }
	return 0;	
}
