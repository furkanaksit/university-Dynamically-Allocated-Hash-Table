#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <dirent.h>
#include <Windows.h>


#define LoadF 0.6	// load factor of the hast table
#define R 2


// file struct keeps the name and size of the struct
typedef struct files {
    char *filename;
    int sizeOfFile;
} files;

typedef struct hashTable {
    int tableSize;
    int fileCount;
    files **table;
    int *flags;
} hashTable;


int hash(int key, int i, int M);
int hash1(int key, int M);
int hash2(int key, int M);

int isPrime(int n);
int nextPrime(int N);
int lenghtOfHashTable(int numberOfElements);


int calculateKey(files *file);
int keyFromWord(char* wordR);
hashTable *filesToHash(hashTable *table);
hashTable *addToTable(hashTable *table, files *newFile);
hashTable *reHash(hashTable *table);
int isSame(files *first, files *second);
hashTable *makeHashTable();
void saveHashTable(hashTable *table);
int searchInHashTable(char *filename, hashTable *table);
void deleteFromHashTable(char *filename, hashTable *table);

int main(int argc, char **argv)
{
	
	
	hashTable *table = makeHashTable();
	filesToHash(table);
	//menu();
	

	
	return 0;
}


int hash(int key, int i, int M){
	// M is the lenght of table
	// hash function is defined by the homework
	return ((hash1(key, M) + i*(hash2(key, M))) % M);
	}
int hash1(int key, int M){
	// M is the lenght of table
	// hash1 function is defined by the homework
	// it might be developed
	return (key % M); 
	}
int hash2(int key, int M){
	// MM is the lenght of table
	// MM is defined by the homework
	// hash2  function is defined by the homework
	int MM = M-1;
	return 1+(key % MM);
	}	
// Function that returns true if n  
// is prime else returns false  
int isPrime(int n){  
    // Corner cases  
    if (n <= 1)  return 0;  
    if (n <= 3)  return 1;  
    
    // This is checked so that we can skip   
    // middle five numbers in below loop  
    if (n%2 == 0 || n%3 == 0) return 0;  
    
    for (int i=5; i*i<=n; i=i+6)  
        if (n%i == 0 || n%(i+2) == 0)  
           return 0;  
    
    return 1;  
	}  
  
// Function to return the smallest 
// prime number greater than N 
int nextPrime(int N){ 
    // Base case 
    if (N <= 1) 
        return 2; 
  
    int prime = N; 
    int found = 0; 
  
    // Loop continuously until isPrime returns 
    // true for a number greater than n 
    while (!found) { 
        prime++; 
  
        if (isPrime(prime)) 
            found = 1; 
    } 
    return prime; 
	} 
int lenghtOfHashTable(int numberOfElements){
	printf("\n");
	printf("\nlenghtofhash: calculate size of table for - %d - elements",numberOfElements);
	printf("\nlenghtofhash: nextprime(%d)",(int)(numberOfElements/LoadF));
	// returns lenght of hash table according to the formula that
	// is defined by the homework
	return nextPrime((int)(numberOfElements/LoadF));
	}


// keyFromWord calculates keys of words
int keyFromWord(char* wordR){
	printf("\n");
	int key = 0;
	int size = strlen(wordR);
	int i;
	for(i = size; i > 0; i--){
		key += (int)(wordR[size-i])*pow(R,i-1);
		//printf("\n  - %c = %d - * - 2^%d - \n",wordToBeCalculated->wordR[size-i],(int)(wordToBeCalculated->wordR[size-i]), i-1);
		}
	return key;
	}
// calculate key is for summing all key values of every word in the given file	
int calculateKey(files *file){
	printf("\n");
	// calculates the key value of a file given filename
	// takes the words char by char and uses the formula defined by
	// homework to calculate the key value
	// has to be checked whether return value is 0 or not
	// if 0 file couldn't be read and returned an error message
	
	int key = 0;
	char *wordR = (char*)malloc(sizeof(char)*1024); 
	// c is a char buffer to read file char by char
	printf("\ncalculateKey: recieved file with name: %s", file->filename);
	
	FILE * fp = fopen(file->filename, "r");
	if (fp == NULL){
		printf("\nfile: %s couldn't be read\n", file->filename);
		return 0;
		}
	else{
		printf("\ncalculateKey: file succesfully opened");
		
		while( fscanf(fp, "%s", wordR) != EOF )
        {
            key += keyFromWord(wordR);
        }
		
	
		printf("\nfile succesfully read and key is constructed. key : %d", key);
		}
	fclose(fp);
	return key;
	}
	
