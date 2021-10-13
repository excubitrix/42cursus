#include "philo_three.h"

static int	launch_processes(t_data *data, pid_t **pid)
{
	int		i;

	*pid = malloc(sizeof(pid_t) * data->no_philos);
	if (!*pid)
		return (put_error("malloc() returned NULL\n"));
	i = -1;
	if (get_time(&data->current_time) != SUCCESS)
		return (put_error("gettimeofday() returned -1\n"));
	while (++i < data->no_philos)
	{
		data->no = i + 1;
		(*pid)[i] = fork();
		if (!(*pid)[i])
			philosopher(data);
		else if ((*pid)[i] < 0)
		{
			while (i--)
				kill((*pid)[i], SIGTERM);
			return (put_error("fork() returned -1\n"));
		}
	}
	return (SUCCESS);
}

static int	process_handler(t_data *data, pid_t *pid, int i)
{
	int64_t	time;
	int		stat;

	while (i--)
	{
		waitpid(-1, &stat, 0);
		if (WEXITSTATUS(stat) == DEATH_EXIT
			|| WEXITSTATUS(stat) == ERROR_EXIT)
		{
			while (data->no_philos--)
				kill(pid[data->no_philos], SIGTERM);
			if (WEXITSTATUS(stat) == ERROR_EXIT)
				return (put_error("Something went wrong "
						"in a child process\n"));
			break ;
		}
	}
	if (WEXITSTATUS(stat) == MEAL_EXIT)
	{
		if (get_time(&time) != SUCCESS)
			return (put_error("gettimeofday() returned -1\n"));
		printf("%llu \033[32mall done\033[0m\n", time - data->start_time);
	}
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pid_t		*pid;
	int			ret;

	pid = NULL;
	ret = SUCCESS;
	if (init_data(&data, argc, argv) != SUCCESS
		|| launch_processes(&data, &pid) != SUCCESS
		|| process_handler(&data, pid, data.no_philos) != SUCCESS)
		ret = FAILURE;
	if (data.print != SEM_FAILED)
	{
		sem_unlink("/print");
		sem_close(data.print);
	}
	if (data.forks != SEM_FAILED)
	{
		sem_unlink("/forks");
		sem_close(data.forks);
	}
	if (pid)
		free(pid);
	return (ret);
}
