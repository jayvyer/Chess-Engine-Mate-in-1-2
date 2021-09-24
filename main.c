#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RANK_OF(pos)			(8 - ((pos)/8) + '0') /* Obtain the rank of a square given its pos */
#define FILE_OF(pos)			(((pos) % 8) + 'a')   /* Obtain the file of a square given its pos */


int main(int argc, char *argv[]) {
	char str[100];
	FILE *fp;
	FILE *fptr;
	fp = fopen(argv[1], "r");
	fptr = fopen("solution.txt", "w");
	if(fp == NULL){
		printf("Error!");
	}
	while(fgets(str, 100, fp) != NULL){
		char move[] = {RANK_OF(6), FILE_OF(6), '-', RANK_OF(8), FILE_OF(8), '\n', '\0'};
		fputs(move, fptr);
	}
	fclose(fp);
	fclose(fptr);
	return 0;
}
