/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:34:10 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 15:23:57 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *nptr)
{
	long	i;
	long	s;
	long	m;

	i = 0;
	m = 1;
	s = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			m = m * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		s = s * 10 + (nptr[i] - 48);
		i++;
	}
	s = s * m;
	if (s <= 2147483647 && s >= -2147483648)
		return ((int)s);
	return (0);
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	printf("%d", atoi("+00123a"));
	printf("\n%d", ft_atoi("+00123a"));
}
*/
