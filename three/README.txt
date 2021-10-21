Please answer the following questions to explain your implementation (Directly write your answer below the questions).



1. Which are the critical regions need to be protected for mutula exclusion? Why are they? 


The two most critical regions are the last two methods in the bbuffer.c. They are the insert/remove methods. Both of these methods need to 
be protected so the buffer can update correctly. If both threads have access to the function at the same time, items would be removed/inserted
in the incorrect location. This makes the program run a bit slow but it produces the desired output.



2. There are 7 requirements your program should achieve: 

1)	When a producer thread inserts a new item into the buffer, a message should be print to screen showing which thread (with ID) insert which item (with value) to which buffer slot (with next_in)

The print statement in the insert_item function prints the correct output as in the program pdf; printf("producer %ld: inserted item %d into buffer index %d\n", id, item, buffer.next_in);
The id represents the threads ID and the item variable is the items value. The buffer.next_in is the buffer slot.

2)	When a consumer thread removes a new item from the buffer, a message should be print to screen showing which thread (with ID) remove which item (with value) from which buffer slot (with next_out)

The print statement in the remove_item function prints the correct output as in the program pdf; printf("consumer %ld: removed item %d from buffer index %d\n", id, *item, buffer.next_out);
The id represents the threads ID and the item variable is the items value. The buffer.next_out is the buffer slot.

3)	Producers must block if the buffer is full,

There is a lock for the semaphore in the insert_item method which checks if there is available space and if not, a wait is called to wait 
for an available spot.

4)	Consumers must block if the buffer is empty,

There is a lock for the semaphore in the remove_item method which checks if buffer is empty. If it cannot remove, then a wait is called until 
there is something to be removed.
5)	No two/more producers insert items to the same buffer slot,

More than one producer cannot insert items into the same buffer slot because of the semaphore lock in the insert_item method. Buffer slot cannot be 
changed until the lock is released.

6)	No two/more consumers remove the items from the same buffer slot, 

More than one consumer cannot remove items in the same buffer slot because of the semaphore lock in the remove_item method. Buffer slot cannot
be changed until lock is release.

7)	The messages must be printed in the order showing the real execution scenarios.

After an item is inserted/removed, a print statement follows after. Once a thread is created, a print statement states so. 

Please explain how they are satisfied in your design (you need to explain one by one!)








3) Why you think your design is the most effective one? Is there any other design also works but less effective? 


I believe my design is the most effective because it utilizes already given code as well as using as few semaphore locks as possible 
(an empty and full signal, along with a mutex signal). This allows the processes to be completed faster since there are fewer semaphore 
values to reference and the methods to manipulate the items and buffer pointers are very simplistic. If there is a better design to use, 
I'd honestly like to see it, but since the concepts are simple to implement, I don't think there are any better ideas to use.

My design is the most effective because I used several semaphore locks to prevent items from being inserted/removed into the wrong spots.
I utilized the given code and edited a few methods. I used waits to efficiently lock and unlock semaphores to produce the desired outputs.
Since I used less semaphore values for reference, the process to output was completed much quicker. The methods I implemented were pretty
simple as well. Since the implementation was very simple, I can't think of a more effective way to design this program.



