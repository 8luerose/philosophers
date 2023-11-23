/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:18:58 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/23 19:57:59 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main_thread_start(t_all_info *arg, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < arg->philo)
	{
		printf("check*** 1\n\n");
		philo[i].last_eat_time = get_time();
		if (pthread_create(&(philo[i].thread_id), NULL, mk_thread, &(philo[i])))
			return (FAIL);
		i++;
		printf("check*** (%d %d)\n\n", i, arg->philo);
	}
	printf("check*** 2\n\n");
	always_on_monitoring(arg, philo);
	printf("check*** 3\n\n");
	return (SUCCESS);
}

void	*mk_thread(void *pthread_create_info_philo_idx)
{
	t_philo		*philo_idx;
	t_all_info	*arg;

	philo_idx = (t_philo *)pthread_create_info_philo_idx;
	arg = philo_idx->p_arg;
	if (philo_idx->id % 2 == 1)
		usleep(200);
	while (!arg->finish_flag)
	{
		printf("check### 1, finish_flag: %d\n\n", arg->finish_flag);
		philo_pick_up_fork(arg, philo_idx);
		printf("check### 2-1, finish_flag: %d\n\n", arg->finish_flag);
		if ((philo_must_eat_check(arg, philo_idx)) == SUCCESS)
		{
			printf("check### 2-2, finish_flag: %d\n\n", arg->finish_flag);
			break ;
		}
		printf("check### 3, finish_flag: %d\n\n", arg->finish_flag);
		message_print(arg, philo_idx->id, "is sleeping");
		go_until_to_time((long long)arg->time_to_sleep, arg);
		message_print(arg, philo_idx->id, "is thinking");
	}
	printf("check### 2-3, finish_flag: %d\n\n", arg->finish_flag);
	return (NULL);
}

void	philo_pick_up_fork(t_all_info *arg, t_philo *philo_idx)
{
	if (arg->philo == 1)
	{
		message_print(arg, philo_idx->id, "has taken a fork");
		printf("check@@@ 1\n\n");
		go_until_to_time((long long)arg->time_to_die, arg);
		printf("check@@@ 2\n\n");
		message_print(arg, philo_idx->id, "died");
		printf("check@@@ 3\n\n");
		arg->finish_flag = 1;
		printf("check@@@ 4\n\n");
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

// void philo_pick_up_fork(t_all_info *arg, t_philo *philo_idx)
// {
//     if (arg->philo == 1)
//     {
//         message_print(arg, philo_idx->id, "has taken a fork");
//         go_until_to_time((long long)arg->time_to_die, arg);
//         message_print(arg, philo_idx->id, "died");
//         arg->finish_flag = 1;
//     }
//     else
//     {
//         if (philo_idx->id % 2 == 0)
//         {
//             // 짝수 ID 철학자는 오른쪽 포크 먼저
//             pthread_mutex_lock(&(arg->forks[philo_idx->right_fork]));
//             message_print(arg, philo_idx->id, "has taken a fork");
//             pthread_mutex_lock(&(arg->forks[philo_idx->left_fork]));
//         }
//         else
//         {
//             // 홀수 ID 철학자는 왼쪽 포크 먼저
//             pthread_mutex_lock(&(arg->forks[philo_idx->left_fork]));
//             message_print(arg, philo_idx->id, "has taken a fork");
//             pthread_mutex_lock(&(arg->forks[philo_idx->right_fork]));
//         }
//         message_print(arg, philo_idx->id, "is eating");
//         pthread_mutex_lock(&(philo_idx->mutex_for_eat_time));
//         philo_idx->last_eat_time = get_time();
//         pthread_mutex_unlock(&(philo_idx->mutex_for_eat_time));
//         philo_idx->eat_cnt++;
//         go_until_to_time((long long)arg->time_to_eat, arg);
//         pthread_mutex_unlock(&(arg->forks[philo_idx->right_fork]));
//         pthread_mutex_unlock(&(arg->forks[philo_idx->left_fork]));
//     }
// }

int	philo_must_eat_check(t_all_info *arg, t_philo *philo)
{
	printf("check--- 1\n\n");
	if (arg->must_eat_cnt == philo->eat_cnt)
	{
		printf("check--- 2\n\n");
		arg->total_eat++;
		printf("check--- 3\n\n");
		return (SUCCESS);
		printf("check--- 4\n\n");
	}
	printf("check--- 5\n\n");
	return (FAIL);
}

void	message_print(t_all_info *arg, int philo_id, char *msg)
{
	printf("check!!! 2-1\n\n");
	long long	now_time;

	now_time = get_time();
	pthread_mutex_lock(&(arg->mutex_for_print));
	if (!(arg->finish_flag))
	{
		printf("%lld %d %s \n", now_time - arg->init_time, philo_id + 1, msg);
		printf("check!!! 2-2\n\n");
	}
	pthread_mutex_unlock(&(arg->mutex_for_print));
	printf("check!!! 2-3\n\n");
}
