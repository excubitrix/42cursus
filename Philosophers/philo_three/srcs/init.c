#include "philo_three.h"

static int	parse_args(t_data *data, int argc, char **args)
{
	if (argc < 5)
		return (put_error("Not enough arguments\n"));
	else if (argc > 6)
		return (put_error("Too many arguments\n"));
	if (mini_atoi((int64_t *)&data->no_philos, args[1]) != SUCCESS
		|| mini_atoi(&data->tt_die, args[2]) != SUCCESS
		|| mini_atoi((int64_t *)&data->tt_eat, args[3]) != SUCCESS
		|| mini_atoi((int64_t *)&data->tt_sleep, args[4]) != SUCCESS
		|| mini_atoi((int64_t *)&data->no_meals, args[5]) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->print = (sem_t *)(-1);
	data->forks = (sem_t *)(-1);
	data->status = THINKING;
	if (parse_args(data, argc, argv) != SUCCESS)
		return (FAILURE);
	sem_unlink("/print");
	data->print = sem_open("/print", O_CREAT, S_IRWXU, 1);
	sem_unlink("/forks");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->no_philos / 2);
	if (data->print == SEM_FAILED || data->forks == SEM_FAILED)
		return (put_error("sem_open() returned an error\n"));
	if (get_time(&data->start_time) != SUCCESS)
		return (put_error("gettimeofday() returned -1\n"));
	data->last_time_eaten = data->start_time;
	return (SUCCESS);
}
