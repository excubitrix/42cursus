#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>

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
	int				printing;
	int				sems_init;
	sem_t			*count;
	sem_t			*check;
	sem_t			*eat;
	sem_t			*print;
	sem_t			*forks;
	char			*error;
}				t_data;

typedef struct s_info
{
	int				no;
	int				status;
	int64_t			last_time_eaten;
	t_data			*data;
}				t_info;

int				init_philo(t_info *info, t_data *data);
int				init_data(t_data *data, int argc, char **argv);

void			close_sems(t_data *data);

void			*reaper(void *arg);
void			*philosopher(void *arg);

int				get_time(int64_t *ptr);
int				ft_print(t_data *data, int no, char *s, int twice);
int				*set_error(t_data *data, char *msg);
int				put_error(t_data *data, char *msg);

#endif
