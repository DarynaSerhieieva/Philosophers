/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserhiei <dserhiei@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:48 by dserhiei          #+#    #+#             */
/*   Updated: 2025/01/08 17:04:17 by dserhiei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo(t_table *table)
{
	pthread_t	*threads;
	int			i;
	int			rc;

	i = 0;
	threads = malloc(table->num_philos * sizeof(pthread_t));
	if (!threads)
		cleanup_table(table, "Memory allocation for threads failed", 0);
	while (i < table->num_philos)
	{
		rc = pthread_create(&threads[i], NULL, routine, &table->philos[i]);
		if (rc)
			cleanup_table(table, "Unable to create thread", 0);
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(table->philos[i].thread, NULL);
		i++;
	}
	free(threads);
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
