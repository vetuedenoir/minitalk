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
	{
		write(1, str, *i - 1);
		write(1, "\n", 1);
	}
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
	static int	pidx;
	static char	c = 0xFF;

	(void) p;
	ft_check_id(&pidx, info->si_pid);
	if (pidx != info->si_pid)
		return ;
	if (num == SIGUSR2)
		c ^= 0x80 >> i;
	else if (num == SIGUSR1)
		c |= 0x80 >> i;
	i++;
	if (i == 8)
	{
		c = ft_insert(c);
		if (c == 0)
			pidx = 0;
		c = 0xFF;
		i = 0;
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
	ft_printf("%d\n", getpid());
	while (1)
	{
	}
	return (1);
}
