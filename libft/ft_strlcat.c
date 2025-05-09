/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:30:33 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:10:08 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (dst[i])
		i++;
	while (src[k])
		k++;
	if (size <= i)
	{
		return (size + k);
	}
	while (src[j] != '\0' && j < size - 1 - i)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + k);
}
/*
#include <stdio.h>
int	main(void)
{
	char	dst[50] = "42 is the";
	char	src[50] = " best school in the world";
	printf("%zu", ft_strlcat(dst, src, 5));
	printf("\n%s", dst);
}
*/
