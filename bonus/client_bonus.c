/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:11:32 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/02/27 18:26:56 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

volatile sig_atomic_t	g_flag = 0;

void	server_signal(int signal)
{
	if (signal == SIGUSR1)
		g_flag = 1;
	if (signal == SIGUSR2)
		ft_printf("Message received\n");
}

static void	send_signal(char *s, int served_pid)
{
	int	bits;

	while (1)
	{
		bits = 7;
		while (bits >= 0)
		{
			if ((*s >> bits) & 1)
			{
				if (kill(served_pid, SIGUSR2) == -1)
					exit(ft_printf("Signal sent failed") || EXIT_FAILURE);
			}
			else
			{
				if ((kill(served_pid, SIGUSR1) == -1))
					exit(ft_printf("Signal sent failed") || EXIT_FAILURE);
			}
			while (g_flag == 0)
				usleep(100);
			g_flag = 0;
			bits--;
		}
		if (*s++ == '\0')
			break ;
	}
}

int	main(int argc, char *argv[])
{
	int					server_pid;
	struct sigaction	sa;

	sa.sa_handler = &server_signal;
	if (sigemptyset(&sa.sa_mask) == -1)
		exit(EXIT_FAILURE);
	sa.sa_flags = 0;
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		exit(EXIT_FAILURE);
	server_pid = 0;
	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		if (!server_pid)
		{
			ft_printf("Wrong <PID>");
			return (0);
		}
		send_signal(argv[2], server_pid);
	}
	else
		ft_printf("Invalid. Enter arguments: ./client <PID> <STRING>.\n");
	return (0);
}
