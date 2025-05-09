/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:52:52 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 16:44:58 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*strsrc;
	char			*strdest;
	unsigned int	i;

	if (!dest && !src)
		return (0);
	strsrc = (char *)src;
	strdest = (char *)dest;
	i = 0;
	while (i < n)
	{
		strdest[i] = strsrc[i];
		i++;
	}
	return (strdest);
}
/*
#include <stdio.h>
int	main(void)
{
	char strsrc[3] = "12";
	char strdest[3];
	ft_memcpy(strdest,strsrc,5);
	printf("%s",strdest);
}
*/