// filesToHash is for checking if there are files to hash in '/waitingFiles'	
hashTable *filesToHash(hashTable *table){
	printf("\n");
	
	DIR *dr , *ir; 
	struct dirent *de, *ie;
	
	FILE *waitingFile;
	files *fileToAdd;
	
	int i = 0;	
	long fsize = 0;
	char file[1024];
	char load; 
	
	
	dr = opendir("./waitingFiles"); 
	
	if (dr == NULL){ 
		printf("\nfilesToHash: Could not open current directory" ); 
		return 0; 
		} 
		
	for(i=2; i>0 && ((de = readdir(dr)) != NULL); i--){
		} 
		
		
	while((de = readdir(dr)) != NULL){
		printf("\n-----------------------------------\n");
		fileToAdd = (files*)malloc(sizeof(files));
		fileToAdd->filename = (char*)malloc(sizeof(char)*1024);
		
		printf("\nfilesToHash: adding %s to hash table", de->d_name);	
		strcpy(file, "waitingFiles/");
		strcat(file, de->d_name);
		strcpy(fileToAdd->filename , file);
		
		waitingFile = fopen(file,"r");
		// to get to end of file
		if(waitingFile != NULL){
			
			// Go to end of the file
			fseek(waitingFile, 0, SEEK_END); 
			fsize = ftell(waitingFile);
			fclose(waitingFile);
			
			printf("\nfilesToHash: \tfilestohash: %s ",file);
			
			
			fileToAdd->sizeOfFile = fsize;
			
			printf("\nfilesToHash: %s with size %d is created", fileToAdd->filename, fileToAdd->sizeOfFile);
			
			table = addToTable(table, fileToAdd);
					
			}
		else{
			printf("\nfilesToHash: file : %s couldnt be opened",de->d_name);
			}
		}
	closedir(dr);
	
	ir = opendir("./waitingFiles/newFiles"); 
	if (ir != NULL){ 
		printf("\nfilesToHash: Checking for new files to hash" ); 

		load = 10;
		while(load == 10){

			
			
			
			for(i=2; i>0 && ((ie = readdir(ir)) != NULL); i--){
				} 
			
			
			while((ie = readdir(ir)) != NULL){
				
				fileToAdd = (files*)malloc(sizeof(files));
				fileToAdd->filename = (char*)malloc(sizeof(char)*1024);
					
				strcpy(file, "waitingFiles/newFiles/");
				strcat(file, ie->d_name);
				strcpy(fileToAdd->filename , file);
				//printf("\n%s, %s",fileToAdd->filename, file);
				if(searchInHashTable(file,table) == -1){
					
					//printf("\n%s", file);
					waitingFile = fopen(file,"r");
					// to get to end of file
					if(waitingFile != NULL){
						// Go to end of the file
						fseek(waitingFile, 0, SEEK_END); 
						fsize = ftell(waitingFile);
						fclose(waitingFile);
						
						fileToAdd->sizeOfFile = fsize;
						table = addToTable(table, fileToAdd);		
						}
					else{
						printf("\nfilesToHash: file : %s couldnt be opened",ie->d_name);
						}
					}
				}
				
			rewinddir(ir);
			printf("\n to keep looking for new files press enter, to stop press something else. ");
			load = getchar();
			}
		 closedir(ir);
		}
	else{
		printf("couldnt open new files");
		} 

	
	
	saveHashTable(table);
    return table; 
	}
	
	
	
