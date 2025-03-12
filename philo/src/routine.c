#include <philo.h>

void	thinking(t_philo *philo)
{
	if (time_to_die(philo))
		return ;
	pthread_mutex_lock(&philo->table->print_lock);
	if (print_message(philo, "is thinking"))
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->print_lock);
}

void	eating(t_philo *philo)
{
	while (!time_to_die(philo))
	{
		pthread_mutex_lock(&philo->table->print_lock);
		if (!philo->table->i_forks[philo->id - 1] && \
		!philo->table->i_forks[philo->id])
		{
			if (lock_fork(philo, philo->id - 1))
				return ;
			if (lock_fork(philo, philo->id))
				return ;
			if (print_message(philo, "is eating"))
			{
				unlock_forks(philo);
				pthread_mutex_unlock(&philo->table->print_lock);
				return ;
			}
			pthread_mutex_unlock(&philo->table->print_lock);
			usleep(philo->time_to_eat * 1000);
			unlock_forks(philo);
			philo->meals_eaten++;
			philo->last_meal_time = current_time_ms();
			return ;
		}
		pthread_mutex_unlock(&philo->table->print_lock);
	}
}

void	sleeping(t_philo *philo)
{
	if (time_to_die(philo))
		return ;
	pthread_mutex_lock(&philo->table->print_lock);
	if (print_message(philo, "is sleeping"))
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->table->print_lock);
	usleep(philo->time_to_sleep * 1000);
}

int	time_to_die(t_philo *philo)
{
	long	time_of_death;

	pthread_mutex_lock(&philo->table->print_lock);
	if (philo->table->should_stop)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (1);
	}
	time_of_death = current_time_ms();
	if ((time_of_death - philo->last_meal_time) >= philo->time_to_die)
	{
		print_message(philo, "dead");
		philo->table->should_stop = 1;
		pthread_mutex_unlock(&philo->table->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!time_to_die(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
