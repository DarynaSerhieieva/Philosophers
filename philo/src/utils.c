#include "philo.h"

long	ft_atoi(const char *nptr)
{
	unsigned long	num;
	int				i;

	i = 0;
	num = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (num > INT_MAX)
		{
			printf("Error: Number exceeds the maximum value for a int.\n");
			return (-1);
		}
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	return ((unsigned int)num);
}

int	is_valid(int size, char **arrey)
{
	int	i;
	int	j;
	int	nb;

	j = 1;
	while (j < size)
	{
		i = 0;
		while (arrey[j][i] != '\0')
		{
			if (i == 0 && (arrey[j][i] == '+'))
				i++;
			else if ((arrey[j][i] < '0' || arrey[j][i] > '9'))
				return (print_error(j, "Is not positive int argument "), 1);
			i++;
		}
		nb = ft_atoi(arrey[j]);
		if (j == 1 && nb > 250)
			return (print_error(-1, "Philos sould not be exceed 250"), 1);
		else if (nb == -1)
			return (1);
		j++;
	}
	return (0);
}

long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}


void	print_error(int id, char *message)
{
	if (id == -1)
		printf("Error: %s\n!", message);
	else
		printf("Error: %s %d!\n", message, id);
}
