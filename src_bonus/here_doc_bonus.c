/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 09:29:05 by isainz-r          #+#    #+#             */
/*   Updated: 2024/07/05 09:29:07 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_get_eof(char **argv)
{
	char	*eof;

	eof = (char *)malloc(ft_strlen(argv[2] + 2));
	ft_strlcpy(eof, argv[2], ft_strlen(argv[2]) + 1);
	eof[ft_strlen(argv[2])] = '\n';
	eof[ft_strlen(argv[2]) + 1] = '\0';
	return (eof);
}

int	ft_write_temp(int *fd, char **argv, char *buffer)
{
	int	n_bytes;

	while (1)
	{
		write(1, ">", 1);
		n_bytes = read(STDIN_FILENO, buffer, 1024);
		if (n_bytes == 0)
			break ;
		else if (n_bytes < 0)
		{
			close(fd[0]);
			close(fd[1]);
			return (1);
		}
		buffer[n_bytes] = '\0';
		if (!ft_strncmp(ft_get_eof(argv), buffer, n_bytes))
			break ;
		write(fd[0], buffer, n_bytes);
	}
	return (0);
}

int	ft_here_doc(int argc, char **argv, char **env)
{
	int		fd[2];
	char	buffer[1024];
	int		status;

	if (argc != 6)
		return (ft_error(1));
	fd[0] = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd[0] < 0)
		return (ft_error(2));
	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd[1] < 0)
	{
		close(fd[0]);
		return (ft_error(2));
	}
	if (ft_write_temp(fd, argv, buffer) == 1)
		return (1);
	close (fd[0]);
	fd[0] = open("temp.txt", O_RDONLY, 0777);
	status = ft_forks(fd, argc - 1, argv + 1, env);
	close(fd[0]);
	close(fd[1]);
	unlink("temp.txt");
	return (status);
}

/*
./pipex here\_doc LIMITADOR comando comando1 archivo

comando << LIMITADOR | comando1 >> archivo
*/