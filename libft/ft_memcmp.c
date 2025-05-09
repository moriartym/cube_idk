/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:58:59 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 20:02:25 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*cs1;
	char	*cs2;
	size_t	i;

	cs1 = (char *) s1;
	cs2 = (char *) s2;
	i = 0;
	if (n == 0)
		return (0);
	while (cs1[i] == cs2[i] && n > i + 1)
	{
		i++;
	}
	if ((unsigned char)cs1[i] > (unsigned char)cs2[i])
		return (1);
	if ((unsigned char)cs1[i] < (unsigned char)cs2[i])
		return (-1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d",memcmp("darr","dar",4));
	printf("\n%d",ft_memcmp("darr","dar",4));
}
*/
