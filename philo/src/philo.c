/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserhiei <dserhiei@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:48 by dserhiei          #+#    #+#             */
/*   Updated: 2024/12/24 15:12:26 by dserhiei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo(int size, char **arrey, t_philo *data)
{
	// if (!is_it_num(size, arrey, data))
	// 	return ;
	// printf("number_of_philosophers: %d\n", data->number_of_philosophers);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
}



int	main(int argc, char **argv)
{
	t_table	table;

	// table = NULL;
	if (argc != 5)
	{
		printf("Should be 4 arguments, but you have %d\n", argc - 1);
		return (1);
	}
	init_table(argc, argv, &table);
	return (0);
}
