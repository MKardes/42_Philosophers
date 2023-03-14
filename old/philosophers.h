/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:24:38 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/25 15:34:10 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define FORK 'f'
# define EAT 'e'
# define SLP 's'
# define THNK 't'
# define DIE 'd'

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include "libft/libft.h"

typedef struct s_main	t_main;

typedef struct s_philo{
	pthread_t		td;
	t_main			*main;
	char			*color;
	char			*state;
	long			time;
	long			die_t;
	int				id;
	int				e_cnt;
}	t_philo;

typedef struct s_main{
	int				a_5;
	int				trgt;
	int				reach;
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
void	my_sleep(long long time);
long	get_time(long time);
int		get_eat(t_philo *philo);
int		print(long time, t_philo *philo, char c);
int		main(int ac, char **av);
int		lock_fork(t_philo *philo);

#endif
