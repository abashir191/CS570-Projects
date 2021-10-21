I unzipped the one file and began to edit the mulproc.c. I first checked my lap zero testspecial and testalphabet to see if they compiled
correctly. First thing I did was call the arguments for testalphabet and testspecial from the zero file. 

I then created the two child process variables. Then for the two child processed, I used a if else if to run through and print in each process.
The first if statement checks if the fork has an error then executes the testalphabet. In the next else if statement it executes the testspecial.
In both those if statements I printed the correct text to print. In the else statement, I used a wait to wait for the process to terminate
then print the correct text. 


results:
Macs-MacBook-Air:one mac$ make
gcc -g -std=c99   -c -o mulproc.o mulproc.c
gcc -o mulproc mulproc.o
Macs-MacBook-Air:one mac$ ./mulproc 
CHILD <PID: 11984> process is executing /.testspecial program!
CHILD <PID: 11985> process is executing /.testalphabet program!
a -> 2973036
b -> 556908
c -> 765864
d -> 1786752
e -> 4883076
f -> 765336
g -> 809292
h -> 2818068
i -> 2586276
j -> 35112
k -> 401412
l -> 1728276
m -> 1050852
n -> 2509320
o -> 2766192
p -> 562848
q -> 28776
r -> 2177076
s -> 2465496
t -> 3291684
u -> 1015608
v -> 276804
w -> 1085040
x -> 46860
y -> 730752
z -> 12936
CHILD <PID: 11984>: Process has done with /.testalphabet program! See the results above!
, -> 745668
. -> 798072
: -> 15708
; -> 32340
! -> 63228
CHILD <PID: 11985>: Process has done with /.testspecial program! See the results above!