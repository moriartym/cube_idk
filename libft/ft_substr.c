/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:44:10 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 14:53:17 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	count_size(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned int	k;

	k = 0;
	i = 0;
	while (s[k])
		k++;
	if (k < start)
	{
		return (0);
	}
	while (s[start])
	{
		start++;
		i++;
	}
	if (i < len)
		return (i);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	int			i;
	int			size;

	i = 0;
	size = count_size(s, start, len);
	if (size == 0)
	{
		str = (char *) malloc(1 * sizeof(char));
		if (!str)
			return (0);
		str[0] = 0;
		return (str);
	}
	str = (char *) malloc(size + 1 * sizeof(char));
	if (!str)
		return (0);
	while (len-- && s[start])
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s", ft_substr("0123456789", 10, 100));
}
*/
