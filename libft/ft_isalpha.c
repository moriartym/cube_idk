/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:07:49 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 19:32:22 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (1024);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main ()
{
	printf("%d\n", ft_isalpha('a'));
	printf("%d\n", isalpha('a'));
        printf("%d\n", ft_isalpha('Z'));
        printf("%d\n", isalpha('Z'));
        printf("%d\n", ft_isalpha('3'));
        printf("%d\n", isalpha('3'));

}
*/
