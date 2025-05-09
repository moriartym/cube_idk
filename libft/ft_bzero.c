/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:36:01 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:09:12 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = s;
	while (i != n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>

int     main(void)
{
	char    real[11] = "1234567890";

        printf ("\nBefore Real memset: %s \n", real);

        ft_bzero (real + 5, 1);

        printf("\nAfter Real memset: %s \n", real);

	int	i;
	i = 0;
	while (real[i] != '\0')
	{
		i++;
	}
	printf("%d",i);
}
*/
