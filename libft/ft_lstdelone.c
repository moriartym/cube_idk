/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:46:49 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:20:52 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
/*
void	ft_del(void *content)
{
	free(content);
}
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	t_list var_next = {.content = "hello1", .next = NULL};

	t_list *test;
	char	*str;

	str = (char *) malloc (sizeof(char) * 6);
	test = (t_list *) malloc (sizeof(t_list));

	strcpy(str, "hello");
	test->content = str;
	test->next = &var_next;

	ft_lstdelone(test, &ft_del);

	printf("%s", str);
	printf("\n%s",(char *) var_next.content);
}
*/
