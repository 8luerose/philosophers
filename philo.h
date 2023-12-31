/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:00:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/25 19:58:17 by taehkwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>

# define SUCCESS 0
# define FAIL 1

typedef struct s_all_info
{
	int				philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_cnt;
	long long		init_time;
	int				finish_flag;
	int				total_eat;
	int				*forks_init_status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_for_print;
	pthread_mutex_t	mutex_for_finish;
	pthread_mutex_t	mutex_for_total_eat;
}	t_all_info;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_cnt;
	long long		last_eat_time;
	t_all_info		*p_arg;
	pthread_t		thread_id;
	pthread_mutex_t	mutex_for_eat_time;
}	t_philo;

//utils.c
int			ft_atoi(const char *str);
int			print_error(char *msg);
long long	get_time(void);
void		go_until_to_time(long long arg_timeout, t_all_info *arg);
//init.c
int			init_arg(t_all_info *arg, int ac, char **av);
int			init_mutex(t_all_info *arg);
int			init_philo(t_all_info *arg, t_philo **philo);
//philo.c
int			main_thread_start(t_all_info *arg, t_philo *philo);
void		*mk_thread(void *pthread_create_info_philo_idx);
void		philo_pick_up_fork(t_all_info *arg, t_philo *philo_idx);
int			philo_must_eat_check(t_all_info *arg, t_philo *philo);
void		message_print(t_all_info *arg, int philo_id, char *msg);
//monitoring.c
void		always_on_monitoring(t_all_info *arg, t_philo *philo);
int			must_eat_check(t_all_info *arg);
int			time_to_die_check(t_all_info *arg, t_philo *philo, int i);
//cleaning.c
int			end_waiting_thread(t_all_info *arg, t_philo **philo);
int			destroy_mutex(t_all_info *arg, t_philo *philo);
void		free_all(t_all_info *arg, t_philo **philo);

#endif