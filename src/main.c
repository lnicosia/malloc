/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:29:55 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/01 16:25:07 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "malloc.h"
#include "libft.h"

int		main(int ac, char **av)
{
	ft_printf("Size of t_page: %d\n", sizeof(t_page));
	ft_printf("Size of t_malloc: %d\n", sizeof(t_malloc));
	ft_printf("Size of size_t: %d\n", sizeof(size_t));
	ft_printf("Size of unsigned int: %d\n", sizeof(unsigned int));
	ft_printf("Page size = %d\n", getpagesize());

	ft_printf("\nSize of TINY page: %d\n", TINY);
	ft_printf("Max size of TINY blocks: %d\n", TINY_BLOCK);
	ft_printf("Size of SMALL page: %d\n", SMALL);
	ft_printf("Max size of SMALL blocks: %d\n", SMALL_BLOCK);
	ft_printf("Size of LARGE page: %d\n", LARGE);
	ft_printf("Max size of LARGE blocks: %d\n\n", LARGE_BLOCK);

	//-- FILL PAGE TEST --//
	/*char	*text[129];
	for (int i = 0; i < 129; i++)
	{
		ft_printf("i = %d\n", i);
		text[i] = (char*)malloc2(95);
	}
	show_alloc_mem();
	for (int i = 0; i < 129; i++)
	{
		ft_printf("i = %d\n", i);
		free2(text[i]);
	}
	show_alloc_mem();*/
	
	//-- BASIC TEST --//
	/*char *text = (char*)malloc2(10);
	char *text2 = (char*)malloc2(5);
	char *text3 = (char*)malloc2(2);
	char *text4 = (char*)malloc2(40);
	char *text5 = (char*)malloc2(41);
	char *text6 = (char*)malloc2(163483);
	char *text7 = (char*)malloc2(163484);
	char *text8 = (char*)malloc2(16384);
	ft_printf("text addrr = %p\n", text);
	ft_bzero(text, ft_strlen(av[1] + 1));
	ft_strcpy(text, av[1]);
	ft_putendl(text);
	show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text2{reset}\n");
	free2(text2);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text{reset}\n");
	free2(text);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text3{reset}\n");
	free2(text3);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text4{reset}\n");
	free2(text4);ft_printf("Free ok\n");show_alloc_mem();
	char *text9 = (char*)malloc2(5);
	ft_printf("{bold}{yellow}New malloc{reset}\n");
	show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text5{reset}\n");
	free2(text5);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text9{reset}\n");
	free2(text9);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text7{reset}\n");
	free2(text7);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text6{reset}\n");
	free2(text6);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text8{reset}\n");
	free2(text8);ft_printf("Free ok\n");show_alloc_mem();*/

	//-- REALLOC TEST --//
	char	*text = (char*)malloc2(90000);
	ft_strcpy(text, "bonjo");
	ft_printf("Text = %p (%s)\n", text, text);
	show_alloc_mem();
	text = (char*)realloc2(text, 9900);
	//text[3] = 0;
	ft_printf("Text = %p (%s)\n", text, text);
	show_alloc_mem();
	free2(text);
	ft_printf("Free\n");
	show_alloc_mem();

	//-- DEFRAG TEST --//
	/*char	*text = (char*)malloc2(90);
	char	*text2 = (char*)malloc2(90);
	char	*text3 = (char*)malloc2(90);
	show_alloc_mem();
	free2(text2);
	ft_printf("Free\n");
	show_alloc_mem();
	text2 = (char*)malloc2(57);
	ft_printf("New malloc\n");
	show_alloc_mem();
	free2(text2);
	ft_printf("Free\n");
	show_alloc_mem();
	text2 = (char*)malloc2(1);
	ft_printf("New malloc\n");
	show_alloc_mem();
	free2(text2);
	ft_printf("Free\n");
	show_alloc_mem();*/
	return (0);
}