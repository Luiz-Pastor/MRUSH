#include "../include/error.h"

/**
 * Function to handle program argument errors
*/
void	argument_error(ARG_ERR err, char *arg)
{
	printf(C_RED"[ ERROR ] "CLEAR);
	switch (err)
	{
		case COUNT:
			printf("Incorrect arguments. Pattern:\n\t\t%s%s <TARGET_INI> <ROUNDS> <N_THREADS>%s\n", C_CYAN, arg, CLEAR);
			break ;
		case N_THREADS:
			printf("Incorrect number of threads (\"%s%s%s\")\n", C_CYAN, arg, CLEAR);
			break ;
		case ROUNDS:
			printf("Incorrect number of rounds (\"%s%s%s\")\n", C_CYAN, arg, CLEAR);
			break ;
		default:
			break ;
	}

	exit(1);
}

/**
 * Function to report how a process has gone
*/
void	print_status(char *who, int status)
{
	if (status == PRC_UNEXPECTED)
		printf("%s %s\n", who, UNEXPECTED_MSG);
	else
		printf("%s %s %d\n", who , STATUS_MSG, status);
}
