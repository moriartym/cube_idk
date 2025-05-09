/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:52:25 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 19:22:40 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(void)
{
	printf("%d\n",ft_isdigit('a'));
	printf("%d\n", isdigit('a'));
	printf("%d\n",ft_isdigit('0'));
        printf("%d\n", isdigit('9'));

}
*/
