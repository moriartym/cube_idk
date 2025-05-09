/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:41:35 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 16:58:41 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (!(*lst))
	{
		*lst = new;
		(*lst)->next = 0;
		return ;
	}
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
	temp = new;
}

/*
#include <stdio.h>
int     main(void)
{
	t_list *l =  NULL;
       	t_list *l2 =  NULL;

	ft_lstadd_back(&l, ft_lstnew((void*)1));
	ft_lstadd_back(&l, ft_lstnew((void*)2));
	ft_lstadd_back(&l2, ft_lstnew((void*)3));
	ft_lstadd_back(&l2, ft_lstnew((void*)4));
	ft_lstadd_back(&l, l2);

	if (l->content == (void*)1)
		printf("ok");
}
*/
