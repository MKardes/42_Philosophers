/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:20 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/24 20:50:52 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	lock_fork(t_philo *philo)
{
	int	time;

	time = get_time(philo->time);
	if (!philo->state[0])
	{
		pthread_mutex_lock(&philo->main->forks[philo->id]);
		pthread_mutex_lock(&philo->main->forks[(philo->id + 1) % philo->main->cnt]);
		if (!print(get_time(philo->time), philo, FORK))
            return (0);
		if (!print(get_time(philo->time), philo, FORK))
            return (0);
		if (get_time(philo->time) - time > philo->main->die - philo->main->slp - philo->main->eat)
			return (print(get_time(philo->time), philo, DIE));
		philo->state[0] = 1;
		return (get_eat(philo));
	}
	return (1);
}

long	get_time(long time)
{
	struct timeval	tv;
	long			now;

	gettimeofday(&tv, NULL);
	now = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (time == 0)
		return (now);
	return (now - time);
}

void	thread_maker(char **av, t_main *main)
{
	int	i;

	i = -1;
	c_strs_put(main);
	main->start_t = get_time(0);
	main->cnt = ft_atoi(av[1]);
	main->die = ft_atoi(av[2]);
	main->eat = ft_atoi(av[3]);
	main->slp = ft_atoi(av[4]);
	main->d_chc = 0;
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main->cnt);
	main->philo = (t_philo *)malloc(sizeof(t_philo) * main->cnt);
	pthread_mutex_init(&main->p_mutex, NULL);
	pthread_mutex_init(&main->reach_m, NULL);
	while (++i < main->cnt)
	{
		main->philo[i].time = main->start_t;
		main->philo[i].state = malloc(4);
		main->philo[i].color = main->color[i % 8];
		main->philo[i].id = i;
		pthread_create(&(main->philo[i].td), NULL, loop, &main->philo[i]);
		pthread_mutex_init(&main->forks[i], NULL);
		main->philo[i].main = main;
		main->philo[i].e_cnt = 0;
		main->philo[i].die_t = main->start_t + main->die;
	}
	i = -1;
	while (++i < main->cnt)
		pthread_join(main->philo[i].td, NULL);
}

int	main(int ac, char **av)
{
	t_main		main;

	if (ac == 5 || ac == 6)
	{
		printf("Die time : %s\nEat time: %s\nSleep time: %s\n\n", av[2], av[3], av[4]);
		main.a_5 = 0;
		if (ac == 6)
		{
			main.trgt = ft_atoi(av[5]);
			main.reach = 0;
			main.a_5 = 1;
		}
		thread_maker(av, &main);
	}
	return (0);
}
