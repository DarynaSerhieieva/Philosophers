#include "philo.h"

int	check_each(char *num, int index)
{
	int	i;

	i = 0;
	while (num[i] != '\0')
	{
		if (i == 0 && (num[i] == '+' || num[i] == '-'))
			i++;
		else if ((num[i] >= '0' && num[i] <= '9'))
			i++;
		else
		{
			printf("The argument with index: %d, is not a number\n", index);
			return (0);
		}
	}
	return (1);
}

int	is_it_num(int size, char **arrey, t_data *data)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (!check_each(arrey[i], i))
			return (0);
		i++;
	}
	data->number_of_philosophers = ft_atoi(arrey[1]);
	data->time_to_die = ft_atoi(arrey[2]);
	data->time_to_eat = ft_atoi(arrey[3]);
	data->time_to_sleep = ft_atoi(arrey[4]);
	return (1);
}
