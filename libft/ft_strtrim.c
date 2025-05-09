/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 12:57:38 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 14:52:59 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <stdio.h>

static int	len(char const *s1)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

static int	ft_front(char const *s1, char const *s2)
{
	int	k;
	int	j;
	int	x;

	k = 0;
	j = 0;
	x = 0;
	while (s1[k] && x == k)
	{
		j = 0;
		while (s2[j])
		{
			if (s1[k] == s2[j])
			{
				x++;
				break ;
			}
			j++;
		}
		k++;
	}
	return (x);
}

static int	ft_back(char const *s1, char const *s2)
{
	int	i;
	int	j;
	int	k;
	int	x;

	k = 0;
	x = 0;
	i = len(s1) - 1;
	j = 0;
	while (i >= 0 && k == x)
	{
		j = 0;
		while (s2[j])
		{
			if (s1[i] == s2[j])
			{
				x++;
				break ;
			}
			j++;
		}
		k++;
		i--;
	}
	return (x);
}

char	*one(void)
{
	char	*str;

	str = (char *) malloc (sizeof(char));
	if (!str)
		return (0);
	str[0] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		same;
	int		size;
	int		front;
	int		i;

	i = 0;
	front = ft_front(s1, set);
	if (len(s1) <= ft_front(s1, set) + ft_back(s1, set))
		return (one());
	else
		same = ft_front(s1, set) + ft_back(s1, set);
	str = (char *) malloc (((len(s1) - same) + 1) * sizeof(char));
	if (!str)
		return (0);
	size = len(s1) - same;
	while (size--)
	{
		str[i] = s1[front];
		front++;
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%d", ft_front("   xxx   xxx", " x"));
}
*/
