/*
	CSE 109: Spring 2018
	Dylan Spector
	drs320
	Takes in words from the user, stores them each in a bucket, and then prints the words.
	Program #2
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

size_t removeDuplicate(char* line, size_t length, char* duplicate, size_t dupSize);
int addWord(char** bucket, size_t* usedSpace, size_t X,  char* word, size_t inputLength);

// Done
size_t createBucket(size_t X, char** buckets, size_t numBucks, size_t* list); // Returns new number of buckets
void printBucket(char* bucket, size_t usedSpace);

int main(int argc, char** argv)
{
	int intX = 0;
	if(argc > 1)
	{
		for(int i = 0; i < strlen(argv[1]); i++)
		{
			if((int)argv[1][i] >= '0' && (int)argv[1][i] <= '9')
			{
				intX = (10 * intX)  + ((int)argv[1][i] - '0');
			}
			else
			{
				fprintf(stderr, "Error: Non-numerical value inputed for X.\n");
				return 1;
			}
		}
		if(intX < 20 || intX > 100000)
		{
			fprintf(stderr, "Error: X out of bounds.\n");
			return 1;
		}
	}
	if(intX == 0)
	{
		intX = 100;
	}
	if(argc > 2)
	{
		fprintf(stderr, "Error: Invalid argument inputed after X.\n");
		return 1;
	}
	size_t X = (size_t)intX;

//
/*
	char** buckets = (char **)malloc(0);
	size_t numBucks = 0;
	size_t* usedStorageList = (size_t*)malloc(0); // list of remaining storage in bucket
*/
	int wordPlaced = 0;

	size_t numBucks = 0;
	char** buckets = (char **)malloc(((numBucks*2) + 1) * sizeof(char*));
	size_t* usedStorageList = (size_t *)malloc(((numBucks*2)+1) * sizeof(size_t));
	usedStorageList[0] = 0;
	numBucks = 1;

	char* input;
	size_t inputLength = -1;
	while(fscanf(stdin, "%ms", &input) != EOF)
	{
		inputLength = strlen(input) + 1;
		// Try to remove from bucket

		// Else try add to bucket
		for(size_t i = 0; i < numBucks; i++)
		{
			if(!wordPlaced)
			{
				wordPlaced = addWord(&buckets[i], &usedStorageList[i], X, input, inputLength);
			}
			else
			{
				wordPlaced = 0;
				break;
			}
		}
				// else make new bucket
					//place word in new bucket
		for(int i = 0; i < numBucks; i++)
		{
   			printBucket(buckets[i], usedStorageList[i]);
		}
	}

	for(int i = 0; i < numBucks; i++)
   	{
    	printBucket(buckets[i], usedStorageList[i]);
   	}

	return 0;
}

/* Attempts to remove *duplicate from *line. If no dup is found, no changes are made
   length is size of *line, dupSize. Returns the resulting size for the line.*/
/*size_t removeDuplicate(char* line, size_t length, char* duplicate, size_t dupSize)
{
	int tempChar = -1; // holds a char temp while removing a word
	int wordFound = 0; // true or false
	size_t index = -1; // Index of start of duplicate word.

	// Loop through every char in *line (a.k.a. a bucket)
	for(size_t i = 0; i < length; i++)
	{
		if(wordFound)
		{
			break;
		}
		// If the first char of *duplicate is found in *line
		if(line[i] == duplicate[0])
		{
			// For every char in *duplicate
			for(size_t j = 1; j < dupSize; j++)
			{
				if(line[i+j] == duplicate[j])
				{
					// If a null pointer is found
					if(duplicate[j] == NULL)
					{
						wordFound = 1;
						index = i;
					}
				}
				else
				{
					break; // This is a different word.
				}
			}
		}
	}
	if(wordFound)
	{
		// Remove word
		for(size_t i = index; i < dupSize; i++)
		{
			line[i] = '\0'; // Set char of word to NULL
			int movingIndex = i;
			for(size_t j = i+1 ; j < length; j++)
			{
				tempChar = line[movingIndex];
				line[movingIndex] = line[j];
				line[j] = tempChar;
				movingIndex++;
			}
		}
	}

	return strlen(line);
}*/









int addWord(char** bucket, size_t* usedSpace, size_t X,  char* word, size_t inputLength)
{
	if(X - *usedSpace >= inputLength)
	{
		for(size_t i = *usedSpace; i < X; i++)
		{
			size_t j = 0;
			if(j < inputLength - 1)
			{
				*bucket[i] = word[j];
				j++;
			}
			else
			{
				*usedSpace =  *usedSpace + inputLength;
				return 1;
			}
		}
	}
	return 0;
}



//DONE
/* Creates a new List of Buckets = (capacity of buckets) + 1. Free's buckets and points
   buckets to Buckets. Pass &numBucks numBucks = numBuckks++*/
size_t createBucket(size_t X, char** buckets, size_t numBucks, size_t* list)
{
	// Allocates memory = the mem
	char** tempBucks = (char **)malloc((numBucks*2)+1 * sizeof(char*));
	size_t* tempList = (size_t *)malloc((numBucks*2)+1 * sizeof(size_t));

	// Copy contents of buckets to tempBucks & lists.
	for(int i = 0; i < numBucks; i++)
	{
		tempBucks[i] = buckets[i];
		tempList[i] = list[i];
		if(!tempList[i]) // If null
		{
			tempList[i] = 0;
		}
	}

	// Create new Bucket
	tempBucks[numBucks] = (char *)malloc(X * sizeof(char)); // X may need to become size_t
	tempList[numBucks] = 0; // no storage has been used

	// Makes buckets point to tempBucks
	free(buckets);
	buckets = NULL;
	buckets = tempBucks;

	// Makes list point to tempList
	free(list);
	list = NULL;
	list = tempList;
	fprintf(stdout, "%ld\n", list[0]);
	numBucks++; // Increase the counter for the number of buckets created by 1.

	return numBucks;
}

// DONE
void printBucket(char* bucket, size_t usedSpace)
{
	fprintf(stdout, "%6d: ", (int)usedSpace); // R-A by 6, '<used Space>: '

	for(size_t i = 0; i < usedSpace; i++)
	{
		if(bucket[i] != '\0')
		{
			fprintf(stdout, "%c", bucket[i]);
		}
		else if(i != usedSpace-1) // if not the last null
		{
			fprintf(stdout, " ");
		}
		else
		{
			fprintf(stdout, "\n");
		}
	}
	return;
}
