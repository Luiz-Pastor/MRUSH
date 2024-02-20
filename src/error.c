#include "../include/error.h"

void	argument_error(char *name)
{
	printf("Incorrect arguments. Pattern:\n\t%s <TARGET_INI> <ROUNDS> <N_THREADS>\n", name);
	exit(1);
}



void	print_status(char *who, int status)
{
	if (status == PRC_UNEXPECTED)
		printf("%s %s\n", who, UNEXPECTED_MSG);
	else
		printf("%s %s %d\n", who , STATUS_MSG, status);
}
