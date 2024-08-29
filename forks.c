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
