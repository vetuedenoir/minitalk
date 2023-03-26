/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kscordel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:29:11 by kscordel          #+#    #+#             */
/*   Updated: 2023/03/21 16:13:52 by kscordel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/serveur.h"

void	ft_reload(t_ping (*pidx)[64], char *c, int *i)
{
	int	x;

	if (pidx[1]->pid == 0)
	{
		pidx[0]->pid = 0;
		pidx[0]->signal = 0;
		*c = 0xFF;
		*i = 0;
	}
	else 
	{
	//	ft_printf("\npidx1 = %d et npdx[0] = %d\n", pidx[1]->pid, pidx[0]->pid);
		x = 0;
		while (pidx[x++]->pid != 0)
			*pidx[x - 1] = *pidx[x];
		if (pidx[0]->signal == SIGUSR1)
			*c = *c | (1 >> 1);
		*i = 1;
		kill(pidx[0]->pid, SIGUSR1);
	}
}

void	ft_check_id(t_ping (*pidx)[64], int sipid, int signal)
{
	int	j;

	j = 0;;
	//ft_printf("pidx[0]pid = %d et sipid = %d pidx[1] = %d\n", pidx[0]->pid, sipid, pidx[1]->pid);
	if (pidx[0]->pid == 0)
	{
		pidx[0]->pid = sipid;
		pidx[0]->signal = signal;
		
		//pidx[1]->pid = 0;
		return ;
	}
	if (pidx[0]->pid == sipid)
	{
		//if (pidx[1]->signal == 0)
		//	pidx[1]->pid = 0;
		return ;
	}
	else
	{
		ft_printf("pidx[0] = %d et sipid = %d\n", pidx[0]->pid, sipid);
		while (pidx[j]->pid != 0)
			j++;
		pidx[j]->pid = sipid;
		pidx[j]->signal = signal;
	//	ft_printf("avant d envoyer sigusr2 sipid = %d\n", sipid);
		kill(sipid, SIGUSR2);
	}
}

char	*ft_resize(char *str, int *size, char c, int *i)
{
	char	*buf;
	
		*size = *size + 10;
		buf = malloc(sizeof(char) * (*size + 1));
		ft_memcpy(buf, str, *i);
		free(str);
		if (str == NULL)
			ft_printf("va niquer ta mere\n");
		buf[*i] = c;
		*i = *i +1;
		return (buf);
}

int	ft_insert(char c)
{
	static char	*str;
	static int	i;
	char		*buf;
	static int	size = 10;

	write(1, &c, 1);
	if (str == NULL)
		str = malloc(sizeof(char) * (size + 1));
	if (i <= size)
		str[i++] = c;
	else
		str = ft_resize(str, &size, c, &i);
	//ft_putstr_fd(str, 1);
	if (c == '\n')
	{
		str[i] = '\0';
		write(1, str, i);
		i = 0;
		size = 10;
		//free(str);
		return (1);
	}
	else if (c == 0)
	{
		i = 0;
		size = 10;
		write(1, str, i - 1);
		//free(str);
		return (0);
	}
	else
		return (1);
}

void	ft_reception(int num, siginfo_t *info, void *p)
{
	static t_ping	pidx[64] = {0};
	static char	c = 0xFF;
	static int	i;
	
	(void) p;
	ft_check_id(&pidx, info->si_pid, num);
	if (pidx[0].pid != info->si_pid)
		return ;
	/*if (num == SIGUSR1)
	{
		c ^= 0xFF;
	}
	c = c >> 1;*/
	if (num == SIGUSR2)
		c ^= 0x80 >> i;
	else if (num == SIGUSR1)
		c |= 0x80 >> i;
	//ft_printf("i = %d\n", i);
	i++;
	//ft_printf("adr de i = %p et adr de pidx[1] = %p et %p\n", &i, &pidx[1].pid, &pidx[1]);
	if (i == 8)
	{
		//ft_printf("le caractere %c \n",c);
		c = ft_insert(c);
		if (c == 0)
			ft_reload(&pidx, &c, &i);
		else
		{
			c = 0xFF;
			i = 0;
		}
	}
	kill(info->si_pid, SIGUSR1);
	return ;
}

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = ft_reception;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("%d\n",getpid());
	while (1)
	{}
	return (1);
}
