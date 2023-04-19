/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:42:16 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:42:17 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	ft_atoi(char *str)
{
	long int	r;
	int			i;

	r = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (-1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (*str >= '0' && *str <= '9')
			r = r * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)r);
}

static void	init_sem(t_rules *rules)
{
	rules->forks = "/forks";
	rules->post = "/post";
	sem_unlink(rules->forks);
	sem_unlink(rules->post);
	rules->sem_f = sem_open(rules->forks, O_CREAT, 0666, rules->num_philo);
	rules->sem_p = sem_open(rules->post, O_CREAT, 0666, 1);
}

int init_philos(t_rules *rules, char **argv)
{
    rules->num_philo = ft_atoi(argv[1]);
    rules->time_to_die = ft_atoi(argv[2]);
    rules->time_to_eat = ft_atoi(argv[3]);
    rules->time_to_sleep = ft_atoi(argv[4]);
    rules->philo.eat_times = 0;
    if (argv[5])
    {
        rules->meal_cnt = ft_atoi(argv[5]);
        if (rules->meal_cnt <= 0)
            return (1);
    }
	if (rules->num_philo < 1 || rules->num_philo > 200 || rules->time_to_die < 60)
		return (1);
    if (rules->time_to_eat < 60 || rules->time_to_sleep < 60)
        return (1);
    init_sem(rules);
    return (0);
}