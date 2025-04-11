#include <philo.h>

static void	set_stop_flag(t_table *table, bool state)
{
	pthread_mutex_lock(&table->stop_lock);
	table->is_sim_stopped = state;
	pthread_mutex_unlock(&table->stop_lock);
}

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = current_time_ms();
	if ((time - philo->last_meal_time) >= philo->table->time_to_die)
	{
		set_stop_flag(philo->table, true);
		pthread_mutex_lock(&philo->table->print_lock);
		printf("%ld %d  died\n", time, (philo->id + 1));
		pthread_mutex_unlock(&philo->table->print_lock);
		pthread_mutex_unlock(&philo->meal_lock);
		return (true);
	}
	return (false);
}

static bool	end_condition_reached(t_table *table)
{
	unsigned int	i;
	bool			all_ate_enough;

	all_ate_enough = true;
	i = 0;
	while (i < table->nb_philos)
	{
		pthread_mutex_lock(&table->philos[i]->meal_lock);
		if (kill_philo(table->philos[i]))
			return (true);
		if (table->must_eat != -1)
			if (table->philos[i]->meals_eaten
				< (unsigned int)table->must_eat)
				all_ate_enough = false;
		pthread_mutex_unlock(&table->philos[i]->meal_lock);
		i++;
	}
	if (table->must_eat != -1 && all_ate_enough == true)
	{
		set_stop_flag(table, true);
		return (true);
	}
	return (false);
}

void	*reaper(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->must_eat == 0)
		return (NULL);
	set_stop_flag(table, false);
	start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
