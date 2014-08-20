#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

#define tostring(x) #x

void parse_args(int argc, char** argv)
{
	// no arguments given
	if(argc == 1) 
	{
		printf("Error: no file supplied. use %s -h for help\n", argv[0]);
		exit(EXIT_FAILURE);
	} 
	// -h flag given, show help
	else if(argc == 2 && strncmp("-h", argv[1], 2) == 0) 
	{
		printf("SlideScript - Simple, everyday use, programming script\n"
		"Arguments:\n\n"
		"-v\t Display version number\n"
		"-h\t Display this help page\n"
		"Usage: %s <filename>\n", argv[0]);
		exit(EXIT_SUCCESS);
	} 
	// -v flag given, show version
	else if(argc == 2 && strncmp("-v", argv[1], 2) == 0) 
	{
		printf("SlideScript %s\n", VERSION);
		exit(EXIT_SUCCESS);
	}
	
}

