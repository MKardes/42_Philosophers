/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:20:44 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/25 15:33:39 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*exit_mutex(t_philo *philo)
{
	usleep(1000);
	pthread_mutex_unlock(&philo->main->forks[philo->id]);
	pthread_mutex_unlock(&philo->main->forks
	[(philo->id + 1) % philo->main->cnt]);
	return (0);
}

int	get_think(t_philo *philo)
{
	philo->state[2] = 0;
	if (!print(get_time(philo->time), philo, THNK))
		return (0);
	philo->state[3] = 1;
	return (1);
}

int	get_sleep(t_philo *philo)
{
	philo->state[0] = 0;
	philo->state[1] = 0;
	if (!print(get_time(philo->time), philo, SLP))
		return (0);
	if (get_time(philo->time) + philo->main->slp > philo->die_t)
		return (print(philo->die_t, philo, DIE));
	my_sleep(philo->main->slp);
	philo->state[2] = 1;
	return (1);
}

int	get_eat(t_philo *philo)
{
	philo->state[1] = 1;
	if (!print(get_time(philo->time), philo, EAT))
		return (0);
	philo->die_t = get_time(philo->time) + philo->main->die;
	philo->e_cnt++;
	if (philo->e_cnt == philo->main->trgt)
	{
		pthread_mutex_lock(&philo->main->reach_m);
		philo->main->reach++;
		pthread_mutex_unlock(&philo->main->reach_m);
	}
	if (philo->main->a_5 && philo->main->reach == philo->main->cnt)
		return (print(0, philo, '-'));
	if (philo->main->eat > philo->main->die)
		return (print(philo->die_t, philo, DIE));
	else
		my_sleep(philo->main->eat);
	pthread_mutex_unlock(&philo->main->forks[philo->id]);
	pthread_mutex_unlock(&philo->main->forks
	[(philo->id + 1) % philo->main->cnt]);
	philo->state[0] = 0;
	return (1);
}

void	*loop(void *philos)
{
	t_philo	*philo;

	philo = (t_philo *)philos;
	if (philo->main->cnt == 1)
	{
		print(get_time(philo->time), philo, FORK);
		print(get_time(philo->time), philo, DIE);
		return (0);
	}
	if (philo->id % 2)
		usleep(15000);
	while (1)
	{
		if (!lock_fork(philo))
			return (exit_mutex(philo));
		if (philo->state[1])
			if (!get_sleep(philo))
				return (exit_mutex(philo));
		if (philo->state[2])
			if (!get_think(philo))
				return (exit_mutex(philo));
	}
	return (0);
}
