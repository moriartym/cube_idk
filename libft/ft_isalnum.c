/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:01:39 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/18 17:02:19 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	unsigned char	check;

	check = (unsigned char) c;
	if ((check >= 'A' && check <= 'Z') || (check >= 'a' && check <= 'z')
		|| (check >= '0' && check <= '9'))
		return (8);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>

int	main(void)
{
	printf("%d\n",ft_isalnum('-'));
	printf("%d\n",isalnum('-'));
	printf("%d\n",ft_isalnum('a'));
        printf("%d\n",isalnum('a'));
	printf("%d\n",ft_isalnum('0'));
        printf("%d\n",isalnum('0'));
}
*/