// addToHash is for adding new files to hash
hashTable *addToTable(hashTable *table, files *newFile){
	printf("\n");
	printf("\n addtotable: file to add: %s", newFile->filename);
	printf("\n addtotable: table size: %d, file count: %d", table->tableSize, table->fileCount);
	int i = 0;
	int same = 0, key = 0, place = 0;
	int full = 1;
	FILE *fp = NULL;
	

	while(table->fileCount+1 >= (int)(table->tableSize*LoadF)){
		printf("\n addtotable: #files: %d >= tablesize*loadF : %d",table->fileCount+1, (int)(table->tableSize*LoadF));
		printf("\n addtotable: not enough space -> rehash");

		table = reHash(table);
		
		printf("\n addtotable: newly created table size: %d - filecount: %d",table->tableSize, table->fileCount);
		}
		
	if(newFile != NULL){
		
		printf("\n addtotable: searching for place to set the file");
		printf("\n addtotable: sending file to calculatekey(%s)", newFile->filename);
		key = calculateKey(newFile);
		printf("\n addtotable: key for the file: %d", key);
		
		while(full == 1){
			
			place = hash(key,i,table->tableSize);
			printf("\n addtotable: place: %d = hash(key: %d , i: %d , table->tableSize: %d)",place,key,i,table->tableSize);
			
			
			if(table->flags[place] == 1){
				
				// if flag is 1 that means slot is full
				// if the selected slot is full

				printf("\n addtotable: place is already occupied, check if it is same");

				//same = isSame(newFile,table->table[hash(calculateKey(newFile),i,table->tableSize)]);
				same = isSame(newFile,table->table[place]);
				// we check if the file in the slot and the file to be
				// added is the same
				if(same != 1){
					// if files are not the same we increment i and find
					// a new key then we hash again
					printf("\n addtotable: files are not same, looking for the next place, inrementing i");
					
					i++;
					printf("\n addtotable: new i: %d ", i);
					printf("\n addtotable: recalculating the place because it is full with %s, cannot place %s", table->table[place]->filename, newFile->filename);
					printf("\n ---------- ");
					
					}
				else{
					// if files are same we can break out of the while
					printf("\n addtotable: file: %s and newfile: %s are same",table->table[place]->filename, newFile->filename);
					
					full = 0; // deleted line break;
					}
					
				}
			else{
				
				// if flag is 0 -> empty, -1 -> deleted
				// so slot is not full
				// we can get out the while
				printf("\n addtotable: place is empty, we can put the file:%s to place: %d",newFile->filename, place);
				full = 0;
				
				}
				
			}
			
		if(table->flags[place] != 1){	
				
			// after we break out of the while
			// we need to check if the reason of why we are out of
			// the while
			// if the files are the same we dont need to reassign the
			// values
			// if files are not same that means we found an empty slot 
			// or slot that has previously been deleted so we can 
			// put the file to the slot
			
			printf("\n addtotable: files are not same, we found the place, file is in: %d", place);
			
			table->table[place] = newFile;
			table->flags[place] = 1;
			table->fileCount += 1;
			
			fp = fopen("samples.txt", "a+");
			fprintf(fp,"\n%s\n",newFile->filename);
			fclose(fp);
			
			printf("\n addtotable: new file added to table size: %d, filecount: %d", table->tableSize, table->fileCount);	
			}	
		}	
	else{
		printf("\n addtotable: file is NULL, nothing to place ");
		}
	return table;
	}
	
// reHash is used when the hashtable is more than it should 
// to be effective 
hashTable *reHash(hashTable *table){
	//printf("\n");
	//printf("\n\trehash: called for table size: %d, filecount: %d", table->tableSize, table->fileCount);
	
	
	hashTable *tmpTable = (hashTable*)malloc(sizeof(hashTable));
	int i=0;
	FILE *resetSamples;
	
	
	
	tmpTable->tableSize = lenghtOfHashTable((int)(table->tableSize/LoadF));
	tmpTable->fileCount = 0;
	tmpTable->table = (files**)malloc(sizeof(files*)*tmpTable->tableSize);
	tmpTable->flags = (int*)calloc(tmpTable->tableSize,sizeof(int));
	
	printf("\n\trehash: size: %d -> %d", table->tableSize, tmpTable->tableSize);
	
	
	
	if(table->fileCount>0){
		
		printf("\n\trehash: newly created table is empty");
		printf("\n\trehash: should move the old files to new table");
		printf("\n\tsamples.txt is resetted because table will be resetted");
		
		resetSamples = fopen("samples.txt", "w");
		fclose(resetSamples);
		
		
		//printf("\n\trehash: old hash table");
		//printf("\n\t----------------------");
		
		//for (i=0; i < table->tableSize; i++){
			//if(table->flags[i] == 1){
				//printf("\n\t%d - %s flag: %d", i,table->table[i]->filename,table->flags[i]);
				//}
			//}
		}
	for (i=0; i < table->tableSize; i++){
		if(table->flags[i] == 1){
			
			addToTable(tmpTable,table->table[i]);
			printf("\n\trehash: addtotable is called for file: %d name: %s",i,table->table[i]->filename);
			}
		}
		
	printf("\n\trehash: newly created table with size: %d, filecount: %d", tmpTable->tableSize, tmpTable->fileCount);

	return tmpTable;
	}
