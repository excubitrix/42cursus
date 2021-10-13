#include "philo_two.h"

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

	if (sem_wait(data->print) != SUCCESS)
		return (*set_error(data, "sem_wait() returned an error\n"));
	if (!data->death && !data->error)
	{
		if (get_time(&time) != SUCCESS)
		{
			sem_post(data->print);
			return (*set_error(data, "gettimeofday() returned -1\n"));
		}
		printf("%llu %d %s\n", time - data->start_time, no + 1, s);
		if (twice)
			printf("%llu %d %s\n", time - data->start_time, no + 1, s);
	}
	if (sem_post(data->print) != SUCCESS)
		return (*set_error(data, "sem_post() returned an error\n"));
	return (SUCCESS);
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
	close_sems(data);
	return (FAILURE);
}
