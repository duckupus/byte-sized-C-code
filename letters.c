#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

char var=' ';

void help(void) {
	puts("Usage:");
	puts("-h, --help\n\t displays this help message");
	puts("-b, --bigalp\n\t converts letters to big letters");
	puts("-s, --smallalp\n\t converts letters to small letters");
	puts("-t=[value], --togglealp=[value]\n\t toggles letter capitalisation");
	puts("e.g.\n./letters -t=0   toggles from first letter\naaaa\nAaAa");
	puts("./letters --togglealp=1   toggles from 2nd letter\naaaa\naAaA");
	puts("NOTE: if no flags are given, default is converting to big letters");
}

void uppercaseconv(void) {
	while(var != EOF) {
		var=getc(stdin);
		if(var >= 'a' && var <= 'z')
			printf("%c", var-32);
		else
			printf("%c", var);
	}
	fclose(stdin);
}

void lowercaseconv(void) {
	while(var != EOF) {
		var=getc(stdin);
		if(var >= 'A' && var <= 'Z')
			printf("%c", var+32);
		else
			printf("%c", var);
	}
	fclose(stdin);
}

void toggleconv(int toggle_at) {
	int i=0;
	while(var != EOF) {
		var=getc(stdin);
		if(i == toggle_at){
			/* checks range */
			if(var <= 'z' && var >= 'A') {
				if(var <= 'Z')
					printf("%c", var+32);
				if(var >= 'a')
					printf("%c", var-32);
			} else
				printf("%c", var);
			i=-1;
		}
		printf("%c", var);
		i++;
	}
	fclose(stdin);
}

int main(int argc, char *argv[]) {
	int i, opt=0, toggle;
	static struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"bigalp", no_argument, NULL, 'b'},
		{"smallalp", no_argument, NULL, 's'},
		{"togglealp", required_argument, NULL, 't'}
	};
	while((i = getopt_long(argc, argv, "hbst:", long_options, NULL)) != -1) {
		switch(i) {
			case 'h':
				help();
				return 0;
				break;
			case 'b':
				opt=0;
				break;
			case 's':
				opt=1;
				break;
			case 't':
				toggle = atoi(optarg);
				opt = 2;
				break;
		}
	}
	switch(opt) {
		case 0:
			uppercaseconv();
			break;
		case 1:
			lowercaseconv();
			break;
		case 2:
			toggleconv(toggle);
			break;
	}
	return 0;
}
