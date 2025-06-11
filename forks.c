/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:55:16 by isainz-r          #+#    #+#             */
/*   Updated: 2024/06/28 19:09:23 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Frees a null-terminated array of strings and the array itself.
 * 
 * Iterates through each string in the array, frees them individually,
 * then frees the array pointer.
 * 
 * @param kid Null-terminated array of strings to be freed
 */
void	ft_free_kids(char **kid)
{
	int	i;

	i = 0;
	while (kid[i])
	{
		free(kid[i]);
		i++;
	}
	free(kid);
}

/**
 * @brief Executes second command in pipeline with proper I/O redirection.
 * 
 * Sets up input from pipe and output to file descriptor, then executes
 * the command and exits with appropriate status code.
 * 
 * @param fd File descriptor array for input/output files
 * @param int_array Pipe file descriptors for inter-process communication
 * @param kid_2 Command and arguments array for second command
 * @param env Environment variables array
 * @return Always exits with status 127 on failure
 */
int	ft_kid_2(int *fd, int *int_array, char **kid_2, char **env)
{
	char	*path_command;
	char	*path_mid;

	close(int_array[1]);
	dup2(int_array[0], 0);
	close(int_array[0]);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	path_mid = NULL;
	path_command = ft_get_path_command(kid_2, env, path_mid);
	if (path_command)
		execve(path_command, kid_2, env);
	ft_free_kids(kid_2);
	exit(127);
}

/**
 * @brief Executes first command in pipeline with input/output redirection.
 * 
 * Sets up input from file descriptor and output to pipe, then executes
 * the first command in the pipeline.
 * 
 * @param fd File descriptor array for input/output files
 * @param int_array Pipe file descriptors for inter-process communication
 * @param kid_1 Command and arguments array for first command
 * @param env Environment variables array
 */
void	ft_kid_1(int *fd, int *int_array, char **kid_1, char **env)
{
	char	*path_command;
	char	*path_mid;

	close(int_array[0]);
	dup2(fd[0], 0);
	close(fd[0]);
	close(fd[1]);
	dup2(int_array[1], 1);
	close(int_array[1]);
	path_mid = NULL;
	path_command = ft_get_path_command(kid_1, env, path_mid);
	if (path_command)
		execve(path_command, kid_1, env);
	ft_free_kids(kid_1);
}

/**
 * @brief Creates and manages a two-command pipeline with proper I/O handling.
 * 
 * Forks two child processes to execute commands in pipeline, managing
 * pipe communication and waiting for both processes to complete.
 * 
 * @param fd File descriptor array for input/output files
 * @param kid_1 Command and arguments array for first command
 * @param kid_2 Command and arguments array for second command
 * @param env Environment variables array
 * @return Exit status of the second command
 */
int	ft_forks(int *fd, char **kid_1, char **kid_2, char **env)
{
	int		int_array[2];
	pid_t	num_fork_1;
	pid_t	num_fork_2;
	int		status;

	pipe(int_array);
	num_fork_1 = fork();
	if (num_fork_1 == 0)
	{
		ft_free_kids(kid_2);
		ft_kid_1(fd, int_array, kid_1, env);
	}
	num_fork_2 = fork();
	if (num_fork_2 == 0)
	{
		ft_free_kids(kid_1);
		status = ft_kid_2(fd, int_array, kid_2, env);
	}
	close(int_array[0]);
	close(int_array[1]);
	waitpid(num_fork_1, &status, 0);
	waitpid(num_fork_2, &status, 0);
	return (WEXITSTATUS(status));
}
