/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:34:17 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/26 18:13:07 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

static	char	**freeall(char	**buffer, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		free(buffer[i]);
		i++;
	}
	free(buffer);
	return (0);
}

static int	array_length(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c && s[i])
			i++;
	}
	return (j);
}

static int	fsl(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

static char	*fsm(char const *s, int size)
{
	char	*str;
	int		k;
	int		i;

	k = 0;
	i = 0;
	str = (char *) malloc ((size + 1) * sizeof(char));
	if (!str)
		return (0);
	while (size--)
	{
		str[k] = s[i];
		k++;
		i++;
	}
	str[k] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**buffer;
	int		size;
	int		j;

	j = 0;
	size = array_length(s, c);
	buffer = (char **)malloc (sizeof(char *) * (size + 1));
	if (!buffer)
		return (0);
	while (*s != 0)
	{
		if (fsl(s, c) > 0)
		{
			buffer[j] = fsm(s, fsl(s, c));
			if (!buffer[j])
				return (freeall(buffer, j));
			j++;
			while (*s != c && *s != 0)
				s++;
		}
		if (*s != 0)
			s++;
	}
	buffer[j] = 0;
	return (buffer);
}
/*
int	main(void)
{
	char	**array = ft_split("  tripouille  42  ", ' ');

	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}
*/
