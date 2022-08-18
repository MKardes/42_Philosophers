#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define GRAY "\033[0;90m"
# define RED "\033[0;90m"
# define GREEN "\033[0;90m"
# define YELLOW "\033[0;90m"
# define BLUE "\033[0;90m"
# define MAGENTA "\033[0;90m"
# define CYAN "\033[0;90m"
# define WHITE "\033[0;90m"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
/*
	pthread_create  //2046 ya kadar
	pthread_detach
	pthread_join
*/

# include <sys/time.h>
//	int gettimeofday(struct timeval *restrict tv, struct timezone *restrict tz);

# include "libft/libft.h"

typedef struct s_main t_main;

typedef struct s_philo{
	pthread_t		td;
	t_main			*main;
	char			*color;
	int				id;
	char			*state;
}	t_philo;

typedef struct s_main{
	int				cnt;
	int				die;
	int				eat;
	int				slp;
	char			**msgs;
	char			**color;
	t_philo			*philo;
	pthread_mutex_t	*forks;
}	t_main;

t_main c_strs_put(void);

#endif