// isSame checks is to given files are same by checking firstly their size
// then their elements one by one
// size might be not wise if the files has different types
// but we know our files are txt
int isSame(files *first, files *second){
	printf("\n");
	printf("\nissame: %s - %s",first->filename,second->filename);
	int same = 0;
	char ch1, ch2 , tmp1, tmp2;
	int true = 1;
	
	if(first->sizeOfFile == second->sizeOfFile){
		FILE *frst = fopen(first->filename,"r");
		FILE *scnd = fopen(second->filename,"r");
		
		while (true == 1) {
			
			
			
			tmp1 = fgetc(frst); 
			tmp2 = fgetc(scnd); 
			
			//printf("\nissame: %c - %c",tmp1,tmp2);
			
			true = (tmp1 != EOF && tmp2 != EOF);
			true = true && (tmp1 == tmp2);
			if(tmp1 != EOF){
				ch1 = tmp1;
				ch2 = tmp2;
				}
			}
		if(ch1 == ch2){
			same = 1;
			}
		}
	return same;
	}
	
hashTable *makeHashTable(){
	
	hashTable *table = (hashTable*)malloc(sizeof(hashTable));
	
	table->tableSize = 1;
	table->fileCount = 0;
	table->table = (files**)malloc(sizeof(files*)*table->tableSize);
	table->flags = (int*)malloc(sizeof(int)*table->tableSize);	

	return table;
	}

void saveHashTable(hashTable *table){
	
	if(table->fileCount != 0){
		int i = 0;
		FILE *fp = fopen("./hashTable/hashTable.txt", "w+");
		
		if(fp != NULL){
			printf("\nsaveHashTable: file opened succesfuly");
			
			printf("\nsaveHashTable: tableSize: %d is written to the file\n", table->tableSize);
			printf("\nsaveHashTable: fileCount: %d is written to the file\n", table->fileCount);
			
			fprintf(fp,"tableSize: %d \n", table->tableSize);
			fprintf(fp,"fileCount: %d \n", table->fileCount);
			fprintf(fp,"--------------\n");
			for(i=0; i<table->tableSize; i++){
				if(table->flags[i] == 1){
					fprintf(fp,"\n|%d| %d,  %s\n",i,table->flags[i],table->table[i]->filename);
					}
				else{
					//fprintf(fp,"\n0,  empty\n");
					}
			}
		printf("\nHash Table Saved to : ./hashTable/hashTable.txt\n");
		fclose(fp);
			}
		}
	else{
		printf("\nsaveHashTable: hash table is empty, nothing to save");
		}
	
	}
	
	
int searchInHashTable(char *filename, hashTable *table){
	
	int i = -1;
	int result = -1;


	//printf("%s",filename);
	for(i=0;i<table->tableSize;i++){
		if(table->flags[i]==1){
			if(strcmp(filename, table->table[i]->filename) == 0){
				result = i;
				}
			//printf("\n|%s|%s|",filename,table->table[i]->filename);
			}
		}
		

	return result;
	}
	
void deleteFromHashTable(char *filename, hashTable *table){
	int place = searchInHashTable(filename,table);
	if(place >= 0){
		table->flags[place] = -1;
		}
	
	if(table->flags[place] == -1){
		printf("file succesfully deleted");
		}
	else{
		printf("file couldnt be deleted");
		}
	}



