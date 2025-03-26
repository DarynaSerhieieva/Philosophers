/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserhiei <dserhiei@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:48 by dserhiei          #+#    #+#             */
/*   Updated: 2025/03/26 16:30:11 by dserhiei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

void	philo(t_table *table, int argc, char **argv)
{
	pthread_t	*threads;
	int			i;
	int			rc;

	i = 0;
	threads = malloc(table->num_philos * sizeof(pthread_t));
	if (!threads)
	{
		printf("Error: Memory allocation for threads failed!\n");
		return ;
	}
	while (i < table->num_philos)
	{
		rc = pthread_create(&threads[i], NULL, routine, &table->philos[i]);
		if (rc)
		{
			printf("Error: Unable to create thread!\n");
			return ;
		}
		i++;
	}
	i = 0;
	while (i < table->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	free(threads);
}
