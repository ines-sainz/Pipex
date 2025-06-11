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

#include "pipex_bonus.h"

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
 * @brief Executes the last command in a pipeline with proper I/O redirection.
 * 
 * Creates a child process to execute the final command, redirecting input
 * from pipe and output to specified file descriptor.
 * 
 * @param fd File descriptor array for input/output files
 * @param int_array Pipe file descriptors for inter-process communication
 * @param kid Command and arguments array to execute
 * @param env Environment variables array
 * @return Always returns 0
 */
int	ft_last_kid(int *fd, int *int_array, char **kid, char **env)
{
	char	*path_command;
	char	*path_mid;
	pid_t	num_fork;

	num_fork = fork();
	if (num_fork == 0)
	{
		close(int_array[1]);
		dup2(int_array[0], 0);
		close(int_array[0]);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		path_mid = NULL;
		path_command = ft_get_path_command(kid, env, path_mid);
		if (path_command)
			execve(path_command, kid, env);
		ft_free_kids(kid);
		exit (127);
	}
	close(int_array[0]);
	close(int_array[1]);
	ft_free_kids(kid);
	return (0);
}

/**
 * @brief Executes a middle command in a pipeline with pipe redirection.
 * 
 * Creates a new pipe and child process for intermediate pipeline commands,
 * handling input from previous pipe and output to new pipe.
 * 
 * @param int_array_1 Input pipe file descriptors from previous command
 * @param kid Command and arguments array to execute
 * @param env Environment variables array
 * @param fd File descriptor array for input/output files
 * @return New pipe file descriptors array for next command
 */
int	*ft_mid_kids(int *int_array_1, char **kid, char **env, int *fd)
{
	int		*int_array_2;
	pid_t	num_fork;
	char	*path_command;
	char	*path_mid;

	int_array_2 = malloc(2 * sizeof(int));
	pipe(int_array_2);
	num_fork = fork();
	if (num_fork == 0)
	{
		close(int_array_1[1]);
		dup2(int_array_1[0], 0);
		close(int_array_1[0]);
		close(fd[0]);
		close(fd[1]);
		close(int_array_2[0]);
		dup2(int_array_2[1], 1);
		close(int_array_2[1]);
		path_mid = NULL;
		path_command = ft_get_path_command(kid, env, path_mid);
		if (path_command)
			execve(path_command, kid, env);
		ft_free_kids(kid);
	}
	return (free(int_array_1), int_array_2);
}

/**
 * @brief Executes the first command in a pipeline with input redirection.
 * 
 * Creates a child process for the first command in pipeline, redirecting
 * input from file and output to pipe for next command.
 * 
 * @param fd File descriptor array for input/output files
 * @param int_array Pipe file descriptors for inter-process communication
 * @param kid Command and arguments array to execute
 * @param env Environment variables array
 */
void	ft_first_kid(int *fd, int *int_array, char **kid, char **env)
{
	char	*path_command;
	char	*path_mid;
	pid_t	num_fork;

	num_fork = fork();
	if (num_fork == 0)
	{
		close(int_array[0]);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		dup2(int_array[1], 1);
		close(int_array[1]);
		path_mid = NULL;
		path_command = ft_get_path_command(kid, env, path_mid);
		if (path_command)
			execve(path_command, kid, env);
		ft_free_kids(kid);
	}
}

/**
 * @brief Creates and manages a pipeline of commands with proper I/O handling.
 * 
 * Orchestrates the execution of multiple commands in a pipeline, creating
 * child processes and managing pipes between them.
 * 
 * @param fd File descriptor array for input/output files
 * @param argc Number of command line arguments
 * @param argv Command line arguments array
 * @param env Environment variables array
 * @return Exit status of the last executed command
 */
int	ft_forks(int *fd, int argc, char **argv, char **env)
{
	int		*int_array;
	char	**kid;
	int		status;
	int		i;

	int_array = malloc(2 * sizeof(int));
	pipe(int_array);
	kid = ft_split(argv[2], ' ');
	ft_first_kid(fd, int_array, kid, env);
	i = 3;
	while (i <= argc - 3)
	{
		ft_free_kids(kid);
		kid = ft_split(argv[i], ' ');
		int_array = ft_mid_kids(int_array, kid, env, fd);
		i++;
	}
	ft_free_kids(kid);
	kid = ft_split(argv[i], ' ');
	status = ft_last_kid(fd, int_array, kid, env);
	while (waitpid(-1, &status, 0) != -1)
		continue ;
	return (free(int_array), WEXITSTATUS(status));
}
