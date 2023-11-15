/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:21:32 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/15 23:00:11 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_error(char *msg)
{
    printf("ERROR: %s\n", msg);
    return (FAIL);
}

long get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	pass_time(long arg_time_eat, t_all_info *arg)
{
	long start;
	long now;

	start = get_time();
	while (!(arg->finish_flag))
	{
		now = get_time();
		if ((now - start) >= arg_time_eat)
			break ;
		usleep(10);
	}
};