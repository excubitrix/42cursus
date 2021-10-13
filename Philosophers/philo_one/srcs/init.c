#include "philo_one.h"

int	init_philo(t_info *info, t_data *data)
{
	info->data = data;
	info->status = THINKING;
	info->last_time_eaten = info->data->start_time;
	if (pthread_mutex_lock(&info->data->lock) != SUCCESS)
		return (*set_error(info->data, "pthread_mutex_lock() "
				"returned an error\n"));
	info->no = info->data->no++;
	if (pthread_mutex_unlock(&info->data->lock) != SUCCESS)
		return (*set_error(info->data, "pthread_mutex_unlock() "
				"returned an error\n"));
	info->left_fork = info->no + 1;
	if (info->left_fork == info->data->no_philos)
		info->left_fork = 0;
	return (SUCCESS);
}

static int	mini_atoi(t_data *data, int64_t *result, char *val)
{
	*result = -1;
	if (!val)
		return (SUCCESS);
	*result = 0;
	while (*val)
	{
		if (*val < 48 || *val > 57)
			return (*set_error(data, "Encountered unexpected characters\n"));
		*result = (*result * 10) + *val++ - 48;
	}
	if (*result > INT_MAX)
		return (*set_error(data, "One or more values are out of range\n"));
	return (SUCCESS);
}

static int	parse_args(t_data *data, int argc, char **args)
{
	if (argc < 5)
		return (*set_error(data, "Not enough arguments\n"));
	else if (argc > 6)
		return (*set_error(data, "Too many arguments\n"));
	if (mini_atoi(data, (int64_t *)&data->no_philos, args[1]) != SUCCESS
		|| mini_atoi(data, &data->tt_die, args[2]) != SUCCESS
		|| mini_atoi(data, (int64_t *)&data->tt_eat, args[3]) != SUCCESS
		|| mini_atoi(data, (int64_t *)&data->tt_sleep, args[4]) != SUCCESS
		|| mini_atoi(data, (int64_t *)&data->no_meals, args[5]) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int	init_mutex_locks(t_data *data)
{
	int		i;

	if (pthread_mutex_init(&data->lock, NULL) != SUCCESS
		|| pthread_mutex_init(&data->print, NULL) != SUCCESS
		|| pthread_mutex_init(&data->count, NULL) != SUCCESS)
		return (FAILURE);
	i = -1;
	while (++i < data->no_philos)
		if (pthread_mutex_init(&data->fork[i], NULL) != SUCCESS)
			return (FAILURE);
	return (SUCCESS);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->no = 0;
	data->done = 0;
	data->death = 0;
	data->locks_init = 0;
	data->error = NULL;
	if (parse_args(data, argc, argv) != SUCCESS)
		return (FAILURE);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->no_philos);
	if (!data->fork)
		return (*set_error(data, "malloc() returned NULL\n"));
	if (init_mutex_locks(data) != SUCCESS)
		return (*set_error(data, "pthread_mutex_init() returned an error\n"));
	data->locks_init = 1;
	if (get_time(&data->start_time) != SUCCESS)
		return (put_error(data, "gettimeofday() returned -1\n"));
	return (SUCCESS);
}
