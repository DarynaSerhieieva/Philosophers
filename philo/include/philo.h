#ifndef PHILO_H
# define PHILO_H

# include "stdio.h"
# include "stdlib.h"

typedef struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_data;

//philo
void	philo(int size, char **arrey, t_data *data);

// check_arg
int		check_each(char *num, int index);
int		is_it_num(int size, char **arrey, t_data *data);

// utils
int		ft_atoi(const char *nptr);

#endif
