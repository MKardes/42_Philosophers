/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student->42kocaeli->com->tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:54:43 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/23 17:55:58 by mkardes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	c_strs_put(t_main *main)
{
	main->color = (char **)malloc(sizeof(char *) * 8);
	main->color[7] = ft_strdup("\033[0;34m");
	main->color[4] = ft_strdup("\033[0;31m");
	main->color[2] = ft_strdup("\033[0;92m");
	main->color[3] = ft_strdup("\033[0;93m");
	main->color[1] = ft_strdup("\033[0;94m");
	main->color[5] = ft_strdup("\033[0;95m");
	main->color[6] = ft_strdup("\033[0;96m");
	main->color[0] = ft_strdup("\033[0;97m");
	main->msgs = (char **)malloc(sizeof(char *) * 6);
	main->msgs[0] = ft_strdup("has taken a fork 🍴");
	main->msgs[1] = ft_strdup("is eating 🍝");
	main->msgs[2] = ft_strdup("is sleeping 💤");
	main->msgs[3] = ft_strdup("is thinking 💬");
	main->msgs[4] = ft_strdup("died! ⚰️ ");
	main->msgs[5] = ft_strdup("-----The philosophers reached their eating target 🎯-----\n");
}

int	print(long time, t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->main->p_mutex);
	if (philo->main->d_chc)
	{
		pthread_mutex_unlock(&philo->main->p_mutex);
		usleep(100000);
		exit_mutex(philo);
		return (0);
	}
	if (msg[0] == '-')
	{
		philo->main->d_chc = 1;
		pthread_mutex_unlock(&philo->main->p_mutex);
		return(0);
	}
	else
	{
		printf("%s""Time:%ld\t""%d.Philosoph 🗿 %s\n", philo->color, time, philo->id + 1, msg);
		if (msg[0] == 'd')
		{
			philo->main->d_chc = 1;
			pthread_mutex_unlock(&philo->main->p_mutex);
			return(0);
		}
	}
	pthread_mutex_unlock(&philo->main->p_mutex);
	return (1);
}
