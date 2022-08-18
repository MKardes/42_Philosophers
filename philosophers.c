/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:55:20 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/19 00:20:40 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//void	print(t_philo *philo)

//void	get_fork()

void    *loop1(void *philos)
{
	int	i;
    t_philo	*philo;

	philo = (t_philo *)philos;
	i= 0;
	while(1)
	{
		//if (philo->id % 2)
		//	get_fork(philo, 2);
		printf("%s""Time: ""%d.Philosoph 🗿 %s  %d\n", philo->color, philo->id, philo->main->msgs[philo->id % 5], philo[0].main->philo[0].main->philo[0].main->philo[1].main->philo[4].id);
	}
	return (0);
}

void	thread_maker(char **av, t_main *main)
{
	int	i;

	i = 0;
	(*main) = c_strs_put();
	main->cnt = ft_atoi(av[1]);
	main->die = ft_atoi(av[2]);
	main->eat = ft_atoi(av[3]);
	main->slp = ft_atoi(av[4]);
	main->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * main->cnt);
	main->philo = (t_philo *)malloc(sizeof(t_philo) * main->cnt);
	while (i< main->cnt)
	{
		main->philo[i].state = 0;
		main->philo[i].color = main->color[i % 8];
		main->philo[i].id = i;
		main->philo[i].state = i % 4;
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
