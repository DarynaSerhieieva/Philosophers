#include "philo.h"

void	mutex_destroy(pthread_mutex_t *forks, int s)
{
	int	i;

	i = 0;
	while (i < s)
	{
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
		mutex_destroy(table->forks, table->num_philos);
		if (pthread_mutex_destroy(&table->print_lock) != 0)
			printf("Error: Failed to destroy mutex for print_lock!\n");
	}
	else if (status == 1)
		mutex_destroy(table->forks, table->num_philos);
	if (status == 2)
		free_memory(NULL, table->philosophers);
	else
		free_memory(table->forks, table->philosophers);
	printf("Error: %s!\n", text);
	exit (2);
}
