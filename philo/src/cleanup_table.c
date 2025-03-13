#include "philo.h"

void	free_item(void **item)
{
	if (item && *item)
	{
		free(*item);
		*item = NULL;
	}
}

void	free_memory(pthread_mutex_t **forks, t_philo **philos, int **i_phil)
{
	if (forks && *forks)
		free_item((void **)forks);
	if (philos && *philos)
		free_item((void **)philos);
	if (i_phil && *i_phil)
		free_item((void **)i_phil);
}

void	mutex_destroy(pthread_mutex_t *forks, int s)
{
	int	i;

	if (!forks)
		return ;
	i = 0;
	while (i < s)
	{
		if (pthread_mutex_destroy(&forks[i]) != 0)
		{
			printf("Error: Failed to destroy mutex for fork %d\n", i);
		}
		i++;
	}
}

void	cleanup_table(t_table *table)
{
	if (!table)
		return ;
	if (table->forks)
	{
		mutex_destroy(table->forks, table->num_philos);
		if (pthread_mutex_destroy(&table->print_lock) != 0)
			printf("Error: Failed to destroy mutex for print_lock!\n");
	}
	free_memory(&table->forks, &table->philos, &table->i_forks);
}
