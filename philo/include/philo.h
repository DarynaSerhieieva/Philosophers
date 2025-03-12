#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>



typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			last_meal_time;
	int				meals_eaten;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	pthread_mutex_t	*forks;
	int				*i_forks;
	pthread_mutex_t	print_lock;
	long			start_time;
	int				should_stop;
	int				must_eat;
	t_philo			*philos;
}	t_table;

//philo
void	philo(t_table *table);

//routine
void	*routine(void *arg);
void	thinking(t_philo *philo);
void	eating(t_philo *philo);
int		time_to_die(t_philo *philo);
void	sleeping(t_philo *philo);

//lock_unclok
int		print_message(t_philo *philo, char *massege);
// int		lock_forks(t_philo *philo);
int		lock_fork(t_philo *philo, int id);
void	unlock_forks(t_philo *philo);

// init_table
void	init_table(t_table *table, int size, char **arrey);
void	is_it_num(int size, char **arrey);
void	check_each(char *num, int index);
void	fill_data(t_table *table, char **arrey);

//cleanup_table
void	cleanup_table(t_table *table, char *text, int status);
void	mutex_destroy(pthread_mutex_t *forks, int s);

// utils
long	ft_atoi(const char *nptr);
void	free_item(void **item);
void	free_memory(pthread_mutex_t **forks, t_philo **philos, int **i_phil);
// void	free_memory(pthread_mutex_t *forks, t_philo *philosophers);
long	current_time_ms(void);

#endif
