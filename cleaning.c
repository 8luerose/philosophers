/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:59:37 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/22 17:56:11 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_waiting_thread(t_all_info *arg, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < arg->philo)
	{
		if (pthread_join((*philo)[i].thread_id, NULL))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	destroy_mutex(t_all_info *arg)
{
	int	i;

	i = 0;
	if (pthread_mutex_destroy(&(arg->mutex_for_print)))
		return (FAIL);
	while (i < arg->philo)
	{
		if (arg->forks_init_status[i])
		{
			if (pthread_mutex_destroy(&(arg->forks[i])))
				return (FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

void	free_all(t_all_info *arg, t_philo **philo)
{
	free(arg->forks_init_status);
	free(arg->forks);
	free(*philo);
}
