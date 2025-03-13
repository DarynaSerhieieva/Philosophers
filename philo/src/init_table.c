#include "philo.h"

int	is_pos_num(int size, char **arrey)
{
	int	i;
	int	j;

	j = 1;
	while (j < size)
	{
		i = 0;
		while (arrey[j][i] != '\0')
		{
			if (i == 0 && (arrey[j][i] == '+'))
				i++;
			else if ((arrey[j][i] < '0' || arrey[j][i] > '9'))
			{
				printf("Error: The argument %d is not positive int\n", j);
				return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}


void	fill_data(t_table *table, char **arrey)
{
	int		i;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	time;

	i = 0;
	time_to_die = ft_atoi(arrey[2]);
	time_to_eat = ft_atoi(arrey[3]);
	time_to_sleep = ft_atoi(arrey[4]);
	time = current_time_ms();
	while (i < table->num_philos)
	{
		table->i_forks[i] = 0;
		table->philos[i].id = i + 1;
		table->philos[i].time_to_die = time_to_die;
		table->philos[i].time_to_eat = time_to_eat;
		table->philos[i].time_to_sleep = time_to_sleep;
		table->philos[i].last_meal_time = time;
		table->philos[i].meals_eaten = 0;
		table->philos[i].table = table;
		i++;
	}
	table->should_stop = 0;
	table->must_eat = -1;
}

int	mem_all(t_table *table, int size)
{
	int	i;

	i = 0;
	table->philos = malloc(size * sizeof(t_philo));
	if (!table->philos)
		return (printf("Error: Memory allocation for philos failed!\n"), 1);
	table->i_forks = malloc(size * sizeof(int));
	if (!table->i_forks)
		return (printf("Error: Memory allocation for forks failed!\n"), 1);
	table->forks = malloc(size * sizeof(pthread_mutex_t));
	if (!table->forks)
		return (printf("Error: Allocation mutex for forks failed!\n"), 1);
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		return (printf("Error: Failed to initialize print lock mutex!\n"), 1);
	while (i < size)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (printf("Error: Failed to initialize mutex for fork!\n"), 1);
		i++;
	}
	return (0);
}

int	init_table(t_table *table, int size, char **arrey)
{
	int	num_philos;

	if (is_pos_num(size, arrey))
		return (1);
	num_philos = (int)ft_atoi(arrey[1]);
	if (num_philos <= 0)
		return (printf("Error: Number of philos must be at least 1.\n"), 1);
	table->num_philos = num_philos;
	if (mem_all(table, num_philos))
		return (1);
	if (size == 6)
		table->must_eat = (int)ft_atoi(arrey[5]);
	fill_data(table, arrey);
	return (0);
}
