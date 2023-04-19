/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:42:14 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/18 18:42:15 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void write_std_error(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    write(2, "Error: ", 7);
    write(2, str, i);
    write(2, "\n", 1);
}

void print_std_error(int flag)
{
    if (flag == 1)
        write_std_error("wrong N of arguments");
    else if (flag == 2)
        write_std_error("at least one wrong argument");
	else if (flag == 3)
		write_std_error("error while closing a semaphore");
    exit(1);
}