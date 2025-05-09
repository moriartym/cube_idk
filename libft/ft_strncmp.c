/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:07:55 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 15:06:38 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i] && s1[i] != '\0') && (s2[i] != '\0' && n > i + 1))
	{
		i++;
	}
	if ((unsigned char)s1[i] > (unsigned char)s2[i])
		return (1);
	if ((unsigned char)s1[i] < (unsigned char)s2[i])
		return (-1);
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%d",strncmp("abd","abc",3));
	printf("\n%d",ft_strncmp("abd","abc",3));
}
*/
