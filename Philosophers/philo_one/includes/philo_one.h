#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# include <limits.h>

# define SUCCESS 0
# define FAILURE 1

# define EATING 1
# define SLEEPING 2
# define THINKING 0

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
	int				done;
	int				death;
	int				locks_init;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
	pthread_mutex_t	count;
	pthread_mutex_t	*fork;
	char			*error;
}				t_data;

typedef struct s_info
{
	int				no;
	int				left_fork;
	int				status;
	int64_t			last_time_eaten;
	t_data			*data;
}				t_info;

int				init_philo(t_info *info, t_data *data);
int				init_data(t_data *data, int argc, char **argv);

void			*reaper(void *arg);
void			*philosopher(void *arg);

int				get_time(int64_t *ptr);
int				ft_print(t_data *data, int no, char *s, int twice);
int				*set_error(t_data *data, char *msg);
int				put_error(t_data *data, char *msg);
void			free_all(t_data *data);

#endif
