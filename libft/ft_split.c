/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:20:22 by isainz-r          #+#    #+#             */
/*   Updated: 2024/01/30 21:00:17 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char	**ft_free_strings(char **new_string, int j)
{
	while (j >= 0)
	{
		free(new_string[j]);
		j--;
	}
	free(new_string);
	return (0);
}

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != '\0')
			i++;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j + 1);
}

char	**ft_split(char const *s, char c)
{
	int		cont[3];
	char	**string;

	cont[0] = 0;
	cont[1] = 0;
	string = ft_calloc(ft_count_words(s, c), sizeof(char *));
	if (string == NULL)
		return (0);
	while (s[cont[0]] != '\0')
	{
		if (s[cont[0]] == c)
			cont[0]++;
		cont[2] = cont[0];
		while (s[cont[0]] != c && s[cont[0]])
		{
			cont[0]++;
			if (s[cont[0]] == c || s[cont[0]] == '\0')
			{
				string[cont[1]] = ft_substr(s, cont[2], cont[0] - cont[2]);
				if (string[cont[1]++] == NULL)
					return (ft_free_strings(string, cont[1]));
			}
		}
	}
	return (string);
}

/*int main(void)
{
	char	**str;
	int		i;

	i = 0;
	str = ft_split("holchochol", 'c');
	while (str[i])
	{
	    printf("%s\n", str[i]);
		i++;
	}
}
*/
