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

/*
 * @brief Function to handle program argument errors
 * 
 * @param error The type of error
 * @param arg Text that prints to help understand the error
*/
void	argument_error(ARG_ERR error, char *arg);

/*
 * @brief Function to report how a process has gone
 * 
 * @param who Name of the process
 * @param status Process return value
*/
void	print_status(char *who, int status);

#endif
