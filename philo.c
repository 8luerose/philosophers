/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:18:58 by taehkwon          #+#    #+#             */
/*   Updated: 2023/10/31 22:34:11 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int philosophers(t_all_info *arg, t_philo *philo)
{
	int i;
	
	i = 0;
	while (i < arg->philo_num)
	{
		philo[i].last_eat_clock = get_time();
		if (pthread_create(&(philo[i].thread_id), NULL, make_thread, &(philo[i])))
			return (FAIL);
		i++;
	}
}

// void *make_thread(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	while (1)
// 	{
// 		if (philo->p_arg->must_eat_num != -1 && philo->eat_cnt >= philo->p_arg->must_eat_num)
// 			break ;
// 		if (philo->p_arg->philo_num % 2 == 1)
// 		{
// 			if (philo->id % 2 == 0)
// 				eat(philo);
// 			else
// 				sleep(philo);
// 		}
// 		else
// 		{
// 			if (philo->id % 2 == 0)
// 				sleep(philo);
// 			else
// 				eat(philo);
// 		}
// 	}
// 	return (NULL);
// }

void *make_thread()