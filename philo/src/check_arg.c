#include "philo.h"

void	check_each(char *num, int index)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (i == 0 && (num[i] == '+' || num[i] == '-'))
			i++;
		else if ((num[i] <= '0' && num[i] >= '9'))
		{
			printf("The argument with index: %d, is not a number\n", index);
			exit (1);
		}
		i++;
	}
}

void	is_it_num(int size, char **arrey, t_table *table)
{
	int	i;

	i = 1;
	while (i < size)
	{
		check_each(arrey[i], i);
		i++;
	}
}

void	init_table(t_table *table, int size, char **arrey)
{
	int	i;
	int	num_philosophers;

	i = 0;
	is_it_num(size, arrey, &table);
	num_philosophers = ft_atoi(arrey[1]);
	table->num_philosophers = num_philosophers;
	table->philosophers = malloc(num_philosophers * sizeof(philo));
	table->forks = malloc(num_philosophers * sizeof(pthread_mutex_t));

	while (i < num_philosophers)
	{
		table->philosophers[i].id = i + 1;
		table->philosophers[i].time_to_die = ft_atoi(arrey[2]);
		table->philosophers[i].time_to_eat = ft_atoi(arrey[3]);
		table->philosophers[i].time_to_sleep = ft_atoi(arrey[4]);
		table->philosophers[i].last_meal_time = 0;
		table->philosophers[i].meals_eaten = 0;
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_lock, NULL);
	table->start_time = current_time_ms();
}
