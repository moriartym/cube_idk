/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:51:36 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 16:45:52 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		k;

	i = 0;
	k = 0;
	str = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (0);
	while (s1[i])
	{
		str[k] = s1[i];
		i++;
		k++;
	}
	i = 0;
	while (s2[i])
	{
		str[k] = s2[i];
		i++;
		k++;
	}
	str[k] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s", ft_strjoin("hello", " my name is john"));
}
*/
