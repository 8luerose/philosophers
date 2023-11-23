/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:03:31 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/23 19:58:35 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	always_on_monitoring(t_all_info *arg, t_philo *philo)
{
	int	i;

	while (!arg->finish_flag)
	{
		printf("check&&& 1, finish_flag: %d\n\n", arg->finish_flag);
		if (must_eat_check((arg)) == SUCCESS)
			break ;
		i = 0;
		printf("check&&& 2, finish_flag: %d\n\n", arg->finish_flag);
		while (i < arg->philo)
		{
			if (time_to_die_check((arg), philo, i) == SUCCESS)
				break ;
			i++;
		}
	}
	printf("check&&& 3, finish_flag: %d\n\n", arg->finish_flag);
}

int	must_eat_check(t_all_info *arg)
{
	if ((arg->must_eat_cnt > 0) && (arg->philo == arg->total_eat))
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

	now_time = get_time();
	pthread_mutex_lock(&(philo[i].mutex_for_eat_time));
	if ((now_time - philo[i].last_eat_time) >= arg->time_to_die)
	{
		printf("check!!! 1, finish_flag: %d\n\n", arg->finish_flag);
		message_print(arg, i, "died");
		printf("check!!! 3\n\n");
		printf("check!!! arg->finish_flag = %d\n", arg->finish_flag);
		arg->finish_flag = 1;
		pthread_mutex_unlock(&(philo[i].mutex_for_eat_time));
		return (SUCCESS);
	}
	return (FAIL);
}
