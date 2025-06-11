/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:47:17 by isainz-r          #+#    #+#             */
/*   Updated: 2024/07/04 11:47:19 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/**
 * @brief Searches for executable command in PATH directories.
 * 
 * Iterates through PATH directories to find executable command,
 * checking access permissions and returning full path if found.
 * 
 * @param path_list Array of PATH directories to search
 * @param path_mid Temporary string for path construction
 * @param kid Command name to search for
 * @return Full path to executable command or NULL if not found
 */
char	*ft_check_command(char **path_list, char *path_mid, char *kid)
{
	int		j;
	int		i;
	char	*path_fin;

	j = -1;
	while (path_list[++j])
	{
		path_mid = ft_strjoin(path_list[j], "/");
		path_fin = ft_strjoin(path_mid, kid);
		free(path_mid);
		if (access(path_fin, X_OK) == 0)
		{
			i = 0;
			while (path_list[i])
			{
				free(path_list[i]);
				i++;
			}
			free(path_list);
			return (path_fin);
		}
		free(path_fin);
	}
	return (NULL);
}

/**
 * @brief Resolves command path from environment PATH variable.
 * 
 * Checks if command contains path separator or searches through PATH
 * environment variable to find executable command location.
 * 
 * @param kid Command and arguments array (command is at index 0)
 * @param env Environment variables array
 * @param path_mid Temporary string for path construction
 * @return Full path to command or NULL if not found
 */
char	*ft_get_path_command(char **kid, char **env, char *path_mid)
{
	int		i;
	char	*path;
	char	**path_list;

	if (ft_strchr(kid[0], '/'))
		if (access(kid[0], X_OK) == 0)
			return (ft_strdup(kid[0]));
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp("PATH=", env[i], 5))
		{
			path_list = ft_split(env[i], ':');
			path = ft_check_command(path_list, path_mid, kid[0]);
			if (path)
				return (path);
		}
	}
	i = 0;
	while (path_list[i])
	{
		free(path_list[i]);
		i++;
	}
	return (free(path_list), NULL);
}
