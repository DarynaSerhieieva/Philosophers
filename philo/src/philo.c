/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserhiei <dserhiei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:48 by dserhiei          #+#    #+#             */
/*   Updated: 2025/01/05 19:45:59 by dserhiei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_rutin(void* arg)
{
	t_philo	*philo = (t_philo *)arg;

	printf("Philosopher %d: Starting routine\n", philo->id);

	while (1)
	{
		printf("Philosopher %d: Thinking\n", philo->id);
		usleep(philo->time_to_eat * 1000);

		printf("Philosopher %d: Eating\n", philo->id);
		philo->last_meal_time = current_time_ms();
		philo->meals_eaten++;
		usleep(philo->time_to_eat * 1000);

		printf("Philosopher %d: Sleeping\n", philo->id);
		usleep(philo->time_to_sleep * 1000);
	}
}

void	philo(t_table *table)
{
	pthread_t	threads[table->num_philos];
	int			i;
	int			rc;

	i = 0;
	while (i < table->num_philos)
	{
		rc = pthread_create(&threads[i], NULL, philo_rutin, &table->philosophers[i]);
        if (rc)
			cleanup_table(table, "Unable to create thread", 0);
		i++;
	}

	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philosophers[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc != 5)
	{
		printf("Should be 4 arguments, but you have %d\n", argc - 1);
		return (1);
	}
	init_table(&table, argc, argv);
	philo(&table);
	usleep(100000);
	cleanup_table(&table, "end", 0);
	return (0);
}


