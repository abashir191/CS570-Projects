/*
 * specialcharcount.c - this file implements the specialcharcount function.
 */

#include <stdio.h>
#include "count.h"
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
void specialcharcount(char *path, char *filetowrite, long charfreq[])
{
  DIR *di;
  char *filename;
  char *file; //file storename
  struct dirent *dir;
  di = opendir(path); //open directory
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
        int ch = fgetc(fi); //gets first char
        while (!feof(fi))
        {
          if (ch == 33)
          {
            charfreq[4] = (long)charfreq[4] + 1;
          }
          else if (ch == 44)
          {
            charfreq[0] = (long)charfreq[0] + 1; //increments counter
          }
          else if (ch == 46)
          {
            charfreq[1] = (long)charfreq[1] + 1;
          }
          else if (ch == 58)
          {
            charfreq[2] = (long)charfreq[2] + 1;
          }
          else if (ch == 59)
          {
            charfreq[3] = (long)charfreq[3] + 1;
          }
          ch = fgetc(fi); //initializes again to get next char in the loop
        }
        fclose(fi);
        FILE *ge = fopen(filetowrite, "w");     //opens result.txt
        fprintf(fi, ", -> %ld\n", charfreq[0]); //formats writing
        fprintf(fi, ". -> %ld\n", charfreq[1]);
        fprintf(fi, ": -> %ld\n", charfreq[2]);
        fprintf(fi, "; -> %ld\n", charfreq[3]);
        fprintf(fi, "! -> %ld\n", charfreq[4]);
        fclose(ge);
      }
    }
  }
  closedir(di); //closes directory
}
/**
  The specialcharcount function counts the frequency of the following 5 special characters:
  ','   '.'   ':'    ';'    '!'
   
  in all the .txt files under directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
  
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of the above 5 special characters
      
      charfreq[0]: the frequency of ','
      charfreq[1]: the frequency of '.'
      charfreq[2]: the frequency of ':'
      charfreq[3]: the frequency of ';'
      charfreq[4]: the frequency of '!'

  
  Output: a new file named as filetowrite with the frequency of the above special characters written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     character -> frequency
     
     example:
     , -> 20
     . -> 11
     : -> 20
     ; -> 11
     ! -> 12     
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/
