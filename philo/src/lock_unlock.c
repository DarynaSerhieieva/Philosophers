#include <philo.h>

int	lock_unclok_print(t_philo *philo, char *massege)
{
	long	current_time;

	current_time = current_time_ms();
	pthread_mutex_lock(&philo->table->print_lock);
	if (philo->table->should_stop)
	{
		pthread_mutex_unlock(&philo->table->print_lock);
		return (1);
	}
	printf("%ld %d %s\n", current_time, philo->id, massege);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}

int	lock_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->id - 1]);
	philo->table->i_forks[philo->id - 1] = 1;
	if (lock_unclok_print(philo, "has taken a fork"))
	{
		pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
		philo->table->i_forks[philo->id - 1] = 0;
		return (1);
	}
	pthread_mutex_lock(&philo->table->forks[philo->id]);
	philo->table->i_forks[philo->id] = 1;
	if (lock_unclok_print(philo, "has taken a fork"))
	{
		unlock_forks(philo);
		return (1);
	}
	return (0);
}

void	unlock_forks(t_philo *philo)
{
	philo->table->i_forks[philo->id - 1] = 0;
	philo->table->i_forks[philo->id] = 0;
	pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
}
