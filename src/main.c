#include "../include/mrush.h"

/* NOTE: preguntar sobre 'Miner exited unexpectedly' */
/* NOTE: data races? mutex? */
/* NOTE: error a la hora de comporbar el numero?? puede fallar la primer busqueda */

int	main(int argc, char **argv)
{
	long	target;
	long	rounds;
	long	n_threads;
	pid_t	pid;
	int		status;


	if (argc != 4)
		argument_error(argv[0]);

	/* Guardar los argumentos como número */
	target = atol(argv[1]);
	rounds = atol(argv[2]);
	n_threads = atol(argv[3]);

	/* Crear proceso hijo. Ejecutar al hijo con la funcion de mineria */
	pid = fork();
	if (pid < 0)
		fork_error();
	if (pid == 0)
		mineria(target, rounds, n_threads);

	/* Esperar al hijo */
	waitpid(pid, &status, 0);
	
	/* Imprimir como ha salido el hijo */
	printf("Miner exited with status %d\n", WEXITSTATUS(status));

	return (0);
}