/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dserhiei <dserhiei@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:10:48 by dserhiei          #+#    #+#             */
/*   Updated: 2025/03/27 20:29:27 by dserhiei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

static void	stop_simulation(t_table	*table)
{
	int			i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_join(&table->philos[i]->thread, NULL);
		i++;
	}
}

static bool	start_simulation(t_table *table)
{
	int			i;

	i = 0;
	while (i < table->nb_philos)
	{
		if (pthread_create(&table->philos[i]->thread, NULL,
				routine, &table->philos[i]) != 0)
		{
			print_error(i, "pthread_create faild for philo ");
			while (--i >= 0)
				pthread_join(table->philos[i]->thread, NULL);
			return (false);
		}
		i++;
	}
	if (table->nb_philos > 1)
	{
		if (pthread_create(&table->reaper, NULL,
				reaper, table) != 0)
		{
			stop_simulation(table);
			return (print_error(-1, "pthread_create faild for reaper"), false);
		}
	}
	return (true);
}

static void	philo(t_table *table)
{

	table->start_time = current_time_ms();
	if (!start_simulation(table))
	{

	}
}

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		print_error(argc - 1, "Must be 4 or 5 arguments, but you have ");
		return (1);
	}
	if (is_valid(argc, argv))
		return (1);
	table = initialize_table(argc, argv);
	if (!table)
		return (1);
	philo(&table);
	cleanup_table(&table);
	return (0);
}
