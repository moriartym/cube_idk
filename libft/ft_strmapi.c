/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:42:37 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:17:24 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
/*
char	ft_changetoa(unsigned int i, char c)
{
	if (i > 16)
		return (c + 1);
	return (c);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	str = (char *) malloc ((i + 1) * sizeof(char));
	if (!str)
		return (0);
	while (i--)
	{
		str[j] = f(j, s[j]);
		j++;
	}
	str[j] = '\0';
	return (str);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s", ft_strmapi("hello my name is jordan", &ft_changetoa));
}
*/
