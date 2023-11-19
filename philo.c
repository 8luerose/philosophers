/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:18:58 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/19 18:02:57 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int main_thread_start(t_all_info *arg, t_philo *philo)
// {
// 	int i;
	
// 	i = 0;
// 	while (i < arg->philo)
// 	{
// 		philo[i].last_eat_time = get_time();
// 		if (pthread_create(&(philo[i].thread_id), NULL, make_thread, &(philo[i])))
// 			return (FAIL);
// 		i++;
// 	}
// 	always_on_monitoring(arg, philo);
// 	i = 0;
// 	while (i < arg->philo)
// 	{
// 		pthread_join(philo[i].thread_id, NULL);
// 		i++;
// 	}
// 	i = 0;
// 	pthread_mutex_destory(&(arg->mutex_for_print));
// 	while (i < arg->philo)
// 	{
// 		if (arg->forks_init_status[i])
//             pthread_mutex_destroy(&(arg->forks[i]));
//         i++;
// 	}
// 	free(arg->forks);
// 	free(philo);
// }

int main_thread_start(t_all_info *arg, t_philo *philo)
{
	int i;
	
	i = 0;
	while (i < arg->philo)
	{
		philo[i].last_eat_time = get_time();
		if (pthread_create(&(philo[i].thread_id), NULL, make_thread, &(philo[i])))
			return (FAIL);
		i++;
	}
	always_on_monitoring(arg, philo);
	return (SUCCESS);
}

