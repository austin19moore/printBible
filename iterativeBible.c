/*

Author:						Austin Moore
Assignment Number:			Lab 1
File Name:					main.c // 1b iterative
Course/Section				CS 2124 OC1
Due Date:					9/23/21
Instructor:					Dr. Bernard

*/

/*
 * Iteratively prints Bible from memory
*/

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

int main() {
    
	int fDes = open("./bible.txt", O_RDONLY); // opens file descriptor
	struct stat statStruct; // stat structure for fstat and mmap for length of file
	
	if (fstat(fDes, &statStruct) == -1) {
		
		printf("Could not get size of file\n");
		return -1;
		
	}
	
	/* uses memory map to read bible characters from beginning to end of bible.txt, then assigns them to (private) memory in BibleTxt pointer
	*/
	
	char *BibleTxt = mmap(NULL, statStruct.st_size, PROT_READ, MAP_PRIVATE, fDes, 0);
	
	// iteratively prints bible backwards from length of bible.txt (statStruct.st_size)
	
	for (int i = 0; i < statStruct.st_size; i++) {
		
		printf("%c", BibleTxt[i]);
		
	}
	
	printf("\n");
	
	munmap(BibleTxt, statStruct.st_size); // frees BibleTxt from memory
	close(fDes); // closes file

    return 0;
}
