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
void	philo(t_table *table);

// init_table
void	init_table(t_table *table, int size, char **arrey);
void	is_it_num(int size, char **arrey);
void	check_each(char *num, int index);
void	fill_data(t_table *table, char **arrey);

// utils
long	ft_atoi(const char *nptr);
void	cleanup_table(t_table *table);
void	free_memory(t_table *table);
long	current_time_ms(void);

#endif
