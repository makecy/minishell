/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstefano <mstefano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 17:58:55 by mstefano          #+#    #+#             */
/*   Updated: 2024/02/11 20:23:11 by mstefano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "libft.h"

// int	ft_atoi(const char *str)
// {
// 	int	i;
// 	int	j;	

// 	i = 0;
// 	j = 1;
// 	while (*str == 32 || (*str >= 9 && *str <= 13))
// 		str++;
// 	if (*str == 45)
// 	{
// 		j = -j;
// 		str++;
// 	}
// 	else if (*str == 43)
// 		str++;
// 	while (*str >= 48 && *str <= 57)
// 	{
// 		i = i * 10 + (*str - 48);
// 		str++;
// 	}
// 	return (i * j);
// }

#include "libft.h"

int	ft_atoi(char *str)
{
	int	g[2];

	g[0] = 0;
	g[1] = 0;
	while ((*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	(*str == '+' || *str == '-') && (g[1] = *(str++));
	while (*str >= '0' && *str <= '9')
		g[0] = (g[0] * 10) + (*(str++) - 48);
	return (g[0] * (((2 * (g[1] == '-')) - 1) * -1));
}
