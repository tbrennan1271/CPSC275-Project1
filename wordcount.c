/* wordcount.c
 * CPSC 275
 * 9/27/19
 * Tyler Brennan
 */

#include <stdio.h>
#include <ctype.h>    // Imported to use tolower()
#include <string.h>   // Imported to use strcmp(), memset(), and strcpy()
#define MAX 1000
#define LEN 30

int readFile(char (*words)[LEN], int *count);
void sort(char (*words)[LEN], int *count, int n);

void main(void){
  char words[MAX][LEN];
  int count[MAX];
  int size;
  int i;
  size = readFile(words, count);
  sort(words, count, size);
  for(i = 0; i < size; i++)
    printf("%s:\t%d\n", *(words+i), *(count+i));
}

/*
readFile reads an input file and puts the each word in a 2D array of characters
when it appears the first time. It then checks if there are any repeated
words and increases a count for each word and disregards the repeated word.
*/
int readFile(char (*words)[LEN], int *count){
  int letters = 0;  // Size of the word and will be used for columns in words
  int numWords = 0; // Used to keep track of the rows in words
  int c, i;         // c is used to get characters and i is used for loops
  while((c = tolower(getchar())) != EOF){   // Loop until the end of file is reached
    if(c >= 'a' && c <= 'z'){               // Checks to see if it is another word
      *(*(words + numWords) + letters) = c; // Sets the char to words
      letters++;
    }
    else if(letters > 0){         // Stops the code from taking up two array indexes
      *(count + numWords) = 1;    // Start the word count at 1
      for(i = 0; i < numWords; i++){
        if(strcmp(*(words + i), *(words + numWords)) == 0){ // Checks repeated words
          memset(*(words + numWords), '\0', letters);       // Clears the full string
          numWords--;             // Bring index back one
          (*(count + i))++;       // Increment word count
        }
      }
      numWords++;       // Increment to next space in memory
      letters = 0;      // Reset letters
    }
  }
  return numWords;
}

/*
Sort takes in the sorted array, the word count, and the length and sorts the
each array based off of the given algorithm. It uses count to determine where
everything should go and shifts the the count array index and the corresponding
position in the 2D array of words to the same index.
*/
void sort(char (*words)[LEN], int *count, int n){
  int keyCount;       // Key for the 'count' array
  char keyWord[LEN];  // Key array to store strings from the 'words' array
  int i, j;           // Three variables used for indexes in loops
  for(i = 1; i < n; i++){         // Loop through every indexes
    keyCount = *(count + i);      // Save keys for the current count and words values
    strcpy(keyWord, *(words + i));
    j = i - 1;
    while((j >= 0) && (*(count + j) < keyCount)){ // Checks order based off of the count
      *(count + j + 1) = *(count + j);            // Shifts count to the correct position
      strcpy(*(words + j + 1), *(words + j));     // Copy the word to another index
      j--;            // Decrease j
    }
    *(count + j + 1) = keyCount;  // Use the key to put back the saved count/word
    strcpy(*(words + j + 1), keyWord);
  }
}

/*
Input:
  You know you know this, but you do not know of unknown trolls, because no
  known trolls will sew by windows, though they will owe you a hello when they throw a hoe, as it
  will go low and blow a hole in that window.

Output:
  you:	4
  know:	3
  will:	3
  a:	3
  trolls:	2
  they:	2
  this:	1
  but:	1
  do:	1
  not:	1
  of:	1
  unknown:	1
  because:	1
  no:	1
  known:	1
  sew:	1
  by:	1
  windows:	1
  though:	1
  owe:	1
  hello:	1
  when:	1
  throw:	1
  hoe:	1
  as:	1
  it:	1
  go:	1
  low:	1
  and:	1
  blow:	1
  hole:	1
  in:	1
  that:	1
  window:	1
*/
