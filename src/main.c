/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:29:55 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/25 19:58:05 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "malloc.h"
#include "libft.h"

int		main(int ac, char **av)
{
	ft_printf("Page size = %d\n", getpagesize());
	char	*text = (char*)malloc2(10);
	if (!text)
		ft_printf("Error\n");
	for (int i = 0; i < 420; i++)
	{
		ft_printf("i = %d\n", i);
		char	*text1 = (char*)malloc2(10);
		(void)text1;
		//ft_printf("text1 addrr = %p\n", text1);
	}
	char *text2 = (char*)malloc2(5);
	char *text3 = (char*)malloc2(2);
	ft_printf("text addrr = %p\n", text);
	ft_bzero(text, ft_strlen(av[1] + 1));
	ft_strcpy(text, av[1]);
	ft_putendl(text);
	show_alloc_mem();
	//free2(text);
	ft_printf("text addrr after free = %p\n", text);
	(void)ac;
	return (0);
}