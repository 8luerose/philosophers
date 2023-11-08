/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:35:10 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/08 19:58:12 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_arg(t_all_info *arg, int ac, char **av)
{
	arg->philo_num = ft_atoi(av[1]);
	arg->time_die = ft_atoi(av[2]);
	arg->time_eat = ft_atoi(av[3]);
	arg->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		arg->must_eat_num = ft_atoi(av[5]);
		if (arg->must_eat_num <= 0)
			return (FAIL);
	}
	if (arg->philo_num <= 0 || arg->time_die <= 0 || arg->time_eat <= 0
			|| arg->time_sleep <= 0)
			return (FAIL);
	if (init_mutex(arg))
		return (FAIL);
	return (SUCCESS);
}

int	init_mutex(t_all_info *arg)
{
	int	i;

	arg->forks = malloc(arg->philo_num * sizeof(pthread_mutex_t));
	if (!(arg->forks))
		return (FAIL);
	while (i < arg->philo_num)
	{
		if (pthread_mutex_init(&(arg->forks[i]), NULL))
			return (FAIL);
		i++;
	}
	if (pthread_mutex_init(&(arg->mutex_for_print), NULL))
		return (FAIL);
	return (SUCCESS);
}

int	init_philo(t_all_info *arg, t_philo **philo)
{
	int		i;
	t_philo	*tmp;

	*philo = malloc(arg->philo_num * sizeof(t_philo));
	if (!(philo))
		return (FAIL);
	tmp = *philo;
	i = 0;
	while (i < arg->philo_num)
	{
		tmp[i].id = i;
		tmp[i].left_fork = i;
		tmp[i].right_fork = (i + 1) % arg->philo_num;
		tmp[i].eat_cnt = 0;
		tmp[i].last_eat_clock = 0;							//get_time()써야 할수도
		tmp[i].p_arg = arg;
	}
}

///////////////////////////////