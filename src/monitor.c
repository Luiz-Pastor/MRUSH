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
	char	buffer[18];
	char	*target, *result;
	long	nmr_target, nmr_result;
	long	actual;

	while (1)
	{
		length = read(recieve, buffer, 17);
		
		/* Si falla en leer --> Se ha cerrado el pipe */
		if (length <= 0)
			break ;
		buffer[length] = '\0';

		/* Leemos lo que nos han pasado: target\nresult */
		target = strtok(buffer, "\n");
		result = strtok(NULL, "\n");
		if (!target || !result)
			monitor_exit(send, recieve, PRC_UNEXPECTED);
	
		/* Lo convertimos a numero */
		nmr_target = atol(target);
		nmr_result = atol(result);

		/* Comprobamos si result se equivale al target */
		actual = pow_hash(nmr_result);
		write_test(send, actual == nmr_target);
	}
	monitor_exit(send, recieve, PRC_OK);
}
