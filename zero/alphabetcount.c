/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h>
#include "count.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

/**
  The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:
      alphabetfreq[0]: the frequency of 'a'
      alphabetfreq[1]: the frequency of 'b'
         ... ...
      alphabetfreq[25]:the frequency of 'z'

  
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     letter -> frequency
     
     example:
     a -> 200
     b -> 101
     ... ...
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/
void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
{
   DIR *di;
   char *filename;
   char *file;
   struct dirent *dir; //open directory
   di = opendir(path);
   if (di != NULL)
   {
      while ((dir = readdir(di)) != NULL)
      {
         filename = dir->d_name;            //assign curr name to filename
         size_t txt = strlen(filename) - 3; //check length for .txt
         int cntr = 0;
         while (txt < strlen(filename))
         {
            if (!(filename[txt] == 't' || filename[txt] == 'x'))
               continue;
            else
            {
               cntr++; //increment counter to add current letter
            }
            txt++;
         }
         if (cntr == 3) //if txt is read, counter is 3
         {
            file = dir->d_name; //file is read when file checks out
            char pi[239];
            strcpy(pi, path);
            strcat(pi, "/");
            strcat(pi, file);
            FILE *fi = fopen(pi, "r"); //file path opens for reading
            if (fi == NULL)
            {
               return;
            }
            int ch = fgetc(fi); //gets first character
            while (!feof(fi))
            {
               if ((ch >= 65) && (ch <= 90)) //checks if char is uppercase then changes to lowercase
                  ch = ch + 32;
               if ((ch >= 97) && (ch <= 122))
               {
                  alphabetfreq[ch - 97] = (long)alphabetfreq[ch - 97] + 1; //increments counter
               }
               ch = fgetc(fi); //initializes again to get next char in the loop
            }

            fclose(fi);
            FILE *ge = fopen(filetowrite, "w"); //opens result.txt
            for (int i = 0; i < 26; i++)        //loop for alphabet
            {
               fprintf(fi, "%c -> %ld\n", (char)(i + 97), alphabetfreq[i]); //formats writing
            }

            fclose(ge);
         }
      }
   }
   closedir(di); //closes directory
}
