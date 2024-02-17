#include "../include/error.h"

void	argument_error(char *name)
{
	printf("Incorrect arguments. Pattern:\n\t%s <TARGET_INI> <ROUNDS> <N_THREADS>\n", name);
	exit(1);
}

void	fork_error()
{
	perror("Fork error");
	exit(1);
}
