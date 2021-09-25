#include <stdio.h>
#include <string.h>
void help() {
	puts("Usage:");
	puts("provide one input to read from the specified file");
	puts("Otherwise, the code will read as arguments given when first running the script");
}
int main(int argc, char **argv) {
	//just prints help
	int wc=0, i=0;
	if(argc==1) {
		help();
		return 0;
	}
	if(strcmp(argv[1], "-h")==0 || strcmp(argv[1], "--help")==0)
		help();
	if(argc==2) {
		FILE *filePointer;
		char ch;
		filePointer = fopen(argv[1], "r");
		if (filePointer == NULL)
		{
			printf("File is not available \n");
			return 1;
		}
		else
		{
			while ((ch = fgetc(filePointer)) != EOF) {
				//thanks to @Plehnoh for helping!
				if(ch == '\n' || ch == ' ' || ch == '\t') {
					i++;
				}
				if(i<2 && (ch == '\n' || ch == ' ' || ch == '\t')) {
					wc++;
					continue;
				}
				if(ch != '\n' || ch != ' ' || ch != '\t') {
					i=0;
				}
			}
		}
		printf("Word count: %d\n", wc);
		fclose(filePointer);
	}
	else {
		//yes... its not that difficult
		wc=argc-1;
		printf("Word count: %d\n",wc);
	}
	return 0;
}
