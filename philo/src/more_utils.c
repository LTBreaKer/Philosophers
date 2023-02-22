/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 06:41:19 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/22 15:03:23 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	sleepnthink(t_philo *philo)
{
	gettimeofday(&(philo->curr), NULL);
	pthread_mutex_lock(&philo->var->print_l);
	printf("%5d %d is sleeping\n", ft_time(philo->start, philo->curr),
		philo->id);
	pthread_mutex_unlock(&philo->var->print_l);
	ft_wait(philo->var->t_sleep);
	gettimeofday(&(philo->curr), NULL);
	pthread_mutex_lock(&philo->var->print_l);
	printf("%5d %d is thinking\n", ft_time(philo->start, philo->curr),
		philo->id);
	pthread_mutex_unlock(&philo->var->print_l);
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
		usleep(500);
	}
	pthread_mutex_destroy(&(*var)->eat);
	pthread_mutex_destroy(&(*var)->death_check);
	i = 0;
}
