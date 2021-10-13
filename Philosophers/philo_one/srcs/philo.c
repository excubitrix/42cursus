#include "philo_one.h"

void	*reaper(void *arg)
{
	t_info		*info;
	t_data		*data;

	info = (t_info *)arg;
	data = info->data;
	while (!data->error)
	{
		if (info->last_time_eaten + data->tt_die <= data->current_time)
		{
			while (info->status == EATING)
				;
			if (pthread_mutex_lock(&data->print) != SUCCESS)
				return (set_error(data, "pthread_mutex_lock() "
						"returned an error\n"));
			if (!data->error)
				printf("%llu %d \033[31mdied\033[0m\n",
					data->current_time - data->start_time, info->no + 1);
			data->death = 1;
			break ;
		}
		if (usleep(500) != SUCCESS)
			return (set_error(data, "usleep() returned -1\n"));
	}
	return (NULL);
}

static int	eating(t_info *info, int no, int64_t *rising_time)
{
	int64_t	time_done_eating;

	if (pthread_mutex_lock(&info->data->fork[info->left_fork]) != SUCCESS
		|| pthread_mutex_lock(&info->data->fork[no]) != SUCCESS)
		return (*set_error(info->data, "pthread_mutex_lock() "
				"returned an error\n"));
	info->status = EATING;
	info->last_time_eaten = info->data->current_time;
	time_done_eating = info->data->current_time + info->data->tt_eat;
	ft_print(info->data, no, "has taken a fork", 1);
	ft_print(info->data, no, "is eating", 0);
	while (!info->data->error && time_done_eating > info->data->current_time)
		if (usleep(500) != SUCCESS)
			set_error(info->data, "usleep() returned -1\n");
	ft_print(info->data, info->no, "is sleeping", 0);
	info->status = SLEEPING;
	*rising_time = info->data->current_time + info->data->tt_sleep;
	if (pthread_mutex_unlock(&info->data->fork[info->left_fork]) != SUCCESS
		|| pthread_mutex_unlock(&info->data->fork[info->no]) != SUCCESS)
		return (*set_error(info->data, "pthread_mutex_unlock() "
				"returned an error\n"));
	if (info->data->error)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_meals(t_data *data, int meals, int no)
{
	if (meals == data->no_meals)
	{
		if (ft_print(data, no, "\033[32mis done\033[0m", 0) != SUCCESS)
			return (FAILURE);
		if (pthread_mutex_lock(&data->count) != SUCCESS)
			return (*set_error(data, "pthread_mutex_lock() "
					"returned an error\n"));
		data->done++;
		if (pthread_mutex_unlock(&data->count) != SUCCESS)
			return (*set_error(data, "pthread_mutex_unlock() "
					"returned an error\n"));
	}
	return (SUCCESS);
}

static int	sleeping(t_info *info, int64_t rising_time)
{
	while (rising_time > info->data->current_time)
		if (usleep(500) != SUCCESS)
			return (*set_error(info->data, "usleep() returned -1\n"));
	info->status = THINKING;
	if (ft_print(info->data, info->no, "is thinking", 0) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

void	*philosopher(void *arg)
{
	pthread_t	t;
	t_info		info;
	int64_t		rising_time;
	int			meals;

	meals = 0;
	init_philo(&info, (t_data *)arg);
	if (pthread_create(&t, NULL, reaper, (void *)&info) != SUCCESS)
		return (set_error(info.data, "pthread_create() returned an error\n"));
	if (!(info.no % 2))
		if (usleep(500) != SUCCESS)
			return (set_error(info.data, "usleep() returned -1\n"));
	while (!info.data->death
		&& eating(&info, info.no, &rising_time) == SUCCESS
		&& check_meals(info.data, ++meals, info.no) == SUCCESS
		&& sleeping(&info, rising_time) == SUCCESS)
		;
	pthread_join(t, NULL);
	return (NULL);
}