#include "philo.h"

void	destroy_philos(t_philo **philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (philos[i])
		{
			if (pthread_mutex_destroy(&philos[i]->meal_lock) != 0)
				print_mutex_error(i, "Failed to destroy meal_lock mutex philo");
			free(philos[i]);
		}
		i++;
	}
	free(philos);
}

void	destroy_mutexes(t_table *table, int count)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&table->stop_lock) != 0)
		print_mutex_error(-1, "Failed to destroy stop_lock mutex");
	if (pthread_mutex_destroy(&table->print_lock) != 0)
		print_mutex_error(-1, "Failed to destroy print_lock mutex");
	if (count == 0)
		return ;
	while (i < count)
	{
		if (pthread_mutex_destroy(&table->forks[i]) != 0)
			print_mutex_error(i, "Failed to destroy mutex fork ");
		i++;
	}
	free(table->forks);
}
