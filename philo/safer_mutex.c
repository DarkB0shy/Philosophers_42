/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safer_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:27 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:41:28 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int safe_mutex_lock(t_philosopher *philo, int flag)
{
    t_rules *rules;

    rules = philo->rules;
    if (flag == 0)
    {
        if (pthread_mutex_lock(&(rules->forks[philo->left_fork_id])))
            return (1);
    }
    if (flag == 1)
    {
        if (pthread_mutex_lock(&(rules->writing)))
            return (1);
    }
    if (flag == 2)
    {
        if (pthread_mutex_lock(&(rules->meal_check)))
            return (1);
    }
    if (flag == 3)
    {
        if (pthread_mutex_lock(&(rules->forks[philo->right_fork_id])))
            return (1);
    }
    return (0);
}

int safe_mutex_unlock(t_philosopher *philo, int flag)
{
    t_rules *rules;

    rules = philo->rules;
    if (flag == 0)
    {
        if (pthread_mutex_unlock(&(rules->forks[philo->left_fork_id])))
            return (1);
    }
    if (flag == 1)
    {
        if (pthread_mutex_unlock(&(rules->writing)))
            return (1);
    }
    if (flag == 2)
    {
        if (pthread_mutex_unlock(&(rules->meal_check)))
            return (1);
    }
    if (flag == 3)
    {
        if (pthread_mutex_unlock(&(rules->forks[philo->right_fork_id])))
            return (1);
    }
    return (0);
}