/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:36:40 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/13 16:08:44 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned long long	j;

	i = 0;
	s = 1;
	j = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		s *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		j = j * 10 + str[i++] - '0';
		if (j > 9223372036854775807 && s == 1)
			return (-1);
		if (j > 9223372036854775807 && s == -1)
			return (0);
	}
	return (j * s);
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

int	ft_time(struct timeval start, struct timeval curr)
{
	int	sum;

	sum = (((curr.tv_sec * 1000) + (curr.tv_usec / 1000)) - ((start.tv_sec
					* 1000) + (start.tv_usec / 1000)));
	return (sum);
}

void	ft_wait(int wait_time)
{
	struct timeval	t0;
	struct timeval	t1;

	gettimeofday(&t0, NULL);
	gettimeofday(&t1, NULL);
	while (ft_time(t0, t1) < wait_time)
	{
		usleep(400);
		gettimeofday(&t1, NULL);
	}
}
