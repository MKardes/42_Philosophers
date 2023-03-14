/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 13:20:44 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/25 15:33:39 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_sleep(long long time)
{
	long long	now;

	now = gettime();
	while (gettime() - now < time)
		usleep(100);
}

void	put_color(t_philo *philo)
{
	if (philo-> num % 10 == 0)
		printf("%s", D_GREEN);
	if (philo-> num % 10 == 1)
		printf("%s", D_RED);
	if (philo-> num % 10 == 2)
		printf("%s", D_YELLOW);
	if (philo-> num % 10 == 3)
		printf("%s", D_BLUE);
	if (philo-> num % 10 == 4)
		printf("%s", D_MAGENTA);
	if (philo-> num % 10 == 5)
		printf("%s", D_CYAN);
	if (philo-> num % 10 == 6)
		printf("%s", B_BLACK);
	if (philo-> num % 10 == 7)
		printf("%s", B_RED);
	if (philo-> num % 10 == 8)
		printf("%s", B_YELLOW);
	if (philo-> num % 10 == 9)
		printf("%s", WHITE);
}

int	print(char *s, t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->print));
	pthread_mutex_lock(&(philo->data->death));
	if (philo->data->death_check)
	{
		pthread_mutex_unlock(&(philo->data->death));
		pthread_mutex_unlock(&(philo->data->fork[philo->num]));
		pthread_mutex_unlock(&(philo->data->fork[(philo->num + 1)
				% philo->data->num_philo]));
		pthread_mutex_unlock(&(philo->data->print));
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->death));
	put_color(philo);
	printf("%lu X %d %s\n", gettime() - philo->data->start_t, philo->num + 1, s);
	if (s[0] == 'd')
	{
		pthread_mutex_lock(&(philo->data->death));
		philo->data->death_check = 1;
		pthread_mutex_unlock(&(philo->data->death));
	}
	pthread_mutex_unlock(&(philo->data->print));
	return (1);
}

long	gettime(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		return (0);
	init_data(&data, ac, av);
	init_philo(&data);
	free_all(&data);
}
