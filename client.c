/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehaanpaa <ehaanpaa@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:11:32 by ehaanpaa          #+#    #+#             */
/*   Updated: 2025/02/23 18:37:43 by ehaanpaa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//take string and convert it to binary
//send binary to server
static void	send_signal(char *s, int served_pid)
{
	int	bits;
	int	c;
	int	i;

	i = 0;
	while (1)
	{
		c = s[i];
		bits = 0;
		while (bits < 8)
		{
			if (((unsigned char)(c >> (7 - bits)) & 1) == 0)
				kill(served_pid, SIGUSR1);
			else if (((unsigned char)(c >> (7 - bits)) & 1) == 1)
				kill(served_pid, SIGUSR2);
			usleep(250);
			bits++;
		}
		bits = 0;
		if (s[i] == '\0')
			break ;
		i++;
	}
}

int	main(int argv, char *argc[])
{
	int	server_pid;

	server_pid = 0;
	if (argv == 3)
	{
		server_pid = ft_atoi(argc[1]);
		if (!server_pid)
		{
			ft_printf("Wrong <PID>");
			return (0);
		}
		send_signal(argc[2], server_pid);
	}
	else
	{
		ft_printf("Incorrect argument amount.\n");
		ft_printf("Enter arguments: ./client <PID> <STRING>.\n");
	}
	return (0);
}
