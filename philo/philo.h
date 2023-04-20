/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:16 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/20 14:56:28 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

// da rimuovere

# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"

struct	s_rules;

typedef struct s_philosopher
{
	struct s_rules		*rules;
	int					id;
	int					x_ate;
	int					left_fork_id;
	int					right_fork_id;
	long long			t_last_meal;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_death;
	int					time_eat;
	int					time_sleep;
	int					nb_eat;
	long long			first_timestamp;
	int					finished;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		forks[250];
	pthread_mutex_t		writing;
	t_philosopher		philosophers[250];
}						t_rules;

void		smart_sleep(long long time, t_rules *rules);
int			check_if_lunch_is_over(t_philosopher *philo);
long long	timestamp(void);
long long	time_diff(long long past, long long pres);

int			print_standard_error(char *str);
int			print_error(int i);

int			init_philo(t_rules *rules, char **argv);

int			safe_mutex_unlock(t_philosopher *philo, int flag);
int			safe_mutex_lock(t_philosopher *philo, int flag);

int			print_action(t_philosopher *philo, char *str);
int			start_philosophing(t_rules *rules);
void		stop_philosophing(t_rules *rules);

#endif