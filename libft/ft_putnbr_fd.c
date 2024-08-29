/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 15:17:29 by isainz-r          #+#    #+#             */
/*   Updated: 2024/05/30 11:01:50 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

void	ft_putnbr_fd(int n, int fd)
{
	int	div_n;
	int	to_write;

	if (n == INT_MIN)
		write(fd, "-2147483648", 11);
	if (n > INT_MIN && n <= INT_MAX)
	{
		if (n < 0)
		{
			n = -n;
			write(fd, "-", 1);
		}
		div_n = (n / 10);
		if (n >= 10)
			ft_putnbr_fd(div_n, fd);
		to_write = ((n % 10) + '0');
		write(fd, &to_write, 1);
	}
}

/*int main(void)
{
	int	string;
	char	*file = "./test";
	int		fd;

	fd = open(file, 1);
	string = 12345;
	ft_putnbr_fd(string, fd);
	close(fd);
}*/
