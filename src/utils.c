#include "../include/utils.h"

/**
 * Function to close a file descriptor
*/
void	close_better(int *fd)
{
	close(*fd);
	*fd = -1;
}

/**
 * Function to close the pipes used on the programm
*/
void	close_pipes(int *pipe1, int *pipe2)
{
	if (pipe1)
	{
		if (pipe1[0] >= 0)
			close(pipe1[0]);
		if (pipe1[1] >= 0)
			close(pipe1[1]);
	}
	if (pipe2)
	{
		if (pipe2[0] >= 0)
			close(pipe2[0]);
		if (pipe2[1] >= 0)
			close(pipe2[1]);
	}
}