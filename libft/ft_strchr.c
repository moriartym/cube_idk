/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfasius <dfasius@student.42.sg>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:51:48 by dfasius           #+#    #+#             */
/*   Updated: 2024/05/20 17:12:35 by dfasius          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	int		cm;
	int		i;

	cm = c % 256;
	str = (char *) s;
	i = 0;
	while (s[i] != cm && s[i] != '\0')
		i++;
	if (s[i] == cm)
		return (str + i);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char *s = "hello";
	printf("%d", (strchr(s, '\0')[0]));
	printf("\n%s", s);
	printf("\n%d", (ft_strchr(s, '\0')[0]));
	printf("\n%s", s);
}
*/
