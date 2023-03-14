/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:20:44 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/25 15:33:39 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philo)
	{
		data->philo[i].num = i;
		data->philo[i].last_eat = 0;
		data->philo[i].data = data;
		data->philo[i].count = 0;
		pthread_mutex_init(&data->fork[i], NULL);
		pthread_create(&data->philo[i].thread, NULL,
			philo_control, &data->philo[i]);
	}
	i = -1;
	while (++i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
	}
}

void	init_data(t_data *data, int ac, char **av)
{
	data->num_philo = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->start_t = gettime();
	data->death_check = 0;
	data->count = 0;
	pthread_mutex_init(&(data->death), NULL);
	pthread_mutex_init(&(data->eat), NULL);
	pthread_mutex_init(&(data->print), NULL);
	if (ac == 6)
		data->num_eat = ft_atoi(av[5]);
	else
		data->num_eat = 0;
	data->philo = malloc(sizeof(t_philo) * data->num_philo);
	if (!(data->philo))
		return ;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!(data->fork))
		return ;
}
