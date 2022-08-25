/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkardes <mkardes@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:35:36 by mkardes           #+#    #+#             */
/*   Updated: 2022/08/25 15:50:54 by mkardes          ###   ########.fr       */
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
	main->msgs[5] = ft_strdup
		("-----The philosophers have reached their eating target 🎯-----\n");
}

static char	*massage_put(char a, t_philo *philo)
{
	if (a == 'f')
		return (philo->main->msgs[0]);
	else if (a == 'e')
		return (philo->main->msgs[1]);
	else if (a == 's')
		return (philo->main->msgs[2]);
	else if (a == 't')
		return (philo->main->msgs[3]);
	else if (a == 'd')
	{
		philo->main->d_chc = 1;
		return (philo->main->msgs[4]);
	}
	else if (a == '-')
	{
		philo->main->d_chc = 1;
		printf("%s", philo->main->msgs[5]);
	}
	return (NULL);
}

int	print(long time, t_philo *philo, char c)
{
	pthread_mutex_lock(&philo->main->p_mutex);
	if (philo->main->d_chc)
	{
		exit_mutex(philo);
		pthread_mutex_unlock(&philo->main->p_mutex);
		return (0);
	}
	if (c == '-')
	{
		massage_put(c, philo);
		pthread_mutex_unlock(&philo->main->p_mutex);
		return (0);
	}
	else
	{
		printf("%s""Time:%ld\t""%d.Philosoph 🗿 %s\n", philo->color, time,
			philo->id + 1, massage_put(c, philo));
		if (c == 'd')
		{
			pthread_mutex_unlock(&philo->main->p_mutex);
			return (0);
		}
	}
	pthread_mutex_unlock(&philo->main->p_mutex);
	return (1);
}
