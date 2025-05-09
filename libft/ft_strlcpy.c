/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 19:03:32 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:10:00 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (src[k])
		k++;
	if (size < 1)
	{
		return (k);
	}
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (k);
}
/*
#include <stdio.h>
int	main(void)
{
	char dest[50];
	char src[50] = "42 is the best school";

	ft_strlcpy (dest,src,0);
	printf("%s",dest);
}
*/
