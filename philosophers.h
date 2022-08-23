#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define FORK philo->main->msgs[0]
# define EAT philo->main->msgs[1]
# define SLP philo->main->msgs[2]
# define THNK philo->main->msgs[3]
# define DIE philo->main->msgs[4]

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
/*
	pthread_create  //2046 ya kadar
	pthread_detach
	pthread_join

	pthread_mutex_lock(&mutex);
*/

# include <sys/time.h>
//	int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);

# include "libft/libft.h"

typedef struct s_main t_main;

typedef struct s_philo{
	pthread_t		td;
	t_main			*main;
	char			*color;
	char			*state;
	long			time;
	int				id;
	int				e_cnt;
}	t_philo;

typedef struct s_main{
	int				a_5;
	int				trgt;
	int				reach;
	int				a;
	int				d_chc;
	int				cnt;
	int				die;
	int				eat;
	int				slp;
	char			**msgs;
	char			**color;
	long			start_t;
	t_philo			*philo;
	pthread_mutex_t	*forks;
pthread_mutex_t	reach_m;
	pthread_mutex_t	p_mutex;
}	t_main;

void	c_strs_put(t_main *main);
void	fork_init(t_philo *philo);
void	*exit_mutex(t_philo *philo);
void	*loop(void *philos);
long	get_time(long time);
int		get_eat(t_philo *philo);
int		print(long time, t_philo *philo, char *msg);
int		main(int ac, char **av);
int		lock_fork(t_philo *philo);


#endif
