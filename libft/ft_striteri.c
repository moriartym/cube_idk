/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:25:37 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/19 16:31:48 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
void	ft_change(unsigned int i, char *str)
{
	if (i > 4)
		str[i] = 'a';
}
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] && s)
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char string[50] = "0123456789";
	ft_striteri(string, &ft_change);
	printf("%s\n", string);
}
*/
