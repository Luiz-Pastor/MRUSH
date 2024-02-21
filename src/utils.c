#include "../include/utils.h"

void	close_better(int *fd)
{
	close(*fd);
	*fd = -1;
}

int number_length(long number)
{
	int	count = 0;

	if (number == 0)
		return 1;
	if (number < 0)
		number *= -1;
	
	while (number > 0)
	{
		number /= 10;
		count++;
	}
	return (count);
}

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