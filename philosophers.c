/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:20 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/19 16:41:05 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_fork(t_philo *philo)
{
	if (philo->state[0] && !philo->state[1])
	{
		if (philo->id != philo->main->cnt - 1)
		{
			philo->state[1] = 1;
		}
		else
		{
			philo->state[1] = 1;
		}
	}
	if (philo->state[1] && !philo->state[0])
	{
		philo->state[0] = 1;
	}
}

void	get_think(t_philo *philo)
{
	philo->state[3] = 0;
	print(get_time(philo->time), philo, THNK);
	philo->state[4] = 1;
}

void	get_sleep(t_philo *philo)
{
	philo->state[0] = 0;
	philo->state[1] = 0;
	philo->state[2] = 0;
	print(get_time(philo->time), philo, SLP);
	usleep(philo->main->slp * 1000);
	philo->state[3] = 1;
}

void	get_eat(t_philo *philo)
{
	philo->state[2] = 1;
	print(get_time(philo->time), philo, EAT);
	usleep(philo->main->eat * 1000);
	pthread_mutex_unlock(&philo->main->forks[philo->id]);
	philo->state[0] = 0;
	if (philo->id != philo->main->cnt - 1)
		pthread_mutex_unlock(&philo->main->forks[philo->id + 1]);
	else
		pthread_mutex_unlock(&philo->main->forks[0]);
	philo->state[1] = 0;

}

void	lock_fork(t_philo *philo)
{
	if (!philo->state[0])
	{	
		pthread_mutex_lock(&philo->main->forks[philo->id]);
		print(get_time(philo->time), philo, FORK);
		philo->state[0] = 1;
	}
	if (!philo->state[1])
	{
		if (philo->id != philo->main->cnt - 1)
			pthread_mutex_lock(&philo->main->forks[philo->id + 1]);
		else
			pthread_mutex_lock(&philo->main->forks[0]);
		print(get_time(philo->time), philo, FORK);
		philo->state[1] = 1;
	}
	if (philo->state[0] && philo->state[1])
		get_eat(philo);
}

long	get_time(long time)
{
	struct timeval	tv;
	long			now;
	
	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (time == 0)
		return(now);
	return (now - time);
}

void	print(long time, t_philo *philo, char *msg)
{
	printf("%s""Time:%ld\t""%d.Philosoph 🗿 %s\n", philo->color, time, philo->id + 1, msg);
}

void	fork_init(t_philo *philo)
{
	pthread_mutex_lock(&philo->main->forks[philo->id]);
	print(get_time(philo->time), philo, FORK);
	philo->state[0] = 1;
	if (philo->id != philo->main->cnt - 1)
		pthread_mutex_lock(&philo->main->forks[philo->id + 1]);
	else
		pthread_mutex_lock(&philo->main->forks[0]);
	philo->state[1] = 1;
	print(get_time(philo->time), philo, FORK);
	get_eat(philo);
}

void    *loop1(void *philos)
{
    t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->id % 2)
		fork_init(philo);
	else
		usleep(philo->main->eat * 1000);
	while(1)
	{
		lock_fork(philo);
		if (philo->state[2])
			get_sleep(philo);
		if (philo->state[3])
			get_think(philo);
	}
	return (0);
}

void	thread_maker(char **av, t_main *main)
{
	int	i;

	i = 0;
	(*main) = c_strs_put();
	main->start_t = get_time(0);
	main->cnt = ft_atoi(av[1]);
	main->die = ft_atoi(av[2]);
	main->eat = ft_atoi(av[3]);
	main->slp = ft_atoi(av[4]);
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main->cnt);
	main->philo = (t_philo *)malloc(sizeof(t_philo) * main->cnt);
	while (i< main->cnt)
	{
		main->philo[i].time = main->start_t;
		main->philo[i].state = malloc(5);
		main->philo[i].color = main->color[i % 8];
		main->philo[i].id = i;
		pthread_create(&(main->philo[i].td), NULL, loop1, &main->philo[i]);
		pthread_mutex_init(&main->forks[i], NULL);
		main->philo[i].main = main;
		i++;
	}
	i = 0;
	while (i< main->cnt)
	{
		pthread_join(main->philo[i].td, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_main		main;
	int		i;

	if (ac == 4 || ac == 5)
	{
		thread_maker(av, &main);
		i = 0;
		while (i++ < main.cnt)
			pthread_mutex_destroy(&main.forks[i]);
	}
	//printf("((%d))\n",a);
	return(0);
}
