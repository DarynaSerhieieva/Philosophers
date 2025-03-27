#include "philo.h"

static int	initialize_mutexes(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->stop_lock, NULL) != 0)
		return (print_mutex_error(-1, "mutex_init failed stop_lock"), 1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		print_mutex_error(-1, "mutex_init failed print_lock");
		if (pthread_mutex_destroy(&table->stop_lock) != 0)
			return (print_mutex_error(-1, "mutex_destroy failed stop_lock"), 1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
		return (destroy_mutexes(table, 0), 1);
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], 0) != 0)
		{
			print_mutex_error(i, "mutex_init failed fork ");
			destroy_mutexes(table, i);
			return (1);
		}
		i++;
	}
	return (0);
}

void	initialize_table_data(t_table *table, int size, char **arrey)
{
	table->nb_philos = ft_atoi(arrey[1]);
	table->time_to_die = ft_atoi(arrey[2]);
	table->time_to_eat = ft_atoi(arrey[3]);
	table->time_to_sleep = ft_atoi(arrey[4]);
	table->must_eat = -1;
	if (size - 1 == 5)
		table->must_eat = ft_atoi(arrey[5]);
	table->is_sim_stopped = false;
}

t_table	*initialize_table(int size, char **arrey)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	if (initialize_mutexes(table))
	{
		free(table);
		return (NULL);
	}
	initialize_table_data(table, size, arrey);
	table->philos = initialize_philos(table);
	if (!table->philos)
	{
		destroy_mutexes(table, table->nb_philos);
		free(table);
		return (NULL);
	}
	return (table);
}
