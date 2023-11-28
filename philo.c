/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:18:58 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/28 21:35:09 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_thread_start(t_all_info *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->philo)
	{
		philo[i].last_eat_time = get_time();
		if (pthread_create(&(philo[i].thread_id), NULL, mk_thread, &(philo[i])))
			return (FAIL);
		i++;
	}
	always_on_monitoring(arg, philo);
	return (SUCCESS);
}

void	*mk_thread(void *pthread_create_info_philo_idx)
{
	t_philo		*philo_idx;
	t_all_info	*arg;
	int			finish;

	philo_idx = (t_philo *)pthread_create_info_philo_idx;
	arg = philo_idx->p_arg;
	if (philo_idx->id % 2 == 1)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(&(arg->mutex_for_finish));
		finish = arg->finish_flag;
		pthread_mutex_unlock(&(arg->mutex_for_finish));
		if (finish)
			break ;
		philo_pick_up_fork(arg, philo_idx);
		if (philo_must_eat_check(arg, philo_idx) == SUCCESS)
			break ;
		message_print(arg, philo_idx->id, "is sleeping");
		go_until_to_time((long long)arg->time_to_sleep, arg);
		message_print(arg, philo_idx->id, "is thinking");
	}
	return (NULL);
}

void	philo_pick_up_fork(t_all_info *arg, t_philo *philo_idx)
{
	if (arg->philo == 1)
	{
		message_print(arg, philo_idx->id, "has taken a fork");
		go_until_to_time((long long)arg->time_to_die, arg);
		message_print(arg, philo_idx->id, "died");
		pthread_mutex_lock(&(arg->mutex_for_finish));
		arg->finish_flag = 1;
		pthread_mutex_unlock(&(arg->mutex_for_finish));
	}
	else
	{
		pthread_mutex_lock(&(arg->forks[philo_idx->left_fork]));
		message_print(arg, philo_idx->id, "has taken a fork");
		pthread_mutex_lock(&(arg->forks[philo_idx->right_fork]));
		message_print(arg, philo_idx->id, "has taken a fork");
		message_print(arg, philo_idx->id, "is eating");
		pthread_mutex_lock(&(philo_idx->mutex_for_eat_time));
		philo_idx->last_eat_time = get_time();
		pthread_mutex_unlock(&(philo_idx->mutex_for_eat_time));
		philo_idx->eat_cnt++;
		go_until_to_time((long long)arg->time_to_eat, arg);
		pthread_mutex_unlock(&(arg->forks[philo_idx->right_fork]));
		pthread_mutex_unlock(&(arg->forks[philo_idx->left_fork]));
	}
}

int	philo_must_eat_check(t_all_info *arg, t_philo *philo)
{
	if (arg->must_eat_cnt == philo->eat_cnt)
	{
		pthread_mutex_lock(&(arg->mutex_for_total_eat));
		arg->total_eat++;
		pthread_mutex_unlock(&(arg->mutex_for_total_eat));
		return (SUCCESS);
	}
	return (FAIL);
}

void	message_print(t_all_info *arg, int philo_id, char *msg)
{
	long long	now_time;
	// int			finish;

	now_time = get_time();
	// pthread_mutex_lock(&(arg->mutex_for_finish));
	// finish = arg->finish_flag;
	// pthread_mutex_unlock(&(arg->mutex_for_finish));
	pthread_mutex_lock(&(arg->mutex_for_print));
	if (!arg->finish_flag)
		printf("%lld %d %s \n", now_time - arg->init_time, philo_id + 1, msg);
	pthread_mutex_unlock(&(arg->mutex_for_print));
}
