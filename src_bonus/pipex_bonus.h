/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:57:50 by isainz-r          #+#    #+#             */
/*   Updated: 2024/06/28 19:07:26 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/wait.h>

int		ft_forks(int *fd, int argc, char **argv, char **env);
void	ft_free_kids(char **kid);
char	*ft_get_path_command(char **kid, char **env, char *path_mid);
int		ft_here_doc(int argc, char **argv, char **env);
int		ft_error(int i);

#endif