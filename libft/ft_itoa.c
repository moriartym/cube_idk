/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:18:11 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/22 14:53:48 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

static int	ft_strlen(int n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_max(long n)
{
	char	*str;
	int		size;

	size = 11;
	str = (char *) malloc (size + 1 * sizeof(char));
	if (!str)
		return (0);
	str[size] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[size - 1] = (n % 10) + 48;
		n = n / 10;
		size--;
	}
	return (str);
}

static char	*ft_zero(void)
{
	char	*str;

	str = (char *)malloc (sizeof(char) * 2);
	if (!str)
		return (0);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	if (n == -2147483648)
		return (ft_max((long) n));
	if (n == 0)
		return (ft_zero());
	size = ft_strlen(n);
	str = (char *) malloc (size + 1 * sizeof(char));
	if (!str)
		return (0);
	str[size] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[size - 1] = (n % 10) + 48;
		n = n / 10;
		size--;
	}
	return (str);
}

/*
#include <stdio.h>
int	main(void)
{
	printf("%s",ft_itoa(-2147483648));
}
*/
