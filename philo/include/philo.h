#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
#include <stdbool.h>

typedef struct s_table
{
	pthread_mutex_t	print_lock;
	pthread_mutex_t	stop_lock;
	pthread_mutex_t	*forks;
	pthread_t		reaper;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	unsigned int	nb_philos;
	int				must_eat;
	bool			sim_stop;
	t_philo			**philos;
}	t_table;

typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	unsigned int	id;
	unsigned int	meals_eaten;
	unsigned int	fork[2];
	time_t			last_meal_time;
	t_table			*table;
}	t_philo;

//main


//philo
void	philo(t_table *table, int argc, char **argv);

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
t_table	*init_table(int size, char **arrey);
int		mem_all(t_table *table, int size);
void	fill_data(t_table *table, char **arrey);

//cleanup_table
void		free_item(void **item);
void		free_memory(pthread_mutex_t **forks, t_philo **philos, int **i_phil);
void		cleanup_table(t_table *table);
void		mutex_destroy(pthread_mutex_t *forks, int s);
static void	cleanup_philos(t_philo **philos, int count);
static void	cleanup_mutex(t_table *table, int count);

// utils
long	ft_atoi(const char *nptr);
long	current_time_ms(void);
int		is_valid(int size, char **arrey);

#endif
