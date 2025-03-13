#include <philo.h>

int	print_message(t_philo *philo, char *massege)
{
	long	current_time;

	current_time = current_time_ms();
	if (philo->table->should_stop)
		return (1);
	printf("%ld %d %s\n", current_time, philo->id, massege);
	return (0);
}

int	lock_fork(t_philo *philo, int id)
{
	pthread_mutex_lock(&philo->table->forks[id]);
	philo->table->i_forks[id] = 1;
	if (print_message(philo, "has taken a fork"))
	{
		philo->table->i_forks[id] = 0;
		pthread_mutex_unlock(&philo->table->forks[id]);
		return (1);
	}

	return (0);
}

void	unlock_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id;
	if (left < 0)
		left = philo->table->num_philos - 1;
	philo->table->i_forks[left] = 0;
	philo->table->i_forks[right] = 0;

	pthread_mutex_unlock(&philo->table->forks[left]);
	pthread_mutex_unlock(&philo->table->forks[right]);
}
