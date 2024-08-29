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
