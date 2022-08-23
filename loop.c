/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:20:44 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/23 17:56:06 by mkardes          ###   ########.fr       */
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
	if (philo->main->d_chc)
        return (0);
	philo->state[2] = 1;
	if (!print(get_time(philo->time), philo, EAT))
		return (0);
	philo->e_cnt++;
	if (philo->e_cnt == philo->main->trgt)
	{
		pthread_mutex_lock(&philo->main->reach_m);
		philo->main->reach++;
		pthread_mutex_unlock(&philo->main->reach_m);
	}
	if (philo->main->reach == philo->main->cnt)
		return (!print(0, philo, philo->main->msgs[5]));
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
