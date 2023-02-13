/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharrass <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 11:19:51 by aharrass          #+#    #+#             */
/*   Updated: 2023/02/13 15:20:58 by aharrass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <sys/stat.h> 

typedef struct s_philo
{
	int				id;
	int				eat_n;
	struct s_var	*var;
	struct timeval	last_meal_time;
	struct timeval	curr;
}					t_philo;

typedef struct s_var
{
	struct timeval	start;
	int				n_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				is_alive;
	int				av_philo;
	sem_t			*fork_pile;
	int				*ph_id;
	sem_t			*death_check;
	
}					t_var;

int					ft_atoi(const char *str);
int					is_valid(char **av);
void				ft_wait(int wait_time);
int					ft_time(struct timeval start, struct timeval curr);
void				ft_eat(t_philo *philo);
void				sleepnthink(t_philo *philo);
#endif
