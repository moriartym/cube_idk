/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:42:49 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/26 17:04:01 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
/*
void	ft_del(void *content)
{
	free(content);
}

void	*ft_tp(void *content)
{
	int	i;
	char	*str;
	char	*cont;

	cont = (char *) content;
	i = 0;
	while (cont[i])
		i++;
	str = (char *) malloc (sizeof(char) * (i + 1));
	i = 0;
	while (cont[i])
	{
		if (cont[i] >= 'a' && cont[i] <= 'z')
			str[i] = cont[i] - 32;
		else
			str[i] = cont[i];
		i++;
	}
	str[i] = '\0';
	return ((void *)str);
}
*/
static void	addback(t_list **lst, t_list *new)
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

static t_list	*new(void *content)
{
	t_list	*node;

	node = (t_list *) malloc(sizeof(t_list));
	if (!node)
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}

static void	freeall(t_list *fir, void (*del)(void *))
{
	t_list	*temp;

	while (fir)
	{
		temp = fir->next;
		del(fir->content);
		free(fir);
		fir = temp;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*firstlist;
	t_list	*newlist;
	void	*content;

	if (!lst || !f || !del)
		return (0);
	firstlist = 0;
	while (lst)
	{
		content = f(lst->content);
		newlist = new(content);
		if (!newlist)
		{
			del (content);
			freeall(firstlist, del);
			return (0);
		}
		addback(&firstlist, newlist);
		lst = lst->next;
	}
	return (firstlist);
}
/*
#include <stdio.h>

int	main(void)
{
	t_list test3 = { .content = "hello3", .next = 0};
	t_list test2 = { .content = "hello2", .next = &test3};
	t_list test1 = { .content = "hello1", .next = &test2};
	t_list *mapped;

	mapped = ft_lstmap (&test1, &ft_tp, &ft_del);


	while (mapped)
	{
		printf("%s\n", (char *)mapped->content);
		mapped = mapped->next;
	}
}
*/
