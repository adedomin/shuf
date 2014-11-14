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
#include <time.h>

int readStdin(char *array[])
{
	return 0;
}

void shuffle(char *array[], int size)
{
	char *temp;
	srand(time(NULL));

	for (int itr = 0; itr < size; itr++)
	{
		int pos = itr + (rand() % (size-1) - itr);
		temp  = array[itr];
		array[itr] = array[pos];
		array[pos] = temp;
	}
}

int main(int argc, char *argv[])
{
	if (argc > 1)
	{
		argv++;
		argc--;
		shuffle(argv, argc);
	}
	else
	{
		argc = readStdin(argv);
	}

	for (int itr=0; itr < argc; itr++)
	{
		printf("%s\n", argv[itr]);
	}
	
	return 0;
}
