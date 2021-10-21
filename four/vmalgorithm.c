/*
 *  Implementation of FIFO and LRU page replacement algorithm
 *  Please add appropriate level of comments in this file 
 */

#include "vmalgorithm.h"


/* 
 * Generates a random access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */
void generateAccessPattern()
{
   int i;
   srand(time(0));
   accessPattern = (int *)malloc( sizeof(int) * AccessPatternLength);   
   printf("The randomized Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
		     accessPattern[i] = rand() % ReferenceSZ;
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}

/*
 * Initialize the parameters of simulated memory
 */
void initializePageFrame() {
    int i;
    
    // dynamic allocated FrameNR frames to be used in memory
    memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );    
    
    memory.table = (int *)malloc( sizeof(int)* FrameNR ); //aux table
    
    memory.nextToReplaced = 0;  // indicate the new frame to be replaced as 0
   
   
    for(i=0; i< FrameNR; i++) {
        memory.PageFrameList[i] = -1;  // initialization to -1 indicating all frames are unused
        memory.table[i] = 0; 
   }
}


/*
 * Prints all pages loaded in memory
 */
void printPageFrame() {
   int i;
//    printf("The Access Pattern: ");
   for(i=0; i< FrameNR; i++) {
        printf("%2d ",memory.PageFrameList[i]);       
   }
   printf("\n");
}



/*
 * Prints the access pattern again
 */
void printAccessPattern() {
   int i;

   printf("The Same Access Pattern: ");
   for(i=0; i < AccessPatternLength; i++) {
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}



 /*
 * Return: number of pages fault using FIFO page replacement algorithm
 */
int FIFO() {

    int pageFaultcnt=0;
    int i;


    for (i = 0; i < AccessPatternLength; i++) {
       pageFaultcnt += FIFOAdd(accessPattern[i]);
       printPageFrame();
   }

   return pageFaultcnt;
   
}



// Look for the page number using FIFO
int FIFOLookUp(int pageNum) {
    
    int i;
    for ( i = 0; i < FrameNR; i++ ) {

        if (memory.PageFrameList[i] == pageNum) {

            return 1;
        }
    }

    return 0;
}



// Uses FIFO page replacement to find page fault
int FIFOAdd(int pageNum) {

    int faultPage = 0;
    
    if ( 0 == FIFOLookUp(pageNum) ) {

        memory.PageFrameList[memory.nextToReplaced] = pageNum;
        memory.nextToReplaced = (memory.nextToReplaced + 1) % FrameNR;
        faultPage = 1;
    }

    return faultPage;      
}



/*
 * Return: number of pages fault using LRU page replacement algorithm
 */
int LRU() {
    
    int pageFaultcnt = 0;
    int i;

    for ( i = 0; i < AccessPatternLength; i++ ) { 
        pageFaultcnt += LRUAdd(i);
        printPageFrame();
    }
    
    return pageFaultcnt; 
}


//Look for page number using LRU
int LRULookUp(int pageNum) {

    int j;
    
    
    int i;
    for (i = 0; i < FrameNR; i++) {
        memory.table[i] = 0;      // table resets
    }


    for ( i = 0; i < FrameNR; i++) {
        if (memory.PageFrameList[i] == accessPattern[pageNum]) { //if page is in frame
            return i;
        }
        
        else if (memory.PageFrameList[i] == -1) { //if new page
            memory.nextToReplaced = i;
            return -1;
        }
        
        else { //if frame is full and no new pages
            for (j = pageNum-1; j > 0; j--) {
                if (memory.PageFrameList[i] == accessPattern[j]) {
                    memory.table[i] = j;
                    break;
                }
            }
        }
    }
    
    
    // finds index of LRU page in the frame
    int leas= 10000;
    for ( i = 0; i < FrameNR; i++) {
        if (memory.table[i] < leas) {
            leas = memory.table[i];
            memory.nextToReplaced = i;
        }
    }
    
    return -1;
}


// Uses LRU page replacement to find page fault
int LRUAdd(int pageNum) {
    
    int faultPage = 0;
    int fIndex = -1;
    
    fIndex = LRULookUp(pageNum);

    if ( fIndex == -1 ) { 
        // replace page
        memory.PageFrameList[memory.nextToReplaced] = accessPattern[pageNum];
        faultPage = 1;
    }
    
    return faultPage;
}




