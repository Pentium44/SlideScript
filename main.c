/*
	SlideScript - Basic scripting for everyday use
	(C) Copyright 2014 Chris Dorman - some rights reserved (GPLv3)

	View read me file supplied with this software
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define CHUNKSIZE 2048

// Version
char *ss_version = "1.0";

// StrTok characters
char *char_equal = "=";
char *char_quote = "\"";
char *char_space = " ";
char *char_bracket_open = "[";
char *char_bracket_close = "]";

// Mem struct. All buffers are written here.
//struct mem
//{
//	char bufchunk[CHUNKSIZE];
//};

int main(int argc, char **argv) 
{
	/*
		Variables
	*/

	char script_line[512];
	char *tok_srch;
	
	// Check to see if help was called or if a file path was provided.
	if(argc == 1) 
	{
		printf("Error: no file supplied. use %s -h for help\n", argv[0]);
		exit(1);
	} 
	else if(argc == 2 && strncmp("-h", argv[1], 2) == 0) 
	{
		printf("SlideScript - Simple, everyday use, programming script\n"
		"Arguments:\n\n"
		"-v\t Display version number\n"
		"-h\t Display this help page\n"
		"Usage: %s <filename>\n", argv[0]);
		exit(0);
	} 
	else if(argc == 2 && strncmp("-v", argv[1], 2) == 0) 
	{
		printf("SlideScript v%s\n", ss_version);
		exit(0);
	}
	
	/*
		Main system
	*/
	
	FILE *script = fopen(argv[1], "r");
	
	// check if config opens successfully
	if(access(argv[1], F_OK) == -1) {
		printf("Error: failed to open %s.\n", argv[1]);
		exit(1);
	}
		
	// Run while loop if file is empty.
	if(script != NULL) 
	{
			
		// parse each line from the script in order.
		while(fgets(script_line, sizeof(script_line), script) != NULL) 
		{
			tok_srch = strtok(script_line, "=\" ");
			
			// if line starts with a comment, skip
			if(strncmp("#",tok_srch,1) == 0 || strncmp("//",tok_srch,2) == 0)
			{
				continue;
			} // comment skip
			
			// print function
			if(strncmp("print",tok_srch,5) == 0)
			{
				tok_srch = strtok(NULL, char_quote);
				printf("%s\n", tok_srch);
			} // print function
			
			// sleep function
			if(strncmp("sleep",tok_srch,5) == 0)
			{
				tok_srch = strtok(NULL, char_space);
				
				// if there is a new line, remove it
				if(tok_srch[strlen(tok_srch)-1] == '\n') 
				{
					tok_srch[strlen(tok_srch)-1] = 0;
				}
				
				sleep(atoi(tok_srch));
				
			} // sleep function
			
			// write
			if(strncmp("write",tok_srch,5) == 0)
			{
				// strtok to filename of function
				tok_srch = strtok(NULL, char_quote);
				
				// Check if file exists and can be opened
				if(access(tok_srch, F_OK) == -1) 
				{
					printf("Warning: %s does not exist, creating file.\n", tok_srch);
				}
				
				FILE *write_file = fopen(tok_srch, "w");
				
				// Check if file opened
				if(write_file == NULL) 
				{
					printf("Error: failed to write to %s.\n", tok_srch);
					continue;
				}
				
				// strtok to the content that will be written to file
				tok_srch = strtok(NULL, char_quote);
				tok_srch = strtok(NULL, char_quote);
				
				fprintf(write_file, "%s\n", tok_srch);
				
				fclose(write_file);
				
			} // write function
			
			// read function
			if(strncmp("read",tok_srch,4) == 0)
			{
				// strtok to filename of function
				tok_srch = strtok(NULL, char_quote);
				
				// Check if file exists and can be opened
				if(access(tok_srch, F_OK) == -1) 
				{
					printf("Error: failed to open %s.\n", tok_srch);
					continue;
				}
				
				FILE *read_file = fopen(tok_srch, "r");
				
				// Check if file opened
				if(read_file == NULL) 
				{
					printf("Error: failed to read %s.\n", tok_srch);
					continue;
				}
				
				char read_line[1024];
				
				while(fgets(read_line, sizeof(read_line), read_file) != NULL) 
				{
					printf("%s\n", read_line);
				}
				
				fclose(read_file);
			} // read function
			
		} // end of while
	} // file null
		
	fclose(script);
	
	exit(0);
}
