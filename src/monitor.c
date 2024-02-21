#include "../include/monitor.h"

void	write_test(int send, int value)
{
	if (value)
		write(send, "1", 1);
	else
		write(send, "0", 1);
}

void	monitor_exit(int send, int recieve, int status)
{
	close(send);
	close(recieve);
	exit(status);
}

void	monitor(int send, int recieve)
{
	int		length;
	char	buffer[9];
	long	target, result;
	long	actual;

	while (1)
	{
		/* Leemos el primer numero. Si falla en leer --> Se ha cerrado el pipe */
		length = read(recieve, buffer, 8);
		if (length <= 0)
			break ;
		buffer[length] = '\0';
		target = atol(buffer);

		/* Leemos el segundo numero */
		length = read(recieve, buffer, 8);
		buffer[length] = '\0';
		result = atol(buffer);

		/* Comprobamos si result se equivale al target */
		actual = pow_hash(result);
		write_test(send, actual == target);
	}
	monitor_exit(send, recieve, PRC_OK);
}
