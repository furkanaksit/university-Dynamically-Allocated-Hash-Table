# Dynamically-Allocated-Hash-Table
Hash Table design for Algorithms Course Homework 2

  * Designing an algorithm to implement one of the most essential data types of higher level programming languages using C.
  * Homework spesifications were to develope a hash table of given size. 
  * Added features after the homework specifications are provided:
    * Files structure is designed to be used with higher level programs. There has to be ./waitingFiles, ./waitingFiles/newFiles directories. 
      * waitingFiles is a folder for files to be hashed and added to the hashtable at the beginning of the program.
      * newFiles is a folder for files to be added after program start. Directory is searched for new files until the end of program and newly added files are added to the table when they are moved the folder.
      * In the future, process of searching for a new files could be moved to a thread and newly added files can be moved from newFiles to a addedFiles directory.
     * samples.txt and hashTable.txt documents created to show the files in the hashTable. 
      * In samples.txt, there is a list of files that are in the hashtable.
      * In hashTable.txt, there is a list of files with their position in hashtable, in the header part of file, i added the size of hashtable and the file count.
     * hashtable is now dynamically allocated and files can be added indefinately until memory is full. For the given solidity ratio, when a new file is added, if the solidity ratio is over a given number, hashtable will grow automatically. This function is called reHash function. It will reallocate a new hashtable and move every file to newly allocated hashtable to their newly generated positions.
     * Every file is opened and inspected to calculate the position in hashtable. This function is called hash function. Hashing method is specified in the homework document as double hashing method so i implemented it to my needs. There is a function for calculating the key number of words in file, then calculating the key of file. When this key is given to the first hash function, it produces the key of second hash function. Second hash function produces hash number of the file and it is the position that it will take in the hashtable.
     * Files are checked for their similarity. If two files are same even though their names are different, new file won't be added to the hashtable.
     * Delete file function make the flag of the spot -1 and that means the file is deleted from that spot. If the flag show 0 it shows that it wasn't allocated in any period of time and 1 means it is full.
      
   Functions that will be developed in the future.
   ---
   * Advance searching in the hashtable. Functions that i use right now has a logical problem.
   * Recover from save file.
   * For files there may be file structure or file pointer dictionary.
   * hashTable could be made a generic table for any kind of data type.
   
     
     
