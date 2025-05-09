/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:26:06 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/26 14:15:28 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*str;
	unsigned int	i;
	size_t			total;

	i = 0;
	total = nmemb * size;
	if (size * nmemb >= 2147463647)
		return (0);
	str = (char *) malloc (total);
	if (!str)
		return (0);
	while (total--)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}
/*
#include <stdio.h>
int	main(void)
{
	int* allocated_with_calloc = ft_calloc(0, 4);
	printf("Values of allocated_with_calloc: ");
	for (size_t i = 0; i < 5; ++i)
	{
		printf("%d ", allocated_with_calloc[i]);
	}
}
*/
