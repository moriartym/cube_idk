/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:59:32 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 19:46:16 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		i;
	int		j;

	str = (char *) s;
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (c % 256))
			j = i;
		i++;
	}
	if (j > 0)
		return (str + j);
	if (s[i] == (c % 256))
		return (str + i);
	if (s[j] == (c % 256))
		return (str + j);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	printf("%s",strrchr("hello",'o'));
	printf("\n%s",ft_strrchr("hello",'o'));
}
*/
