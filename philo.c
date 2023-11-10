/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:18:58 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/10 19:07:42 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main_thread_start(t_all_info *arg, t_philo *philo)
{
	int i;
	
	i = 0;
	while (i < arg->philo)
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
// 		if (philo->p_arg->must_eat_cnt != -1 && philo->eat_cnt >= philo->p_arg->must_eat_cnt)
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

void *make_thread(void *pthread_create_info_philo_i)
{
	t_philo		*philo;
	t_all_info	*arg;

	philo = (t_philo *)pthread_create_info_philo_i;
	arg = philo->p_arg;
	id (philo->id % 2 == 1)
		usleep(2000);
	while (!arg->finish_flag)
	{
		philo_pick_up_fork(arg, philo);
		if (philo_must_eat_check(arg, philo));
			break ;
		message_print(arg, philo->id, "is sleeping");
		start_to_pass_time

	}
}