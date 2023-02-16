/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_bonus_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 12:58:50 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/16 18:18:56 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_bonus.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->var->fork_pile);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d has taken a fork\n", ft_time(philo->var->start, philo->curr),
		philo->id);
	sem_wait(philo->var->fork_pile);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d has taken a fork\n", ft_time(philo->var->start, philo->curr),
		philo->id);
	//usleep(500);
	sem_wait(philo->var->death_check);
	gettimeofday(&(philo->last_meal_time), NULL);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is eating\n", ft_time(philo->var->start, philo->curr),
		philo->id);
	sem_post(philo->var->death_check);
	ft_wait(philo->var->t_eat);
	if (!philo->var->is_alive)
		return ;
	sem_post(philo->var->fork_pile);
	sem_post(philo->var->fork_pile);
}

void	sleepnthink(t_philo *philo)
{
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is sleeping\n", ft_time(philo->var->start, philo->curr),
		philo->id);
	ft_wait(philo->var->t_sleep);
	gettimeofday(&(philo->curr), NULL);
	printf("%5d %d is thinking\n", ft_time(philo->var->start, philo->curr),
		philo->id);
}

void	ft_death(t_var *var)
{
	int	i;
	int	status;
	int	s;

	i = 0;
	waitpid(-1, &status, 0);
	if (WIFEXITED(status))
	{
		s = WEXITSTATUS(status);
		if (s == 0)
		{
			while (i < var->n_philo)
				waitpid(var->ph_id[i++], &status, 0);
			usleep(500);
			i = 0;
		}
		if (s != 0)
			(gettimeofday(&var->tf, NULL), printf("%5d %d died\n",
					ft_time(var->start, var->tf), s));
		while (i < var->n_philo)
			kill(var->ph_id[i++], SIGKILL);
		exit(0);
	}
}
