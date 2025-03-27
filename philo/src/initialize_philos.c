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
		return (1);
	philo->id = id;
	philo->meals_eaten = 0;
	philo->table = table;
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
	{
		print_mutex_error(-1, "Allocation failed for mea_lock mutex");
		free(philo);
		return (1);
	}
	return (0);
}

static t_philo	**initialize_philos(t_table *table)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * table->nb_philos);
	if (!philos)
		return (print_mutex_error(-1, "Allocation failed for philos"), NULL);
	i = 0;
	while (i < table->nb_philos)
	{
		philos[i] = malloc(sizeof(t_philo));
		if (!philos[i] || initialize_philo(philos[i], i, table) != 0)
		{
			destroy_philos(philos, i);
			return (NULL);
		}
		assign_forks(philos[i]);
		i++;
	}
	return (philos);
}
