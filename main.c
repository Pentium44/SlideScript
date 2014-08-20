/*
	SlideScript - Basic scripting for everyday use
	(C) Copyright 2014 Chris Dorman - some rights reserved (CC-BY-SA 3.0)

	View read me file supplied with this software
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "util.h"

#define CHUNKSIZE 2048

/* Mem struct. All buffers are written here. */
/*
struct mem
{
	char bufchunk[CHUNKSIZE];
};
*/

int main(int argc, char **argv) 
{
	FILE* script;
	char script_line[512];
	char* tok_srch;

	parse_args(argc, argv);

	script = fopen(argv[1], "r");
	
	/* check if config opens successfully */
	if(script == NULL) {
		printf("Error: failed to open %s.\n", argv[1]);
		exit(EXIT_FAILURE);
	}
		
	/* Run while loop if file is empty. */
	if(script != NULL) 
	{
			
		/* parse each line from the script in order. */
		while(fgets(script_line, sizeof(script_line), script) != NULL) 
		{
			tok_srch = strtok(script_line, "=\" ");
			
			/* if line starts with a comment, skip */
			if(strncmp("#",tok_srch,1) == 0)
			{
				continue;
			} /* comment skip */
			
			/* print function */
			if(strncmp("print",tok_srch,5) == 0)
			{
				tok_srch = strtok(NULL, "\"");
				printf("%s\n", tok_srch);
			} /* print function */
			
			/* sleep function */
			if(strncmp("sleep",tok_srch,5) == 0)
			{
				tok_srch = strtok(NULL, " ");
				
				/* if there is a new line, remove it */
				if(tok_srch[strlen(tok_srch)-1] == '\n') 
				{
					tok_srch[strlen(tok_srch)-1] = 0;
				}
				
				sleep(atoi(tok_srch));
				
			} /* sleep function */
			
			/* write */
			if(strncmp("write",tok_srch,5) == 0)
			{
				FILE* write_file = NULL;

				/* strtok to filename of function */
				tok_srch = strtok(NULL, "\"");
				
				/* open file */
				write_file = fopen(tok_srch, "w");

				/* Check if file exists and can be opened */
				if(write_file == NULL) 
				{
					printf("Warning: Cannot write to %s.\n", tok_srch);
				}
				
				
				/* Check if file opened */
				if(write_file == NULL) 
				{
					printf("Error: failed to write to %s.\n", tok_srch);
					continue;
				}
				
				/* strtok to the content that will be written to file */
				tok_srch = strtok(NULL, "\"");
				tok_srch = strtok(NULL, "\"");
				
				fprintf(write_file, "%s\n", tok_srch);
				
				fclose(write_file);
				
			} /* write function */
			
			/* read function */
			if(strncmp("read",tok_srch,4) == 0)
			{
				char read_line[1024];
				FILE *read_file = NULL;

				/* strtok to filename of function */
				tok_srch = strtok(NULL, "\"");
				
				/* open file */
				read_file = fopen(tok_srch, "r");

				/* Check if file was opened successfully */
				if(read_file == NULL) 
				{
					printf("Error: failed to open %s.\n", tok_srch);
					continue;
				}
				
				while(fgets(read_line, sizeof(read_line), read_file) != NULL) 
				{
					printf("%s", read_line);
				}
				
				fclose(read_file);
			} /* read function */
			
		} /* end of while */
	} /* file null */
		
	fclose(script);
	
	exit(EXIT_SUCCESS);
}

