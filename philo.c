/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:18:58 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/15 22:31:21 by taehkwon         ###   ########.fr       */
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
	if (philo->id % 2 == 1)
		usleep(2000);
	while (!arg->finish_flag)
	{
		philo_pick_up_fork(arg, philo);
		if (philo_must_eat_check(arg, philo));
			break ;
		message_print(arg, philo->id, "is sleeping");
		if (!arg->finish_flag)
		{
			until_to_timeout(arg, arg->time_sleep);
			message_print(arg, philo->id, "is thinking");
		}
	}
}

int	philo_pick_up_fork(t_all_info *arg, t_philo *philo)
{
	pthread_mutex_t	philo_leftfork_id;
	pthread_mutex_t	philo_rightfork_id;

	if (arg->philo == 1)
	{
		philo_leftfork_id = arg->forks[philo->left_fork];
		pthread_mutex_lock(&(philo_leftfork_id));
		message_print(arg, philo->id, "has taken a fork");
		arg->finish_flag = 1;
		pthread_mutex_unlock(&(philo_leftfork_id));
	}
	else
	{
		philo_leftfork_id = arg->forks[philo->left_fork];
		philo_rightfork_id = arg->forks[philo->right_fork];
		pthread_mutex_lock(&(philo_leftfork_id));
		message_print(arg, philo->id, "has taken a fork");
		pthread_mutex_lock(&(philo_rightfork_id));
		message_print(arg, philo->id, "has taken a fork");
		message_print(arg, philo->id, "is eating");
		philo->last_eat_clock = get_time();
		philo->eat_cnt++;
		pass_time()


		pthread_mutex_unlock(&(philo_leftfork_id));
		message_print(arg, philo->id, )
	}

}

int message_print(t_all_info *arg, int philo_id, char *msg)
{
	
}