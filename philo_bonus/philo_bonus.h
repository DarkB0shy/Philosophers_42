/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:42:22 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:42:23 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_philo
{
	int				id;
	int				state;
	int				eat_times;
	struct timeval	start_eat;
	struct timeval	start_sleep;
}				t_philo;

typedef struct s_rules
{
	int				num_philo;
	int				meal_cnt;
	char			*forks;
	char			*post;
	pid_t			parent;
	sem_t			*sem_f;
	sem_t			*sem_p;
	t_philo 		philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	struct timeval	start;
}				t_rules;

int	write_std_error(char *str);
void	print_std_error(int flag);

unsigned long	gap_time(struct timeval v);

int	sem_print_action(t_rules *rules, char *str);
void	close_semaphores(t_rules *rules);
int	check_if_dead(t_rules *rules);
int	sem_take_fork(t_rules *rules);
int	sem_put_back_forks(t_rules *rules);

void	start_child_process(t_rules *rules);
void	start_parent_process(t_rules *rules);

int	init_philos(t_rules *rules, char **argv);
int	thinking(t_rules *rules);

#endif