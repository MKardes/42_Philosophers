/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:20:44 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/25 15:33:39 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

//colors
# define D_RED "\033[0;31m"
# define D_GREEN "\033[0;32m"
# define D_YELLOW "\033[0;33m"
# define D_BLUE "\033[0;34m"
# define D_MAGENTA "\033[0;35m"
# define D_CYAN "\033[0;36m"
# define B_BLACK "\033[0;90m"
# define B_RED "\033[0;91m"
# define B_YELLOW "\033[0;93m"
# define WHITE "\033[0;97m"

typedef struct s_philo	t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_eat;
	int				death_check;
	long			start_t;
	int				count;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	death;
	pthread_mutex_t	eat;
	pthread_mutex_t	print;
}	t_data;

typedef struct s_philo
{	
	long		last_eat;
	int			num;
	int			count;
	t_data		*data;
	pthread_t	thread;
}	t_philo;

void	put_color(t_philo *philo);
int		ft_atoi(const char *str);
void	init_data(t_data *data, int ac, char **av);
void	init_philo(t_data *data);
void	my_sleep(long long time);
int		print(char *s, t_philo *philo);
long	gettime(void);
int		death_check(t_philo *philo);
int		eating(t_philo *philo);
int		take_fork(t_philo *philo);
void	*philo_control(void *ptr);
void	free_all(t_data *data);

#endif
