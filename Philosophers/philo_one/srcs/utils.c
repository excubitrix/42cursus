#include "philo_one.h"

int	get_time(int64_t *ptr)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != -1)
	{
		*ptr = time.tv_sec * 1000 + (time.tv_usec / 1000);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	ft_print(t_data *data, int no, char *s, int twice)
{
	int64_t	time;

	if (!pthread_mutex_lock(&data->print))
	{
		if (get_time(&time) != SUCCESS)
			return (*set_error(data, "gettimeofday() returned -1\n"));
		printf("%llu %d %s\n", time - data->start_time, no + 1, s);
		if (twice)
			printf("%llu %d %s\n", time - data->start_time, no + 1, s);
		pthread_mutex_unlock(&data->print);
		return (SUCCESS);
	}
	return (*set_error(data, "pthread_mutex_lock() returned an error\n"));
}

int	*set_error(t_data *data, char *msg)
{
	int		*ptr;
	int		ret;

	ret = FAILURE;
	ptr = &ret;
	if (!data->error)
		data->error = msg;
	return (ptr);
}

int	put_error(t_data *data, char *msg)
{
	int		len;
	char	*error;

	error = data->error;
	if (msg)
		error = msg;
	len = 0;
	while (error[len])
		len++;
	write(2, "Error: ", 8);
	write(2, error, len);
	free_all(data);
	return (FAILURE);
}

void	free_all(t_data *data)
{
	int		i;

	if (data->locks_init)
	{
		pthread_mutex_destroy(&data->lock);
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->count);
		i = -1;
		while (++i < data->no_philos)
			pthread_mutex_destroy(&data->fork[i]);
	}
	if (data->fork)
		free(data->fork);
}
