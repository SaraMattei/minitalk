/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smattei <smattei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:03:33 by smattei           #+#    #+#             */
/*   Updated: 2026/01/09 16:20:47 by smattei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "./libft/libft.h"
#include <signal.h>
#include <sys/types.h>

void	handle_signal(int sign)
{
	static int				bit_count;
	static unsigned char	i;

	if (sign == SIGUSR1)
		i |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &i, 1);
		bit_count = 0;
		i = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	(void)argv;
	if (argc != 1)
	{
		write(1, "Error: No arguments needed.\n", 28);
		return (1);
	}
	write(1, "Server PID: ", 12);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sa.sa_handler = handle_signal;
	sigemptyset (&sa.sa_mask);
	sa.sa_flags = 0;
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		;
	return (0);
}
