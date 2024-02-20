#ifndef MINERIA_H
# define MINERIA_H

# include "libs.h"
# include "pow.h"
# include "error.h"
# include "utils.h"
# include "monitor.h"

# define NOT_FOUND -1
# define FOUND 1

typedef struct s_miner t_miner;

struct s_miner
{
	/* Variable con la info del hilo */
	pthread_t	thread;

	/* Numero a buscar */
	long		target;

	/* Valores entre los que tiene que buscar el hilo */
	long		start;
	long		end;

	/* Resultado que encuentra el hilo */
	long		result;

	/* Flag para acabar la ejecución */
	int			*finish;
};

void	mineria(long target, long rounds, long n_threads);

#endif