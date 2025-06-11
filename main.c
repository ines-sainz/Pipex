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

/**
 * @brief Prints error messages to stderr based on error type.
 * 
 * Outputs specific error messages for different error conditions and
 * returns error status code.
 * 
 * @param i Error type identifier (1 for arguments, 2 for files)
 * @return Always returns 1 to indicate error status
 */
int	ft_error(int i)
{
	if (i == 1)
		write(2, "Error. Not enough arguments.\n", 29);
	if (i == 2)
		write(2, "Error. Invalid files.\n", 23);
	return (1);
}

/**
 * @brief Main function that handles pipeline execution with file I/O.
 * 
 * Processes command line arguments to execute pipeline commands, handling
 * both regular file operations and here document functionality.
 * 
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @param env Environment variables array
 * @return Exit status of executed pipeline or error code
 */
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
