#include "philo_two.h"

static int	meal_checker(t_data *data)
{
	while (data->no_philos && !data->death && !data->error)
	{
		if (get_time(&data->current_time) != SUCCESS)
			return (*set_error(data, "gettimeofday() returned -1\n"));
		if (data->done == data->no_philos || !data->no_meals)
		{
			if (sem_wait(data->print) != SUCCESS)
				return (*set_error(data, "sem_wait() returned an error\n"));
			printf("%llu \033[32mall done\033[0m\n",
				data->current_time - data->start_time);
			data->death = 1;
			if (sem_post(data->print) != SUCCESS)
				return (*set_error(data, "sem_post() returned an error\n"));
		}
		if (usleep(500) != SUCCESS)
			return (*set_error(data, "usleep() returned -1\n"));
	}
	if (data->error)
		return (FAILURE);
	return (SUCCESS);
}

static void	remove_sem(sem_t *sem, char *name)
{
	sem_close(sem);
	sem_unlink(name);
}

void	close_sems(t_data *data)
{
	int		i;

	if (data->sems_init)
	{
		i = -1;
		while (++i < data->no_philos)
			sem_post(data->forks);
		usleep(200000);
		if (data->count != SEM_FAILED)
			remove_sem(data->count, "/count");
		if (data->check != SEM_FAILED)
			remove_sem(data->check, "/check");
		if (data->eat != SEM_FAILED)
			remove_sem(data->eat, "/eat");
		if (data->print != SEM_FAILED)
			remove_sem(data->print, "/print");
		if (data->forks != SEM_FAILED)
			remove_sem(data->forks, "/forks");
	}
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
	close_sems(&data);
	return (SUCCESS);
}
