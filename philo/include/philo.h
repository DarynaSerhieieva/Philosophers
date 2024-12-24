#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"
# include "sys/time.h"

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		last_meal_time;
	int			meals_eaten;
}	t_philo;

typedef struct s_table
{
	int				num_philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	long			start_time;
	t_philo			*philosophers;
}	t_table;

//philo
void	philo(int size, char **arrey, t_philo *data);

// check_arg
void	is_it_num(int size, char **arrey, t_table *table);
void	check_each(char *num, int index);

// utils
long	ft_atoi(const char *nptr);

#endif
