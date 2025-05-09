/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:09:50 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 21:12:07 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *) big;
	i = 0;
	if (little[0] == '\0')
		return (str);
	while (i < len && big[i])
	{
		j = 0;
		while (big[i] == little[j] && i < len && little[j])
		{
			j++;
			i++;
		}
		if (little[j] == '\0')
			return (str + i - j);
		else if (j > 0)
			i = i - j;
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s", ft_strnstr("aaabcabcd", "aabc", 100));
}
*/
