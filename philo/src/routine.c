#include <philo.h>

void	thinking(t_philo *philo)
{
	printf("Philosopher %d: Thinking\n", philo->id);
	usleep(philo->time_to_eat * 1000);
}

void	eating(t_philo *philo)
{
	printf("Philosopher %d: Eating\n", philo->id);
	philo->last_meal_time = current_time_ms();
	philo->meals_eaten++;
	usleep(philo->time_to_eat * 1000);
}

void	sleeping(t_philo *philo)
{
	printf("Philosopher %d: Sleeping\n", philo->id);
	usleep(philo->time_to_sleep * 1000);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	printf("Philosopher %d: Starting routine\n", philo->id);

	while (1)
	{
		thinking(philo);
		eating(philo);
		sleeping(philo);
	}
}
