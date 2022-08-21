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
}	t_philo;

typedef struct s_main{
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
	pthread_mutex_t	p_mutex;
}	t_main;

t_main	c_strs_put(void);
int		print(long time, t_philo *philo, char *msg);
long	get_time(long time);
int		main(int ac, char **av);

#endif
