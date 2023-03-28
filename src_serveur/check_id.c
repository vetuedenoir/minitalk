/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:00:28 by kscordel          #+#    #+#             */
/*   Updated: 2023/03/28 16:01:30 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/serveur.h"

void	ft_check_id(int *pidx, int sipid)
{
	if (*pidx == sipid)
		return ;
	if (*pidx == 0)
		*pidx = sipid;
	else
		kill(sipid, SIGUSR2);
}
