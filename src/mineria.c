#include "../include/mineria.h"

void	miner_exit(t_miner *miners, int *pipe1, int *pipe2, int status)
{
	if (miners)
		free(miners);
	if (pipe1)
	{
		close(pipe1[0]);
		close(pipe1[1]);
	}
	if (pipe2)
	{
		close(pipe2[0]);
		close(pipe2[1]);
	}
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

void	mineria(long target, long rounds, long n_threads)
{
	t_miner	*miners;
	long	i, j;
	int		finish;
	long	result;
	int		send[2], recieved[2];

	/* Crear las estructuras que vamos a pasar */
	miners = malloc(n_threads * sizeof(t_miner));
	if (!miners)
		miner_exit(NULL, NULL, NULL, PRC_UNEXPECTED);

	/* TODO: Comprobar que la solucion está bien (apartado c) */
	if (pipe(send))
		miner_exit(miners, NULL, NULL, PRC_UNEXPECTED);
	
	if (pipe(recieved))
		miner_exit(miners, send, NULL, PRC_UNEXPECTED);

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

		/* NOTE: Imprimir el resultado. Lo deberia de hacer el proceso MONITOR */
		printf("Solution accepted: %08ld --> %08ld\n", target, result);

		/* Cambiar el target */
		target = result;
	}

	/* Liberamos memoria y volvemos al proceso principal */
	free(miners);
	exit(EXIT_SUCCESS);
	miner_exit(miners, send, recieved, PRC_OK);
}
