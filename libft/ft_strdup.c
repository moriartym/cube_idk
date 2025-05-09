/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:49:14 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:12:30 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	int		i;
	char	*str;
	char	*copy;

	i = 0;
	str = (char *) s;
	while (str[i])
		i++;
	copy = (char *) malloc((i + 1) * sizeof(char));
	if (!copy)
		return (0);
	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s",ft_strdup("hello"));
}
*/
