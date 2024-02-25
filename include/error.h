#ifndef ERROR_H
# define ERROR_H

# include "libs.h"
# include "mineria.h"

# define PRC_OK 0
# define PRC_PROBLEM 1
# define PRC_UNEXPECTED 2

# define MINER "Miner"
# define MONITOR "Monitor"
# define STATUS_MSG "exited with status"
# define UNEXPECTED_MSG "exited unexpectedly"

typedef enum {
	COUNT,
	N_THREADS,
	ROUNDS
} ARG_ERR;

void	argument_error(ARG_ERR error, char *name);
void	print_status(char *who, int status);

#endif
