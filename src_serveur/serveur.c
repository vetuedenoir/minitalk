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
	int		x;
	char	b;

	//ft_printf("pidx[0] = %d et pidx[1] = %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", pidx[0]->pid, pidx[1]->pid);
	if (pidx[1]->pid == 0)
	{
		pidx[0]->pid = 0;
		pidx[0]->signal = 0;
		*c = 0xFF;
		*i = 0;
	}
	else 
	{
	//	ft_ls("\npidx1 = %d et npdx[0] = %d\n", pidx[1]->pid, pidx[0]->pid);
		x = 0;
		b = 0xFF;
		while (pidx[x++]->pid != 0)
		{
			pidx[x - 1]->pid = pidx[x]->pid;
			pidx[x - 1]->signal = pidx[x]->signal;
		}	
		if (pidx[0]->signal == SIGUSR2)
			b ^= 0x80 >> *i;
		else if (pidx[0]->signal == SIGUSR1)
			b |= 0x80 >> *i;
		*i = 1;
		*c = b;
		kill(pidx[0]->pid, SIGUSR1);
	}
}

void	ft_check_id(t_ping (*pidx)[64], int sipid, int signal)
{
	int	j;

	j = 0;
	//ft_printf("pidx[0]pid = %d , pidx[1] = %d et pidx[2] = %d\n", pidx[0]->pid, pidx[1]->pid, pidx[2]->pid);
	//pidx[2]->pid = 400000; 
	if (pidx[0]->pid == 0)
	{
		pidx[0]->pid = sipid;
		pidx[0]->signal = signal;
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
		while (pidx[j]->pid != 0)
			j++;
		pidx[j]->pid = sipid;
		pidx[j]->signal = signal;
		//ft_printf("pidx[0] = %d et sipid = %d et pidx[1] = %d\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", pidx[0]->pid, sipid, pidx[1]->pid);
		//	ft_printf("avant d envoyer sigusr2 sipid = %d\n", sipid);
		kill(sipid, SIGUSR2);
	}
}

char	*ft_resize(char **str, int *size, char c, int *i)
{
	char	*buf;
	
		*size = *size + 100;
		buf = malloc(sizeof(char) * (*size + 1));
		ft_memcpy(buf, *str, *i);
		free(*str);
		*str = NULL;
		buf[*i] = c;
		*i = *i + 1;
		return (buf);
}

int	ft_putsline(char *str, int	*i, int	*size, char c)
{
	if (c == '\n')
	{
		str[*i] = '\0';
		write(1, str, *i);
	}
	if (c == '\0')
		write(1, str, *i - 1);
	*size = 100;
	*i = 0;
	if (c == '\n')
		return (1);
	else
		return (0);	
}

int	ft_insert(char c)
{
	static char	*str;
	static int	i;
	static int	size = 100;

	if (str == NULL)
		str = malloc(sizeof(char) * (size + 1));
	if (i < size)
		str[i++] = c;
	else
		str = ft_resize(&str, &size, c, &i);
	if (c == '\n' || c == '\0')
	{
		c = ft_putsline(str, &i, &size, c);
		free(str);
		str = NULL;
		return ((int)c);
	}
	else
		return (1);
}

void	ft_reception(int num, siginfo_t *info, void *p)
{
	static int	i;
	static t_ping	pidx[64] = {0};
	static char	c = 0xFF;
	
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
