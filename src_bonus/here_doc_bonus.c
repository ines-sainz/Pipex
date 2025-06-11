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

/**
 * @brief Creates end-of-file delimiter string for here document processing.
 * 
 * Allocates memory and copies the delimiter from argv[2], appending a
 * newline character for comparison purposes.
 * 
 * @param argv Command line arguments array containing the delimiter
 * @return Newly allocated string with delimiter and newline terminator
 */
char	*ft_get_eof(char **argv)
{
	char	*eof;

	eof = (char *)malloc(ft_strlen(argv[2] + 2));
	ft_strlcpy(eof, argv[2], ft_strlen(argv[2]) + 1);
	eof[ft_strlen(argv[2])] = '\n';
	eof[ft_strlen(argv[2]) + 1] = '\0';
	return (eof);
}

/**
 * @brief Reads user input and writes to temporary file until delimiter found.
 * 
 * Continuously prompts user for input, writing each line to temporary file
 * until the specified delimiter is encountered or EOF is reached.
 * 
 * @param fd File descriptor array for temporary and output files
 * @param argv Command line arguments containing the delimiter
 * @param buffer Buffer for reading user input
 * @return 0 on success, 1 on read error
 */
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

/**
 * @brief Implements here document functionality for pipeline processing.
 * 
 * Creates temporary file from user input using delimiter, then executes
 * pipeline commands with temporary file as input and specified output file.
 * 
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @param env Environment variables array
 * @return Exit status of pipeline execution or error code
 */
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
