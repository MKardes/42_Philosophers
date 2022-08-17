/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:20 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/17 19:16:47 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//int	a = 0;
//pthread_mutex_t mutex;

void	*routine(void *philos)
{
	long long	i;
	t_philo		*philo;	

	philo = (t_philo *)philos;
	i = 0;
	while (i < 10000)
	{
		pthread_mutex_lock(&(philo->mutex));
		//a++;
		pthread_mutex_unlock(&(philo->mutex));
		i++;
	}
	return (0);
}

void    *loop1(void *philos)
{
    t_philo	*philo;

	philo = (t_philo *)philos;
	while(1)
		printf("%s""%d.Philosoph is doing this.%d\n", philo->color[philo->id], philo->id, philo->state);
	return (0);
}

void	f_color(t_philo *main);

void	thread_maker(char **av, t_main *main)
{
	int	i;

	i = 0;
	main->cnt = ft_atoi(av[1]);
	main->die = ft_atoi(av[2]);
	main->eat = ft_atoi(av[3]);
	main->slp = ft_atoi(av[4]);
	main->philo = (t_philo *)malloc(sizeof(t_philo) * main->cnt);
	while (i< main->cnt)
	{
		main->philo[i].id = i;
		main->philo[i].state = (i * i) % 3;
		pthread_create(&(main->philo[i].td), NULL, loop1, &main->philo[i]);
		pthread_mutex_init(&main->philo[i].mutex, NULL);
		f_color(&main->philo[i]);
		i++;
	}
	i = 0;
	while (i< main->cnt)
	{
		pthread_join(main->philo[i].td, NULL);
		i++;
	}
}

void	f_color(t_philo *main)
{
	main->color = (char	**)malloc(sizeof(char *) * 8);
 	main->color[0] = ft_strdup("\033[0;90m");
 	main->color[1] = ft_strdup("\033[0;91m");
	main->color[2] = ft_strdup("\033[0;92m");
	main->color[3] = ft_strdup("\033[0;93m");
	main->color[4] = ft_strdup("\033[0;94m");
	main->color[5] = ft_strdup("\033[0;95m");
	main->color[6] = ft_strdup("\033[0;96m");
	main->color[7] = ft_strdup("\033[0;97m");
}

int	main(int ac, char **av)
{
	t_main		main;
	if (ac > 1)
		thread_maker(av, &main);
	return(0);
}
