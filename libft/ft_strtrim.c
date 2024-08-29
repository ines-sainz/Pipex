/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:33:50 by isainz-r          #+#    #+#             */
/*   Updated: 2024/01/30 20:50:41 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		finish;
	char	*new_string;

	i = 0;
	finish = 0;
	while (ft_strchr(set, s1[i]) != 0 && s1[i] != '\0')
		i++;
	start = i;
	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != 0 && i != 0)
		i--;
	new_string = ft_substr(s1, start, i - start + 1);
	return (new_string);
}
