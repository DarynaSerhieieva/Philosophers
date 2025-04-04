#include <philo.h>

static void	thinking(t_philo *philo, bool silent)
{
	time_t	time_to_think;

	pthread_mutex_lock(&philo->meal_lock);
	time_to_think = (philo->table->time_to_die
			- (get_time_in_ms() - philo->last_meal_time)
			- philo->table->time_to_eat) / 2;
	pthread_mutex_unlock(&philo->meal_lock);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && silent == true)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (silent == false)
		print_message(philo, "is thinking");
	philo_sleep(philo->table, time_to_think);
}

static void	eating_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->forks[philo->fork[1]]);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = get_time_in_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	sleeping(philo->table, philo->table->time_to_eat);
	if (has_simulation_stopped(philo->table) == false)
	{
		pthread_mutex_lock(&philo->meal_lock);
		philo->meals_eaten += 1;
		pthread_mutex_unlock(&philo->meal_lock);
	}
	print_message(philo, "is sleeping");
	pthread_mutex_unlock(&philo->table->forks[philo->fork[1]]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork[0]]);
	sleeping(philo->table, philo->table->time_to_sleep);
}

static void	sleeping(t_table *table, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = current_time_ms() + sleep_time;
	while (current_time_ms() < wake_up)
	{
		if (has_simulation_stopped(table))
			break ;
		usleep(100);
	}
}

static void	*lone_philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork[0]]);
	print_message(philo, "has taken a fork");
	sleeping(philo->table, philo->table->time_to_die);
	print_message(philo, "dead");
	pthread_mutex_unlock(&philo->table->forks[philo->fork[0]]);
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal_time = philo->table->start_time;
	pthread_mutex_unlock(&philo->meal_lock);
	while (get_time_in_ms() < philo->table->start_time)
		continue ;
	if (philo->table->must_eat == 0 || philo->table->time_to_die == 0)
		return ;
	if (philo->table->nb_philos == 1)
		return (lone_philo_routine(philo));
	else if (philo->id % 2)
		thinking(philo, true);
	while (has_simulation_stopped(philo->table) == false)
	{
		eating(philo);
		thinking(philo, false);
	}
	return ;
}
