#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* CHANGING CODE IN PROCESS... CAREFUL ON COMPILING IT */
int skip;
int q_skip;
int f_check;
int f_found;
int main(int argc, char *argv[])
{
	if(argc==2)
	{
		/*...changing code in progress...*/
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
			while ((ch = fgetc(filePointer)) != EOF)
			{
				if(f_found == 1)
				{
					printf("%c", ch);
				}
				if( ch == '\\')
				{
					skip = 1;
					continue;
				}
				else
				{
					//check for \ in previous character
					if(skip == 1)
					{
						skip = 0;
						continue;
					}
					//checks for double quotes
					if(ch == '"')
					{
						//checks if there is a single quote alr
						if(q_skip == 2)
						{
							continue;
						}
						//checks if there is double quote found beforehand
						else if(q_skip == 1)
						{
							q_skip = 0;
							continue;
						}
						//first time found then
						else
						{
							q_skip = 1;
							continue;
						}
					}
					else if(ch == '\'')
					{
						//check if there is double quote alr
						if(q_skip == 1)
						{
							continue;
						}
						//checks if single quote was found beforehand
						else if(q_skip == 2)
						{
						q_skip = 0;
							continue;
						}
						//if not found
						else
						{
							q_skip = 2;
							continue;
						}
					}
					//function (8)
					if(q_skip == 0 && f_found == 0)
					{
						if(f_check == 0)
						{
							if(ch == 'f')
							{
								f_check = 1;
								continue;
							}
							else
							{
								f_check = 0;
							}
						}
						else if(f_check == 1)
						{
							if(ch == 'u')
							{
								f_check = 2;
								continue;
							}
							else
							{f_check = 0;}
						}
						else if(f_check == 2)
						{
							if(ch == 'n')
							{
								f_check = 3;
								continue;
							}
							else
							{f_check = 0;}
						}
						else if(f_check == 3)
						{
							if(ch == 'c')
							{
								f_check = 4;
								continue;
							}
							else{f_check = 0;}
						}
						else if(f_check == 4)
						{
							if(ch == 't')
							{
							f_check = 5;
							continue;
							}
							else{f_check = 0;}
						}
						else if(f_check == 5)
						{
							if(ch == 'i')
							{
							f_check = 6;
							continue;
							}
							else{f_check = 0;}
						}
						else if(f_check == 6)
						{
							if(ch == 'o')
							{
							f_check = 7;
							continue;
							}
							else{f_check = 0;}
						}
						else if(f_check == 7)
						{
							if(ch == 'n')
							{
							f_check = 0;
							f_found = 1;
							continue;
							}
							else{f_check = 0;}
						}
					}
					if(q_skip == 0 && f_found == 1 && ch == '}')
					{
						f_found = 0;
					}
				}
			}
		}
		fclose(filePointer);
	}
	else
	{
		printf("Usage: <args>");
	}
	return 0;
}
