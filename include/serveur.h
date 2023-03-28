/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:24:00 by kscordel          #+#    #+#             */
/*   Updated: 2023/03/28 16:02:28 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

void	ft_erreur(int pid);
void	ft_check_id(int *pidx, int sipid);
char	*ft_resize(char **str, int *size, char c, int *i);
int		ft_putsline(char *str, int *i, int *size, char c);
int		ft_insert(char c, int pid);
void	ft_reception(int num, siginfo_t *info, void *p);

#endif
