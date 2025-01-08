#include "philo.h"

void	check_each(char *num, int index)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (i == 0 && (num[i] == '+'))
			i++;
		else if ((num[i] < '0' || num[i] > '9'))
		{
			printf("Error: The argument %d is not positive integer\n", index);
			exit (1);
		}
		i++;
	}
}

void	is_it_num(int size, char **arrey)
{
	int	i;

	i = 1;
	while (i < size)
	{
		check_each(arrey[i], i);
		i++;
	}
}

void	fill_data(t_table *table, char **arrey)
{
	int		i;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;

	i = 0;
	time_to_die = ft_atoi(arrey[2]);
	time_to_eat = ft_atoi(arrey[3]);
	time_to_sleep = ft_atoi(arrey[4]);
	while (i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].time_to_die = time_to_die;
		table->philos[i].time_to_eat = time_to_eat;
		table->philos[i].time_to_sleep = time_to_sleep;
		table->philos[i].last_meal_time = 0;
		table->philos[i].meals_eaten = 0;
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			cleanup_table(table, "Failed to initialize mutex for fork", 3);
		i++;
	}
	if (pthread_mutex_init(&table->print_lock, NULL) != 0)
		cleanup_table(table, "Failed to initialize print lock mutex", 1);
	table->start_time = current_time_ms();
}

void	init_table(t_table *table, int size, char **arrey)
{
	int	num_philos;

	is_it_num(size, arrey);
	num_philos = (int)ft_atoi(arrey[1]);
	if (num_philos <= 0)
	{
		printf("Error: Number of philosophers must be a positive integer.\n");
		exit(1);
	}
	table->num_philos = num_philos;
	table->philos = malloc(num_philos * sizeof(t_philo));
	if (!table->philos)
	{
		printf("Error: Memory allocation for philosophers failed!\n");
		exit (1);
	}
	memset(table->philos, 0, num_philos * sizeof(t_philo));
	table->forks = malloc(num_philos * sizeof(pthread_mutex_t));
	if (!table->forks)
		cleanup_table(table, "Memory allocation for forks failed", 2);
	fill_data(table, arrey);
}