int wait_thread_exit(t_all_info *arg, t_philo **philo)
{
	int i;

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
	int i;

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

void	*make_thread(void *pthread_create_info_philo_idx)
{
	t_philo		*philo_idx;
	t_all_info	*arg;

	philo_idx = (t_philo *)pthread_create_info_philo_idx;
	arg = philo_idx->p_arg;
	if (philo_idx->id % 2 == 1)
		usleep(1000);
	// if (philo_idx->id % 2 == 0)
	// 	usleep(1000);
	while (!arg->finish_flag)
	{
		philo_pick_up_fork(arg, philo_idx);
		if ((philo_must_eat_check(arg, philo_idx)) == SUCCESS)
			break ;
		// if (!arg->finish_flag)
		// {
		// 	message_print(arg, philo_idx->id, "is sleeping");
		// 	go_until_to_time((long long)arg->time_to_sleep, arg);
		// 	message_print(arg, philo_idx->id, "is thinking");
		// }
	
		message_print(arg, philo_idx->id, "is sleeping");
		go_until_to_time((long long)arg->time_to_sleep, arg);
		message_print(arg, philo_idx->id, "is thinking");
	}
	return (NULL);
}

// void	philo_pick_up_fork(t_all_info *arg, t_philo *philo)
// {
// 	pthread_mutex_t	philo_leftfork_id;
// 	pthread_mutex_t	philo_rightfork_id;

// 	if (arg->philo == 1)
//     {
// 		// philo_leftfork_id = arg->forks[philo->left_fork];
// 		// pthread_mutex_lock(&(philo_leftfork_id));
//         message_print(arg, philo->id, "has taken a fork");
// 		go_until_to_time((long long)arg->time_to_die, arg);
//         message_print(arg, philo->id, "died");
//         arg->finish_flag = 1;
//     }
// 	else
// 	{
// 		philo_leftfork_id = arg->forks[philo->left_fork];
// 		pthread_mutex_lock(&(philo_leftfork_id));
// 		message_print(arg, philo->id, "has taken a fork");
// 		philo_rightfork_id = arg->forks[philo->right_fork];
// 		pthread_mutex_lock(&(philo_rightfork_id));
// 		message_print(arg, philo->id, "has taken a fork");
// 		message_print(arg, philo->id, "is eating");
// 		philo->last_eat_time  = get_time();
// 		philo->eat_cnt++;
// 		go_until_to_time((long long)arg->time_to_eat, arg);
// 		pthread_mutex_unlock(&(philo_rightfork_id));
// 		pthread_mutex_unlock(&(philo_leftfork_id));
// 	}
// }

void philo_pick_up_fork(t_all_info *arg, t_philo *philo_idx)
{
    if (arg->philo == 1)
    {
        message_print(arg, philo_idx->id, "has taken a fork");
        go_until_to_time((long long)arg->time_to_die, arg);
        message_print(arg, philo_idx->id, "died");
        arg->finish_flag = 1;
    }
    else
    {
        pthread_mutex_lock(&(arg->forks[philo_idx->left_fork]));
        message_print(arg, philo_idx->id, "has taken a fork");
        pthread_mutex_lock(&(arg->forks[philo_idx->right_fork]));
        message_print(arg, philo_idx->id, "has taken a fork");
        message_print(arg, philo_idx->id, "is eating");
        philo_idx->last_eat_time = get_time();
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
		arg->total_eat++;
		return (SUCCESS);
	}
	return (FAIL);
}

void message_print(t_all_info *arg, int philo_id, char *msg)
{
	long long current_time;

	current_time = get_time();
	pthread_mutex_lock(&(arg->mutex_for_print));
	if (!(arg->finish_flag))
		printf("%lld %d %s \n", current_time - arg->init_time, philo_id + 1, msg);
	pthread_mutex_unlock(&(arg->mutex_for_print));
}

// void	always_on_monitoring(t_all_info *arg, t_philo *philo)
// {
// 	int			i;
// 	long long	current_time;

// 	while (!arg->finish_flag)
// 	{
// 		if ((arg->must_eat_cnt > 0) && (arg->philo == arg->total_eat))
// 		{
// 			arg->finish_flag = 1;
// 			break ;
// 		}
// 		i = 0;
// 		while (i < arg->philo)
// 		{
// 			current_time = get_time();
// 			if ((current_time - philo[i].last_eat_time) >= arg->time_to_die)
// 			{
// 				message_print(arg, i, "died");
// 				arg->finish_flag = 1;
// 				break ;
// 			}
// 			i++;
// 		}
// 	}
// }


////////////////////////////////////////////////////////


////1차 합친 코드/////

// void	always_on_monitoring(t_all_info *arg, t_philo *philo)
// {
// 	int i;
//     long long current_time;
	
// 	while (!arg->finish_flag)
// 	{
// 		if ((arg->must_eat_cnt > 0) && (arg->philo == arg->total_eat))
// 		{
// 			arg->finish_flag = 1;
// 			break;
// 		}

// 		i = 0;
// 		while (i < arg->philo)
// 		{
// 			current_time = get_time();
// 			if ((current_time - philo[i].last_eat_time) >= arg->time_to_die)
// 			{
// 				message_print(arg, i, "died");
// 				arg->finish_flag = 1;
// 				break;
// 			}
// 			i++;
// 		}
// 	}
// }

////2차 합친 코드/////

// void always_on_monitoring(t_all_info *arg, t_philo *philo)
// {
//     int i;
//     long long current_time;

//     while (!arg->finish_flag)
//     {
//         if ((arg->must_eat_cnt > 0) && (arg->philo == arg->total_eat))
//         {
//             arg->finish_flag = 1;
//             break;
//         }

//         i = 0;
//         while (i < arg->philo)
//         {
//             current_time = get_time();
//             if ((current_time - philo[i].last_eat_time) >= arg->time_to_die)
//             {
//                 message_print(arg, i, "died");
//                 arg->finish_flag = 1;
//                 break;
//             }
//             i++;
//         }
//     }
// }


//3차 합친 코드
void always_on_monitoring(t_all_info *arg, t_philo *philo)
{
    int i;
    long long current_time;

    while (!arg->finish_flag)
    {
        if ((arg->must_eat_cnt > 0) && (arg->philo == arg->total_eat))
        {
            arg->finish_flag = 1;
            break;
        }

        i = 0;
        while (i < arg->philo)
        {
            current_time = get_time();
            if ((current_time - philo[i].last_eat_time) >= arg->time_to_die)
            {
                message_print(arg, i, "died");
                arg->finish_flag = 1;
                break;
            }
            i++;
        }
    }
}

//////////////////////원래코드/////////////////
// void	always_on_monitoring(t_all_info *arg, t_philo *philo)
// {
// 	while (!arg->finish_flag)
// 	{
// 		if (must_eat_check((arg)) == SUCCESS)
// 			break ;
// 		if (time_to_die_check((arg), philo) == SUCCESS)
// 			break ;
// 	}
// }

//2차
// void	always_on_monitoring(t_all_info *arg, t_philo *philo)
// {
// 	int	i;

// 	while (!arg->finish_flag)
// 	{
// 		if (must_eat_check((arg)) == SUCCESS)
// 			break ;
// 		i = 0;
// 		while (i < arg->philo)
// 		{
// 			if (time_to_die_check((arg), philo, i) == SUCCESS)
// 				break ;
// 			i++;
// 		}
// 	}
// }

// int must_eat_check(t_all_info *arg)
// {
//     if ((arg->must_eat_cnt > 0) && (arg->philo == arg->total_eat))
//     {
//         arg->finish_flag = 1;
//     	return (SUCCESS);
// 	}
// 	else
// 		return (FAIL);
// }

// int time_to_die_check(t_all_info *arg, t_philo *philo, int i)
// {
//     long long current_time;

// 	current_time = get_time();
// 	if ((current_time - philo[i].last_eat_time) >= arg->time_to_die)
// 	{
// 		message_print(arg, i, "died");
// 		arg->finish_flag = 1;
// 		return (SUCCESS);
// 	}
//     return (FAIL);
// }


//원본 코드 백업
// void	always_on_monitoring(t_all_info *arg, t_philo *philo)
// {
// 	while (!arg->finish_flag)
// 	{
// 		if (must_eat_check((arg)) == SUCCESS)
// 			break ;
// 		if (time_to_die_check((arg), philo) == SUCCESS)
// 			break ;
// 	}
// }

// int must_eat_check(t_all_info *arg)
// {
//     if ((arg->must_eat_cnt > 0) && (arg->philo == arg->total_eat))
//     {
//         arg->finish_flag = 1;
//     	return (SUCCESS);
// 	}
// 	else
// 		return (FAIL);
// }

// int time_to_die_check(t_all_info *arg, t_philo *philo)
// {
//     int i;
//     long long current_time;

//     i = 0;
//     while (i < arg->philo)
//     {
//         current_time = get_time();
//         if ((current_time - philo[i].last_eat_time) >= arg->time_to_die)
//         {
//             message_print(arg, i, "died");
//             arg->finish_flag = 1;
//             return (SUCCESS);
//         }
//         i++;
//     }
//     return (FAIL);
// }