/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:35:10 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/25 19:40:41 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_arg(t_all_info *arg, int ac, char **av)
{
	arg->philo = ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	arg->init_time = get_time();
	if (ac == 6)
	{
		arg->must_eat_cnt = ft_atoi(av[5]);
		if (arg->must_eat_cnt <= 0)
			return (FAIL);
	}
	if (arg->philo <= 0 || arg->time_to_die <= 0 || arg->time_to_eat <= 0
		|| arg->time_to_sleep <= 0)
		return (FAIL);
	if (init_mutex(arg))
		return (FAIL);
	return (SUCCESS);
}

int	init_mutex(t_all_info *arg)
{
	int	i;

	arg->forks = malloc(arg->philo * sizeof(pthread_mutex_t));
	arg->forks_init_status = malloc(arg->philo * sizeof(int));
	if (!(arg->forks) || !(arg->forks_init_status))
		return (FAIL);
	i = 0;
	while (i < arg->philo)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			arg->forks_init_status[i] = 0;
		else
			arg->forks_init_status[i] = 1;
		i++;
	}
	if (pthread_mutex_init(&(arg->mutex_for_print), NULL))
		return (FAIL);
	if (pthread_mutex_init(&(arg->mutex_for_finish), NULL))
		return (FAIL);
	if (pthread_mutex_init(&(arg->mutex_for_total_eat), NULL))
		return (FAIL);
	return (SUCCESS);
}

int	init_philo(t_all_info *arg, t_philo **philo)
{
	int		i;
	t_philo	*tmp;

	*philo = malloc(arg->philo * sizeof(t_philo));
	if (!(*philo))
		return (FAIL);
	tmp = *philo;
	i = 0;
	while (i < arg->philo)
	{
		tmp[i].id = i;
		tmp[i].left_fork = i;
		tmp[i].right_fork = (i + 1) % arg->philo;
		tmp[i].eat_cnt = 0;
		tmp[i].last_eat_time = get_time();
		tmp[i].p_arg = arg;
		pthread_mutex_init(&(tmp[i].mutex_for_eat_time), NULL);
		i++;
	}
	return (SUCCESS);
}
