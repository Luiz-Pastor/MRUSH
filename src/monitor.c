#include "../include/monitor.h"

int	write_test(int send, int value)
{
	return (write(send, &value, sizeof(int)) < 0);
}

void	monitor_exit(int send, int recieve, int status)
{
	close(send);
	close(recieve);
	exit(status);
}

void	monitor(int send, int recieve)
{
	long	target, result;
	long	actual;

	while (1)
	{
		/* Leemos el primer numero. Si falla en leer --> Se ha cerrado el pipe */
		if (read(recieve, &target, sizeof(long)) <= 0)
			break ;

		/* Leemos el segundo numero. Si falla, error */
		if (read(recieve, &result, sizeof(long)) < 0)
			monitor_exit(send, recieve, PRC_UNEXPECTED);

		/* Comprobamos si result se equivale al target */
		actual = pow_hash(result);
		if (write_test(send, actual == target))
			monitor_exit(send, recieve, PRC_UNEXPECTED);
	}
	monitor_exit(send, recieve, PRC_OK);
}
