/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcarassi <dcarassi@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:04 by dcarassi          #+#    #+#             */
/*   Updated: 2023/04/20 12:03:19 by dcarassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_standard_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, "Error: ", 7);
	write(2, str, i);
	write(2, "\n", 1);
	return (1);
}

int	print_error(int i)
{
	if (i == 1)
		return (print_standard_error("wrong input"));
	if (i == 2)
		return (print_standard_error("error while creating a mutex"));
	return (1);
}
