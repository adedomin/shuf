/*
shuf implementation

Copyright (c) 2014 Anthony DeDominic

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// doesn't do anything yet...
void readStdin(char **read_buffer)
{

	size_t file_size = 512;
	if (stdin == NULL)
	{
		printf("unknown failure\n");
		exit(EXIT_FAILURE);
	}

	*read_buffer = (char*) malloc(file_size);
	if (read_buffer == NULL)
	{
		printf("allocation fail\n");
		exit(EXIT_FAILURE);
	}
	
	fgets(*read_buffer, 512, stdin);
	
	fclose(stdin);
}

int splitInput(char **buffer, char ***split_array, char delim[])
{
	unsigned int number_of_strings = 0;
	char *temp;

	temp = strpbrk(*buffer, delim);
	while (temp != NULL)
	{
		number_of_strings++;
		temp = strpbrk(temp+1, delim);
	}

	*split_array = (char**) malloc(number_of_strings*sizeof(char*));
	if (*split_array == NULL)
	{
		printf("memory failure");
		exit(EXIT_FAILURE);
	}
	
	temp = strtok(*buffer, delim);
	int itr;
	for (itr=0; temp != NULL; itr++)
	{
		(*split_array)[itr] = temp;
		temp = strtok(NULL, delim);
	}

	return number_of_strings;
}

// returns int [min, max)
int uniform(int min, int max)
{
	int range = max - min;
	return min + rand() % range;
}

// I think it works as intended?
void shuffle(char ***array, int size)
{
	for (int itr = 0; itr < size; itr++)
	{
		int pos = uniform(itr, size);
		char *temp  = (*array)[itr];
		(*array)[itr] = (*array)[pos];
		(*array)[pos] = temp;
	}
}

// flags not implemented
int main(int argc, char *argv[])
{
	srand(time(NULL));
	if (argc > 1)
	{
		argv++;
		argc--;
		shuffle(&argv, argc);
		for (int itr=0; itr < argc; itr++)
		{
			printf("%s\n", argv[itr]);
		}
	}
	else
	{
		char *buffer = NULL; //read buffer
		readStdin(&buffer);

		char **split_buffer = NULL; // splits read buffer by delimiters
		int string_count = splitInput(&buffer, &split_buffer, "\n ");
		shuffle(&split_buffer, string_count);

		for (int itr = 0; itr < string_count; itr++) 
		{
			printf("%s\n", split_buffer[itr]);
		}
	}

	
	return 0;
}

// testing shuffling
// should be 50, 50 chance of first position being a 1 or 2
//int main()
//{
//	srand(time(NULL));
//	int inorder = 0;
//	int outorder= 0;
//	for (int x=0; x < 1000; x++)
//	{
//		char *test[] = {"1","2"};
//		char **ptrtest = test;
//		shuffle(&ptrtest, 2);
//		if (strcmp(test[0], "1"))
//		{
//			inorder++;
//		}
//		else
//		{
//			outorder++;
//		}
//	}
//
//	printf("order: %d, out of order: %d", inorder, outorder);
//}


	
