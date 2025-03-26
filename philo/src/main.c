#include <philo.h>

int	main(int argc, char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		printf("Should be 4 or 5 arguments, but you have %d\n", argc - 1);
		return (1);
	}
	if (is_valid(argc, argv))
		return (1);
	table = init_table(argc, argv);
	if (!table)
		return (1);
	philo(&table, argc, argv);
	cleanup_table(&table);
	return (0);
}
