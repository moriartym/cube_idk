/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:53:26 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 16:46:32 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char			*strsrc;
	char			*strdest;

	if (!dest && !src)
		return (0);
	strsrc = (char *)src;
	strdest = (char *)dest;
	if (strsrc < strdest)
	{
		while (n--)
			strdest[n] = strsrc[n];
	}
	else
	{
		while (n--)
			*strdest++ = *strsrc++;
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char *strsrc = "0123456789";
	char strdest[11] = "1";
	ft_memmove(strdest,strsrc,5);
	printf("%s",strdest);
}
*/
