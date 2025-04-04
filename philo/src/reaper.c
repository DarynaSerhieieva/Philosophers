#include <philo.h>


bool	has_simulation_stopped(t_table *table)
{
	bool	r;

	r = false;
	pthread_mutex_lock(&table->stop_lock);
	if (table->is_sim_stopped == true)
		r = true;
	pthread_mutex_unlock(&table->stop_lock);
	return (r);
}

void	*reaper(void *data)
{
	t_table			*table;

	table = (t_table *)data;
	if (table->must_eat == 0)
		return (NULL);
	set_sim_stop_flag(table, false);
	sim_start_delay(table->start_time);
	while (true)
	{
		if (end_condition_reached(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
