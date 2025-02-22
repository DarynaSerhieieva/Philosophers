#include "philo.h"

void	mutex_destroy(pthread_mutex_t *forks, int **i_forks, int s)
{
	int	i;

	i = 0;

	while (i < s)
	{
		if (i_forks[i])
		{
			pthread_mutex_unlock(&forks[i]);
			i_forks[i] = 0;
		}
		if (pthread_mutex_destroy(&forks[i]) != 0)
		{
			printf("Error: Failed to destroy mutex for fork %d\n", i);
			break ;
		}
		i++;
	}
}

void	cleanup_table(t_table *table, char *text, int status)
{
	if (status == 0)
	{
		mutex_destroy(table->forks, &table->i_forks, table->num_philos);
		if (pthread_mutex_destroy(&table->print_lock) != 0)
			printf("Error: Failed to destroy mutex for print_lock!\n");
	}
	else if (status == 1)
		mutex_destroy(table->forks, &table->i_forks, table->num_philos);
	if (status == 2)
		free_memory(NULL, &table->philos, NULL);
	else if (status == 3)
		free_memory(NULL, &table->philos, &table->i_forks);
	else
		free_memory(&table->forks, &table->philos, &table->i_forks);
	printf("Error: %s!\n", text);
	exit(EXIT_FAILURE);
}
