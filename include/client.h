/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:27:16 by kscordel          #+#    #+#             */
/*   Updated: 2023/03/21 13:28:37 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <signal.h>

void	ft_send(int pid, char *str);
void	ft_one_by_one(int pid, char c, int index);
void	ft_bitgo(int pid, char c, int i);
void	reponse(int num, siginfo_t *info, void *x);

#endif
