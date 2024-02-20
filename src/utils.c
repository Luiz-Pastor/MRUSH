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
