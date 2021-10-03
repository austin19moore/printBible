/*

Author:						Austin Moore
File Name:					recursionBible.c

*/

/*
 * Recursively prints bible from memory
*/

// HAVE TO increase stack size for recursion to work, as its past the regular stack limit of 8mb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// for opening file descriptor
#include <fcntl.h>
// for mmap
#include <sys/mman.h>
// for fstat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Recursively prints bible from BibleTxt using the size, and BibleTxt

void printBible(char *BibleTxt, int i, int size) { 
		
	if (i < size) { // base case
		
		return;
		
	}
	
		printf("%c", BibleTxt[i]);
		printBible(BibleTxt, i + 1, size);
		
	}

int main() {
    
	int fDes = open("./bible.txt", O_RDONLY); // file descriptor
	struct stat statStruct; // stat structure for fstat and mmap for length of file
	
	if (fstat(fDes, &statStruct) == -1) { // returns an error if file size was not correctly assigned
		
		printf("Could not get size of file\n");
		return -1;
		
	}
	
	// uses memory map to read bible characters from beginning to end of bible.txt, then assigns them to (private) memory in BibleTxt pointer
	
	char *BibleTxt = mmap(NULL, statStruct.st_size, PROT_READ, MAP_PRIVATE, fDes, 0);
	
	printBible(BibleTxt, 0, statStruct.st_size); // calls recursive function printBible
	
	printf("\n");
	
	munmap(BibleTxt, statStruct.st_size); // frees BibleTxt from memory
	close(fDes); // closes file

    return 0;
}
