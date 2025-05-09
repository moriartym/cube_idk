/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:14:39 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 19:23:17 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (16384);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf ("%d",ft_isprint(1));
	printf ("\n%d",isprint(1));
	printf ("\n%d",ft_isprint(32));
        printf ("\n%d",isprint(32));
}
*/
