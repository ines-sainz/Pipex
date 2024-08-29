/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:27:01 by isainz-r          #+#    #+#             */
/*   Updated: 2024/06/28 19:08:16 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(int i)
{
	if (i == 1)
		write(2, "Error. Not enough arguments.\n", 29);
	if (i == 2)
		write(2, "Error. Invalid files.\n", 23);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int		fd[2];
	char	**kid_1;
	char	**kid_2;
	int		status;

	if (argc != 5)
		return (ft_error(1));
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] < 0)
		return (ft_error(2));
	fd[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd[1] < 0)
	{
		close(fd[0]);
		return (ft_error(2));
	}
	kid_1 = ft_split(argv[2], ' ');
	kid_2 = ft_split(argv[3], ' ');
	status = ft_forks(fd, kid_1, kid_2, env);
	close(fd[0]);
	close(fd[1]);
	ft_free_kids(kid_1);
	ft_free_kids(kid_2);
	return (status);
}
