/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:34:53 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 19:18:55 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	cm;
	size_t			i;

	cm = (unsigned char) c % 256;
	str = (unsigned char *) s;
	i = 0;
	if (n == 0)
		return (0);
	while (str[i] != cm && i + 1 < n)
		i++;
	if (str[i] == cm)
		return ((void *) str + i);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char str[50] = "42isthebest";
	printf("%s",(char *)  ft_memchr(0x7ffe1a413930, 399(8f): '\217', 43));
	printf("\n%s",(char *)  memchr(0x7ffe1a413930, 399(8f): '\217', 43));
}
*/
