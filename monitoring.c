/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:03:31 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/25 19:41:47 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	always_on_monitoring(t_all_info *arg, t_philo *philo)
{
	int	i;
	int	finish;

	while (1)
	{
		pthread_mutex_lock(&(arg->mutex_for_finish));
		finish = arg->finish_flag;
		pthread_mutex_unlock(&(arg->mutex_for_finish));
		if (finish)
			break ;
		if (must_eat_check(arg) == SUCCESS)
			break ;
		i = 0;
		while (i < arg->philo)
		{
			if (time_to_die_check(arg, philo, i) == SUCCESS)
				break ;
			i++;
		}
	}
}

int	must_eat_check(t_all_info *arg)
{
	int	total_eat;

	pthread_mutex_lock(&(arg->mutex_for_total_eat));
	total_eat = arg->total_eat;
	pthread_mutex_unlock(&(arg->mutex_for_total_eat));
	if ((arg->must_eat_cnt > 0) && (arg->philo == total_eat))
	{
		arg->finish_flag = 1;
		return (SUCCESS);
	}
	else
		return (FAIL);
}

int	time_to_die_check(t_all_info *arg, t_philo *philo, int i)
{
	long long	now_time;
	long long	last_eat_time;

	pthread_mutex_lock(&(philo[i].mutex_for_eat_time));
	last_eat_time = philo[i].last_eat_time;
	pthread_mutex_unlock(&(philo[i].mutex_for_eat_time));
	now_time = get_time();
	if ((now_time - last_eat_time) >= arg->time_to_die)
	{
		pthread_mutex_lock(&(arg->mutex_for_finish));
		if (!arg->finish_flag)
		{
			message_print(arg, i, "died");
			arg->finish_flag = 1;
		}
		pthread_mutex_unlock(&(arg->mutex_for_finish));
		return (SUCCESS);
	}
	return (FAIL);
}
