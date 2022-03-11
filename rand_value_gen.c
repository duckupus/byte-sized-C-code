#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

void help(char **argv) {
	printf("Usage: %s [OPTION]\n", argv[0]);
	printf("helps find strings with a fixed random seed\n");
	printf("Options:\n");
	printf(" -h, --help				shows help list\n");
	printf(" -s [value], --seed [value]		uses value as seed value\n");
	printf(" -w [value], --word [value]		helps find value with rand\n");
	printf("Optional arguments:\n");
	printf(" -M [value], --Max [value]		mods rand by that value(default: 1000)\n");
	printf(" -m [value], --min [value]		adds to rand by that value\n");
	printf(" -f, --fast				limits values to printable ascii range(overrides --Max and --min)\n");
	printf("-o [outfile], --output [outfile]	select files to give output to\n");

	exit(0);
}

int main(int argc, char **argv) {
	/*
	 * NOTE: This is not good programming, do not follow
	 */
	if(argc < 2) {
		help(argv);
	}
	char *word, *filename;
	int opt, seed, max = 1000, min = 0, fast = 0, runsize = 0;
	int filemode = 0;
	FILE *outfile;
	static struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"seed", required_argument, NULL, 's'},
		{"word", required_argument, NULL, 'w'},
		{"Max", required_argument, NULL, 'M'},
		{"min", required_argument, NULL, 'm'},
		{"fast", no_argument, NULL, 'f'},
		{"output", required_argument, NULL, 'o'},
	};
	printf("Initializing values...\n");
	while((opt = getopt_long(argc, argv, "hs:w:M:m:fo:", long_options, NULL)) != -1) {
		switch(opt) {
			case 'h':
				help(argv);
				break;
			case 's':
				seed = atoi(optarg);
				break;
			case 'w':
				word = optarg;
				break;
			case 'M':
				max = atoi(optarg);
				break;
			case 'm':
				min = atof(optarg);
				break;
			case 'f':
				fast = 1;
				break;
			case 'o':
				outfile = fopen(optarg, "w");
				filename = optarg;
				filemode = 1;
				break;
		}
	}
	if(fast) {
		min = 31;
		max = 128;
	}
	/* Error checking */
	if(word == NULL) {
		printf("Error: no phrase chosen!\n");
		printf("Exitting!\n");
		exit(1);
	}
	printf("Checking maximum and minimum values...\n");
	if(max < 127 || min > 32) {
		for(int i = 0; i < strlen(word); i++) {
			if(word[i] >= max) {
				max = (int)word[i] + 1;
				printf("Changed maximum value to %d\n", max);
			} else if(word[i] <= min) {
				min = (int)word[i] - 1;
				printf("Changed minimum value to %d\n", min);
			}
		}
	}
	/* end error checking */
	printf("seed:\t%d\n", seed);
	printf("phrase:\t%s\n", word);
	printf("maximum value: %d\n", max);
	printf("minimum value: %d\n", min);
	if(filemode) {
		printf("filename: %s\n", filename);
		fputs("#include <stdio.h>\n", outfile);
		fputs("#include <stdlib.h>\n", outfile);
		fputs("int main() {\n", outfile);
		fputs("\tint i = 0, size = 0;\n", outfile);
		fprintf(outfile, "\tsrand(%d);\n", seed);
		fputs("\twhile(i != 1) {\n", outfile);
		fputs("\t\tswitch(size) {\n", outfile);
	}
	srand(seed);

	for(int i=0; i < strlen(word); i++) {
		while(word[i] != ((rand() % max) + min)) {
			runsize++;
		}
		if(filemode) {
			fprintf(outfile, "\t\t\tcase %d:\n", runsize);
			fputs("\t\t\t\tprintf(\"\%c\", ((rand() % ", outfile);
			fprintf(outfile, " %d) + %d));\n", max, min);
			if(i == strlen(word) - 1) {
				fputs("\t\t\t\t i = 1;\n", outfile);
			}
			fputs("\t\t\t\tbreak;\n", outfile);
		} else {
			printf("letter: %c: %d\n", word[i], runsize);
		}
		runsize++;
	}
	if(filemode) {
		fputs("\t\t\tdefault:\n", outfile);
		fputs("\t\t\t\trand();\n\t\t\t\tbreak;\n", outfile);
		fputs("\t\t\t}\n", outfile);
		fputs("\t\tsize++;\n", outfile);
		fputs("\t}\n\tprintf(\"\\n\");\n\treturn 0;\n", outfile);
		fputs("}", outfile);
	}
	return 0;
}
