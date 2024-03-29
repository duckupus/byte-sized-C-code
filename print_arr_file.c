#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

static inline void failed_malloc() { //helper
	fprintf(stderr, "Failed to allocate memory\n");
	exit(-1);
}


size_t filelen = 0;
char *readfile(char *path) { //returns entire file content, including EOF
	FILE *fp = fopen(path, "rb");
	if(fp == NULL) {
		fprintf(stderr, "cannot open file\n");
		return NULL;
	}
	char *contents;
	fseek(fp, 0, SEEK_END);
	filelen = ftell(fp);
	fseek(fp, 0, SEEK_SET); //get file length and return to start again
	contents = malloc(filelen*sizeof(char) + 1); //add EOF
	if(contents == NULL) return NULL; //return to allow cleanup
	fread(contents, filelen, 1, fp);
	contents[filelen] = EOF;
	return contents;
}

static void help(char *argv) {
	printf("Usage: %s [OPTIONS]\n", argv);
	printf("prints file values in different fashion\n");
	printf("Options: \n");
	printf(" -f, --file [filename]		file to get values of\n");
	printf(" -c, --c-array			print contents in C array\n");
	exit(0);
}

static struct option long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"file", required_argument, NULL, 'f'},
	{"c-array", no_argument, NULL, 'c'},
	{NULL, 0, NULL, 0}
};

void printContents(char *content) {
	for(int i = 0; i < filelen; i++) putchar(content[i]);
}

void printCArray(char *content, char *filename) {
	printf("char %s_arr[%lu] = { ", filename, filelen);
	for(int i = 0; i < filelen-1; i++) {
		printf("0x%02x, ", content[i]);
	}
	printf("0x%02x };\n", content[filelen-1]);
}


int main(int argc, char **argv) {
	int opt;
	char *infile = NULL;
	size_t infile_path_len = 0;
	int c_array = 0;
	if(argc < 2) help(argv[0]);

	while((opt = getopt_long(argc, argv, "hf:c", long_options, NULL)) != -1) {
		switch(opt) {
			case 'f':
				infile_path_len = strlen(optarg);
				infile = malloc(sizeof(char)*infile_path_len + 1); //including NULL character
				if(infile == NULL) failed_malloc();
				memcpy(infile, optarg, infile_path_len);
				infile[infile_path_len] = 0x0;
				break;
			case 'c':
				c_array = 1;
				break;
			case 'h':
			default:
				help(argv[0]);
				break;
		}
	}
	if(infile == NULL) {
		fprintf(stderr, "Please provide an input file\n");
		exit(-1);
	}
	char *contents = readfile(infile);
	if(c_array == 1) {
		printCArray(contents, infile);
	} else {
		printContents(contents);
	}
	free(contents);
	free(infile);
	return 0;
}

