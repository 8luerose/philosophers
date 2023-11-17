/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taehkwon <taehkwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 21:00:16 by taehkwon          #+#    #+#             */
/*   Updated: 2023/11/17 19:51:56 by taehkwon         ###   ########.fr       */
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

# define	SUCCESS	0
# define	FAIL	1

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
	int				*forks_init_status;		// 뮤텍스 초기화 상태 추적을 위한 배열
	pthread_mutex_t *forks;
	pthread_mutex_t mutex_for_print;
} t_all_info;

typedef struct s_philo
{
	int			id;
	int			left_fork;
	int			right_fork;
	int			eat_cnt;
	long long	last_eat_time;
	t_all_info	*p_arg;
	pthread_t	thread_id;
} t_philo;

int	ft_atoi(const char *str);

int			print_error(char *msg);
long long	get_time(void);
void		go_until_to_time(long long arg_timeout, t_all_info *arg);

int 		init_arg(t_all_info *arg, int ac, char **av);
int			init_mutex(t_all_info *arg);
int			init_philo(t_all_info *arg, t_philo **philo);

int 		main_thread_start(t_all_info *arg, t_philo *philo);
int 		wait_thread_exit(t_all_info *arg, t_philo **philo);
int			destroy_mutex(t_all_info *arg);
void 		*make_thread(void *pthread_create_info_philo_i);
void		philo_pick_up_fork(t_all_info *arg, t_philo *philo);
int			philo_must_eat_check(t_all_info *arg, t_philo *philo);
void 		message_print(t_all_info *arg, int philo_id, char *msg);
void		always_on_monitoring(t_all_info *arg, t_philo *philo);
int			must_eat_check(t_all_info *arg);
int			time_to_die_check(t_all_info *arg, t_philo *philo);

#endif