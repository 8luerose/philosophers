/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:21:32 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/16 17:25:53 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		print_error(char *msg)
{
    printf("ERROR: %s\n", msg);
    return (FAIL);
}

long long	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((long long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

void	go_until_to_time(long long arg_timeout, t_all_info *arg)
{
	long long	start_time;
	long long	current_time;

	start_time = get_time();
	while (!(arg->finish_flag))
	{
		current_time = get_time();
		if ((current_time - start_time) >= arg_timeout)
			break ;
		usleep(10);
	}
};