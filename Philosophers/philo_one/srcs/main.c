#include "philo_one.h"

static int	meal_checker(t_data *data)
{
	while (data->no_philos && !data->death && !data->error)
	{
		if (get_time(&data->current_time) != SUCCESS)
			return (*set_error(data, "gettimeofday() returned -1\n"));
		if (data->done == data->no_philos || !data->no_meals)
		{
			if (pthread_mutex_lock(&data->print) != SUCCESS)
				return (*set_error(data, "pthread_mutex_lock() "
						"returned an error\n"));
			printf("%llu \033[32mall done\033[0m\n",
				data->current_time - data->start_time);
			data->death = 1;
		}
	}
	if (data->error)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	t;
	int			i;

	if (init_data(&data, argc, argv) != SUCCESS)
		return (put_error(&data, NULL));
	i = -1;
	if (get_time(&data.current_time) != SUCCESS)
		return (put_error(&data, "gettimeofday() returned -1\n"));
	while (++i < data.no_philos)
		if (pthread_create(&t, NULL, philosopher, (void *)&data) != SUCCESS)
			return (put_error(&data, "pthread_create() returned an error\n"));
	if (meal_checker(&data) != SUCCESS)
		return (put_error(&data, NULL));
	free_all(&data);
	return (SUCCESS);
}
