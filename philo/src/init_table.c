#include "philo.h"

static void	assign_forks(t_philo *philo)
{
	int	tmp;

	philo->fork[0] = philo->id;
	philo->fork[1] = (philo->id + 1) % philo->table->nb_philos;
	if (philo->id % 2)
	{
		tmp = philo->fork[0];
		philo->fork[0] = philo->fork[1];
		philo->fork[1] = tmp;
	}
}

static int	initialize_philo(t_philo *philo, int id, t_table *table)
{
	if (!philo)
		return (-1);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->table = table;
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
	{
		printf("Error: Alloc mutex for meal lock failed!\n");
		free(philo);
		return (-1);
	}
	return (0);
}

static t_philo	**init_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo) * table->nb_philos);
	if (!philos)
		return (printf("Error: Memory allocation for philos failed!\n"), NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo) * 1);
		if (!philos[i] || initialize_philo(philos[i], i, table) != 0)
		{
			cleanup_philos(philos, i);
			return (NULL);
		}
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}

static int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->sim_stop, NULL) != 0)
		return (printf("Error: Failed to initialize sim_stop mutex!\n"), 1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
	{
		if (pthread_mutex_destroy(&table->sim_stop) != 0)
			return (printf("Error: Failed to destroy sim_stop mutex!\n"), 1);
	}
	table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philos);
	if (!table->forks)
	{
		if (pthread_mutex_destroy(&table->sim_stop) != 0)
			return (printf("Error: Failed to destroy sim_stop mutex!\n"), 1);
		if (pthread_mutex_destroy(&table->print_lock) != 0)
			return (printf("Error: Failed to destroy print_lock mutex!\n"), 1);
	}
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], 0) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	set_table(t_table *table, int size, char **arrey)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_mutex_init(&table->forks[i], 0) != 0)
			return (1);
		i++;
	}
	table->nb_philos = ft_atoi(arrey[1]);
	table->time_to_die = ft_atoi(arrey[2]);
	table->time_to_eat = ft_atoi(arrey[3]);
	table->time_to_sleep = ft_atoi(arrey[4]);
	table->must_eat = -1;
	if (size - 1 == 5)
		table->must_eat = ft_atoi(arrey[5]);
	table->sim_stop = false;
	return (0);
}

t_table	*init_table(int size, char **arrey)
{
	t_table	*table;

	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (NULL);
	if (set_table(table, size, arrey))
	{
		free(table);
		return (NULL);
	}
	table->philos = init_philos(table);
	if (!table->philos)
	{
		free(table);
		return (NULL);
	}
	fill_data(table, arrey);
	return (0);
}
