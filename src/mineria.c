#include "../include/mineria.h"

void	miner_exit(t_miner *miners, int *pipe1, int *pipe2, int status)
{
	int	monitor;

	if (miners)
		free(miners);
	close_pipes(pipe1, pipe2);

	if (wait(&monitor) != -1)
		print_status(MONITOR, WEXITSTATUS(monitor));
	
	exit(status);
}

static void	*search(void *arg)
{
	t_miner *miner;
	long	result;

	if (!arg)
		return (NULL);

	/* Recuperampos la estructura */
	miner = (t_miner *)arg;

	/* Buscamos el numero hasta que algun hilo lo encuentre */
	while (miner->start <= miner->end && *(miner->finish) == NOT_FOUND)
	{
		/* Obtenemos el hash de este numero */
		result = pow_hash(miner->start);

		/* Comparamos el hash obtenido con el que tenemos que buscar */
		if (result == miner->target)
		{
			/* Si encontramos el hash, lo guardamos, terminamos todos los hilos y salimos */
			miner->result = miner->start;
			*(miner->finish) = FOUND;
			break ; // Una alternativa seria pthread_exit()
		}

		/* Si no lo encontramos, seguimos iterando */
		(miner->start)++;
	}
	return (NULL);
}

static void	init_miners(long target, int *finish, long n_threads, t_miner *miners)
{
	int	i;

	*finish = NOT_FOUND;
	for (i = 0; i < n_threads; i++)
	{
		miners[i].target = target;
		miners[i].start = (POW_LIMIT / n_threads) * i;
		miners[i].end = (POW_LIMIT / n_threads) * (i + 1) - 1;
		miners[i].result = -1;
		miners[i].finish = &(*finish);
	}
}

static long	get_result(int n_threads, t_miner *miners)
{
	int	i;

	for(i = 0; i < n_threads; i++)
	{
		if (miners[i].result != -1)
			return (miners[i].result);
	}
	return NOT_FOUND;
}

int	send_request(int send, long target, long result)
{
	if (write(send, &target, sizeof(long)) < 0)
		return (1);
	if (write(send, &result, sizeof(long)) < 0)
		return (1);
	return (0);
}

int	recieve_request(int request)
{
	int buffer;

	if (read(request, &buffer, sizeof(int)) < 1)
		return (-1);
	return (buffer);
}

void	mineria(long target, long rounds, long n_threads)
{
	t_miner	*miners;
	long	i, j;
	int		finish;
	long	result;
	int		request;
	int		send[2], recieved[2];
	pid_t	monitor_pid;

	/* Abrimos los pipes para la comunicacion mineria-monitor*/
	if (pipe(send))
		miner_exit(NULL, NULL, NULL, PRC_UNEXPECTED);
	
	if (pipe(recieved))
		miner_exit(NULL, send, NULL, PRC_UNEXPECTED);

	/* Crear el monitor */
	monitor_pid = fork();
	if (monitor_pid < 0)
		miner_exit(NULL, send, recieved, PRC_UNEXPECTED);
	if (monitor_pid == 0)
	{
		close_better(&send[1]);
		close_better(&recieved[0]);
		monitor(recieved[1], send[0]);
	}
	close_better(&send[0]);		/* Mandamos por send[1] */
	close_better(&recieved[1]);	/* Leemos por recieved[0] */

	/* Crear las estructuras que vamos a pasar */
	miners = malloc(n_threads * sizeof(t_miner));
	if (!miners)
		miner_exit(NULL, NULL, NULL, PRC_UNEXPECTED);

	for (i = 0; i < rounds; i++)
	{
		/* Dar datos a todos los hilos */
		init_miners(target, &finish, n_threads, miners);

		/* Iniciar los hilos */
		for (j = 0; j < n_threads; j++)
		{
			if (pthread_create(&miners[j].thread, NULL, search, (void *)&miners[j]))
			{
				/* Error a la hora de crear el hilo. Paramos todos y salimos */
				finish = FOUND;
				for (j--; j >= 0; j--)
					pthread_join(miners[j].thread, NULL);
				miner_exit(miners, send, recieved, PRC_UNEXPECTED);
			}
		}

		/* Recoger los hilos  */
		for (j = 0; j < n_threads; j++)
			pthread_join(miners[j].thread, NULL);

		/* Obtener el resultado que se haya encontrado */
		result = get_result(n_threads, miners);
		if (result == NOT_FOUND)
			miner_exit(miners, send, recieved, PRC_PROBLEM);

		/* Mandar la info al monitor */
		if (send_request(send[1], target, result))
			miner_exit(miners, send, recieved, PRC_UNEXPECTED);

		/* Recibir la informacion del monitor */
		request = recieve_request(recieved[0]);

		/* Imprimir mensaje dependiendo del monitor */
		if (request == -1)
			miner_exit(miners, send, recieved, PRC_UNEXPECTED);
		else if (request)
			printf("Solution accepted: %08ld --> %08ld\n", target, result);
		else
		{
			printf("Solution rejected: %08ld !-> %08ld\n", target, result);
			miner_exit(miners, send, recieved, PRC_PROBLEM);
		}

		/* Cambiar el target */
		target = result;
	}

	/* Liberamos memoria y volvemos al proceso principal */
	miner_exit(miners, send, recieved, PRC_OK);
}
