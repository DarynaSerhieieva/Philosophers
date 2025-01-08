#include "philo.h"

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
	printf("%ld %d is %s\n", current_time, philo->id, massege);
	pthread_mutex_unlock(&philo->table->print_lock);
	return (0);
}

void	lock_fork(t_philo *philo, int id)
{
	long	current_time;

	current_time = current_time_ms();
	pthread_mutex_lock(&philo->table->forks[id]);
	if (lock_unclok_print(philo, "has taken a fork"))
		return ;
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->id - 1]);
	pthread_mutex_unlock(&philo->table->forks[philo->id]);
}
