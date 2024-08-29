/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isainz-r <isainz-r@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:46:33 by isainz-r          #+#    #+#             */
/*   Updated: 2024/02/02 17:47:33 by isainz-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//PRIMERA VERSIÓN//
/*typedef struct s_list
{
    void *content;
    struct s_list *next;
} t_list;
int ft_lstsize(t_list *lst)
{
	int len;

	len = 0;	
	while (lst[len] != NULL)
		len++;
	return (len);
}
int main()
{
	t_list *element1 = malloc(sizeof(t_list));
    t_list *element2 = malloc(sizeof(t_list));

    element1->content = "Elemento 1";
    element2->content = "Elemento 2";
    element1->next = NULL;
    element2->next = NULL;
    t_list *lista = element1;
    ft_lstsize(&lista);
    t_list *current = lista;
    while (current != NULL)
    {
        printf("Contenido: %s\n", (char *)current->content);
        current = current->next;
    }
    free(element1);
    free(element2);
}*/

//SEGUNDA VERSIÓN//
/* typedef struct t_stack
 {
 	int a;
	int b;
	int c;
	struct t_stack *next;
}t_stack;*/
	/*
	 * while(lst != NULL)
	 * {
	 *	lst -> a = 10;
	 *	lst -> b = 11;
	 *	lst -> c = 12
	 *	lst = lst -> next
	 *	lst -> a = 3300;
	 *	lst -> b = 120;
	 *	lst -> c = 140;
	 * }
	 *
	 * */
/*int main()
 {
 	t_stack *lst = malloc(sizeof(t_stack));
	t_stack *temp = lst;
	while(temp != NULL)
	{
	temp->a = 1;
	temp->b = 2;
	temp->c = 3;
	temp = temp->next;
	}
	printf("%d %d %d", lst->a, lst->b, lst->c);
	 return (0);
 }
 */
//TERCERA VERSIÓN//
int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
