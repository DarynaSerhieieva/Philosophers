/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserhiei <dserhiei@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:48 by dserhiei          #+#    #+#             */
/*   Updated: 2024/12/24 22:44:29 by dserhiei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo(t_table *table)
{
	for (int i = 0; i < table->num_philos; i++)
	{
		printf("id: %d\n", table->philosophers[i].id);
		printf("time_to_die: %ld\n", table->philosophers[i].time_to_die);
		printf("time_to_eat: %ld\n", table->philosophers[i].time_to_eat);
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
	cleanup_table(&table, "end", 0);
	return (0);
}
