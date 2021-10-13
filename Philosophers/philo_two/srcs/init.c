#include "philo_two.h"

int	init_philo(t_info *info, t_data *data)
{
	info->data = data;
	info->status = THINKING;
	info->last_time_eaten = data->start_time;
	if (sem_wait(data->count) != SUCCESS)
		return (*set_error(data, "sem_wait() returned an error\n"));
	info->no = data->no++;
	if (sem_post(info->data->count) != SUCCESS)
		return (*set_error(data, "sem_post() returned an error\n"));
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

static int	init_sems(t_data *data)
{
	sem_unlink("/count");
	data->count = sem_open("/count", O_CREAT, S_IRWXU, 1);
	sem_unlink("/check");
	data->check = sem_open("/check", O_CREAT, S_IRWXU, 1);
	sem_unlink("/eat");
	data->eat = sem_open("/eat", O_CREAT, S_IRWXU, 1);
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->no_philos / 2);
	if (data->count == SEM_FAILED || data->check == SEM_FAILED
		|| data->eat == SEM_FAILED || data->print == SEM_FAILED
		|| data->forks == SEM_FAILED)
		return (FAILURE);
	return (SUCCESS);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->no = 0;
	data->done = 0;
	data->death = 0;
	data->sems_init = 0;
	data->error = NULL;
	if (parse_args(data, argc, argv) != SUCCESS)
		return (FAILURE);
	if (init_sems(data) != SUCCESS)
		return (*set_error(data, "sem_open() returned an error\n"));
	data->sems_init = 1;
	if (get_time(&data->start_time) != SUCCESS)
		return (*set_error(data, "gettimeofday() returned -1\n"));
	return (SUCCESS);
}
