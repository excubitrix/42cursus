#include "philo_three.h"

int	put_error(char *msg)
{
	int		len;

	len = 0;
	while (msg[len])
		len++;
	write(2, "Error: ", 8);
	write(2, msg, len);
	return (FAILURE);
}

int	get_time(int64_t *ptr)
{
	struct timeval	time;

	if (!gettimeofday(&time, NULL))
	{
		*ptr = time.tv_sec * 1000 + (time.tv_usec / 1000);
		return (SUCCESS);
	}
	return (FAILURE);
}

int	mini_atoi(int64_t *result, char *val)
{
	*result = -1;
	if (!val)
		return (SUCCESS);
	*result = 0;
	while (*val)
	{
		if (*val < 48 || *val > 57)
			return (put_error("Encountered unexpected characters\n"));
		*result = (*result * 10) + *val++ - 48;
	}
	if (*result > INT_MAX)
		return (put_error("One or more values are out of range\n"));
	return (SUCCESS);
}

void	ft_print(t_data *data, char *s, int	twice)
{
	int64_t	time;

	if (!sem_wait(data->print))
	{
		if (get_time(&time) != SUCCESS)
			exit(ERROR_EXIT);
		printf("%llu %d %s\n", time - data->start_time, data->no, s);
		if (twice)
			printf("%llu %d %s\n", time - data->start_time, data->no, s);
		if (sem_post(data->print) != SUCCESS)
			exit(ERROR_EXIT);
	}
	else
		exit(ERROR_EXIT);
}
