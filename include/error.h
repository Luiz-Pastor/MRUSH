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

void	argument_error(char *name);
void	print_status(char *who, int status);

#endif
