#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# include <limits.h>

# define SUCCESS 0
# define FAILURE 1

# define EATING 0
# define SLEEPING 1
# define THINKING 2

# define MEAL_EXIT 0
# define DEATH_EXIT 1
# define ERROR_EXIT 2

typedef struct s_data
{
	int				no_philos;
	int64_t			tt_die;
	useconds_t		tt_eat;
	useconds_t		tt_sleep;
	int				no_meals;
	int64_t			start_time;
	int64_t			current_time;
	int				no;
	int				status;
	int64_t			last_time_eaten;
	int				meals_eaten;
	sem_t			*print;
	sem_t			*forks;
}				t_data;

int				init_data(t_data *data, int argc, char **argv);

void			*reaper(void *arg);
void			philosopher(t_data *data);

int				put_error(char *msg);
int				get_time(int64_t *ptr);
int				mini_atoi(int64_t *result, char *val);
void			ft_print(t_data *data, char *s, int twice);

#endif
