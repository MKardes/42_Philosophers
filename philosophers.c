/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:20 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/21 23:19:21 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*exit_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->main->cnt)
	{
		pthread_mutex_unlock(&philo->main->forks[i]);
		i++;
	}
	return (0);
}

int	get_think(t_philo *philo)
{
	philo->state[3] = 0;
	if (!print(get_time(philo->time), philo, THNK))
		return (0);
	philo->state[4] = 1;
	return (1);
}

int	get_sleep(t_philo *philo)
{
	philo->state[0] = 0;
	philo->state[1] = 0;
	philo->state[2] = 0;
	if (!print(get_time(philo->time), philo, SLP))
		return (0);
	if (philo->main->slp > philo->main->die)
		return (!print(get_time(philo->time - philo->main->die + 1), philo, DIE));
	usleep(philo->main->slp * 1000);
	philo->state[3] = 1;
	return (1);
}

int	get_eat(t_philo *philo)
{
	philo->state[2] = 1;
	if (!print(get_time(philo->time), philo, EAT))
		return (0);
	usleep(philo->main->eat * 1000);
	pthread_mutex_unlock(&philo->main->forks[philo->id]);
	philo->state[0] = 0;
	if (philo->id != philo->main->cnt - 1)
		pthread_mutex_unlock(&philo->main->forks[philo->id + 1]);
	else
		pthread_mutex_unlock(&philo->main->forks[0]);
	philo->state[1] = 0;
	return (1);
}

int	lock_fork(t_philo *philo)
{
	int	time;
	
	time = get_time(philo->time);
	if (!philo->state[0])
	{
		pthread_mutex_lock(&philo->main->forks[philo->id]);
		if (get_time(philo->time) - time + philo->main->slp > philo->main->die)
			return (!print(get_time(philo->time), philo, DIE));
		if (!print(get_time(philo->time), philo, FORK))
			return (0);
		philo->state[0] = 1;
	}
	if (!philo->state[1])
	{
		if (philo->id != philo->main->cnt - 1)
		{
			pthread_mutex_lock(&philo->main->forks[philo->id + 1]);
			if (get_time(philo->time) - time + philo->main->slp > philo->main->die)
				return (!print(get_time(philo->time), philo, DIE));
		}
		else
		{
			pthread_mutex_lock(&philo->main->forks[0]);
			if (get_time(philo->time) - time + philo->main->slp > philo->main->die)
				return (!print(get_time(philo->time), philo, DIE));
		}
		if (!print(get_time(philo->time), philo, FORK))
			return (0);
		philo->state[1] = 1;
	}
	if (philo->state[0] && philo->state[1])
		return (get_eat(philo));
	return(1);
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
	while (1)
	{
		if (philo->state[4] || (!philo->state[0] && !philo->state[1]
				&& !philo->state[2] && !philo->state[3] && !philo->state[4]))
			if (!lock_fork(philo))
				return (exit_mutex(philo));
		if (philo->state[2])
			if (!get_sleep(philo))
				return (exit_mutex(philo));
		if (philo->state[3])
			if (!get_think(philo))
				return (exit_mutex(philo));
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
	main->d_chc = 0;
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main->cnt);
	main->philo = (t_philo *)malloc(sizeof(t_philo) * main->cnt);
	pthread_mutex_init(&main->p_mutex, NULL);
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
	i = 0;
}

int	main(int ac, char **av)
{
	t_main		main;

	if (ac == 4 || ac == 5)
	{
		printf("Die time : %s\nEat time: %s\nSleep time: %s\n\n", av[2], av[3], av[4]);
		thread_maker(av, &main);
	}
	return(0);
}
