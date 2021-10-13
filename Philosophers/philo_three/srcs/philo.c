#include "philo_three.h"

void	*reaper(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	while (1)
	{
		if (get_time(&data->current_time) != SUCCESS)
			exit(ERROR_EXIT);
		if (data->last_time_eaten + data->tt_die <= data->current_time)
		{
			while (data->status == EATING)
				;
			if (sem_wait(data->print) != SUCCESS)
				exit(ERROR_EXIT);
			if (get_time(&data->current_time) != SUCCESS)
				exit(ERROR_EXIT);
			printf("%llu %d \033[31mdied\033[0m\n",
				data->current_time - data->start_time, data->no);
			exit(DEATH_EXIT);
		}
		if (usleep(500) != SUCCESS)
			exit(ERROR_EXIT);
	}
}

static void	eating(t_data *data)
{
	int64_t		time_done_eating;
	static int	meals_eaten;

	if (sem_wait(data->forks) != SUCCESS
		|| get_time(&data->last_time_eaten) != SUCCESS)
		exit(ERROR_EXIT);
	ft_print(data, "has taken a fork", 1);
	ft_print(data, "is eating", 0);
	data->status = EATING;
	time_done_eating = data->current_time + data->tt_eat;
	while (time_done_eating >= data->current_time)
		if (usleep(500) != SUCCESS)
			exit(ERROR_EXIT);
	if (++meals_eaten == data->no_meals)
	{
		ft_print(data, "\033[32mis done\033[0m", 0);
		if (sem_post(data->forks) != SUCCESS)
			exit(ERROR_EXIT);
		exit(MEAL_EXIT);
	}
}

void	philosopher(t_data *data)
{
	int64_t		rising_time;
	pthread_t	t;

	if (pthread_create(&t, NULL, reaper, (void *)data) != SUCCESS)
		exit(ERROR_EXIT);
	while (1)
	{
		eating(data);
		ft_print(data, "is sleeping", 0);
		data->status = SLEEPING;
		rising_time = data->current_time + data->tt_sleep;
		if (sem_post(data->forks) != SUCCESS)
			exit(ERROR_EXIT);
		while (rising_time >= data->current_time)
			if (usleep(500) != SUCCESS)
				exit(ERROR_EXIT);
		data->status = THINKING;
		ft_print(data, "is thinking", 0);
	}
}
