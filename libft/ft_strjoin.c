/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 18:07:59 by isainz-r          #+#    #+#             */
/*   Updated: 2024/05/26 11:55:36 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*resultado;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1[0] == '\0')
		resultado = ft_calloc(ft_strlen(s2) + 1, 1);
	else if (s2[0] == '\0')
		resultado = ft_calloc(ft_strlen(s1) + 1, 1);
	else if (s1[0] == '\0' && s2[0] == '\0')
		resultado = ft_calloc(1, sizeof(char));
	else
		resultado = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!resultado)
		return (NULL);
	while (i < ft_strlen(s1) && s1[0] != '\0')
		resultado[j++] = s1[i++];
	i = 0;
	while (i < ft_strlen(s2) && s2[0] != '\0')
		resultado[j++] = s2[i++];
	return (resultado);
}
/*
int   main(void)
{
    printf("%s\n", ft_strjoin("", ""));
}*/
