/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:41:19 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/10 18:58:45 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleepnthink(t_philo *philo)
{
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is sleeping\n", ft_time(philo->start, philo->curr),
		philo->id);
	ft_wait(philo->var->t_sleep);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is thinking\n", ft_time(philo->start, philo->curr),
		philo->id);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_valid(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] == '+')
				j++;
			while (av[i][j] && ft_isdigit(av[i][j]))
			{
				j++;
			}
			if (av[i][j] != 0)
				return (1);
		}
		i++;
	}
	return (0);
}

void	destroy_mutex(t_var **var, t_philo **philo)
{
	int	i;

	i = 0;
	while (i < (*var)->n_philo)
	{
		pthread_mutex_destroy(&(*philo)->fork[i++]);
	}
	pthread_mutex_destroy(&(*var)->eat);
	pthread_mutex_destroy(&(*var)->death_check);
	i = 0;
}
