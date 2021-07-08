/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:29:55 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/08 14:02:01 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "malloc.h"
#include "libft.h"

int		main(int ac, char **av)
{
	ft_printf("Size of void *: %d\n", sizeof(void*));
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
	/*char	*text[250];
	for (int i = 0; i < 250; i++)
	{
		ft_printf("i = %d\n", i);
		text[i] = (char*)malloc(40);
	}
	text[227][4] = 4;
	show_alloc_mem();
	for (int i = 0; i < 250; i++)
	{
		ft_printf("i = %d\n", i);
		free(text[i]);
	}
	show_alloc_mem();*/
	
	//-- BASIC TEST --//
	/*if (ac < 2)
		return 0;
	char *text = (char*)malloc(10);
	char *text2 = (char*)malloc(5);
	char *text3 = (char*)malloc(2);
	char *text4 = (char*)malloc(40);
	char *text5 = (char*)malloc(41);
	char *text6 = (char*)malloc(163483);
	char *text7 = (char*)malloc(163484);
	char *text8 = (char*)malloc(16384);
	ft_printf("text addrr = %p\n", text);
	ft_bzero(text, ft_strlen(av[1] + 1));
	ft_strcpy(text, av[1]);
	ft_putendl(text);
	show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text2{reset}\n");
	free(text2);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text{reset}\n");
	free(text);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text3{reset}\n");
	free(text3);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text4{reset}\n");
	free(text4);ft_printf("Free ok\n");show_alloc_mem();
	char *text9 = (char*)malloc(5);
	ft_printf("{bold}{yellow}New malloc{reset}\n");
	show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text5{reset}\n");
	free(text5);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text9{reset}\n");
	free(text9);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text7{reset}\n");
	free(text7);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text6{reset}\n");
	free(text6);ft_printf("Free ok\n");show_alloc_mem();
	ft_printf("{bold}{yellow}Freeing text8{reset}\n");
	free(text8);ft_printf("Free ok\n");show_alloc_mem();*/

	//-- REALLOC TEST --//
	/*char	*text = (char*)malloc(90000);
	ft_strcpy(text, "bonjo");
	ft_printf("Text = %p (%s)\n", text, text);
	show_alloc_mem();
	text = (char*)realloc(text, 9900);
	//text[3] = 0;
	ft_printf("Text = %p (%s)\n", text, text);
	show_alloc_mem();
	free(text);
	ft_printf("Free\n");
	show_alloc_mem();*/

	/*char	*text1 = (char*)malloc(40000);
	char	*text2 = (char*)malloc(32816);
	show_alloc_mem();
	ft_printf("Free\n");
	free(text2);*/

	//-- VIM CRASH REPRODUCTION TEST --//
	/*char	*text[1000];
	text[0] = (char*)malloc(8192);
	text[1] = (char*)malloc(4096);
	text[2] = (char*)malloc(336);
	text[3] = (char*)malloc(336);
	text[4] = (char*)malloc(1025);
	text[5] = (char*)malloc(104);
	text[6] = (char*)malloc(192);
	text[7] = (char*)malloc(104);
	text[8] = (char*)malloc(104);
	text[9] = (char*)malloc(104);
	text[10] = (char*)malloc(104);
	text[11] = (char*)malloc(112);
	text[12] = (char*)malloc(1600);
	text[13] = (char*)malloc(168);
	text[14] = (char*)malloc(120);
	text[15] = (char*)malloc(104);
	text[16] = (char*)malloc(191);
	text[18] = (char*)malloc(4096);
	text[19] = (char*)malloc(2048);
	text[20] = (char*)malloc(104);
	text[21] = (char*)malloc(104);
	text[22] = (char*)malloc(104);
	text[23] = (char*)malloc(432);
	text[24] = (char*)malloc(104);
	text[25] = (char*)malloc(216);
	text[26] = (char*)malloc(104);
	text[27] = (char*)malloc(1336);
	text[28] = (char*)malloc(104);
	text[29] = (char*)malloc(112);
	text[30] = (char*)malloc(104);
	text[31] = (char*)malloc(776);
	text[32] = (char*)malloc(227);
	text[33] = (char*)malloc(192);
	text[34] = (char*)malloc(8672);
	text[35] = (char*)malloc(576);
	text[36] = (char*)malloc(336);
	text[37] = (char*)malloc(9096);
	text[38] = (char*)malloc(336);
	text[39] = (char*)malloc(1392);
	text[40] = (char*)malloc(224);
	text[41] = (char*)malloc(336);
	text[42] = (char*)malloc(100);
	text[43] = (char*)malloc(121);
	text[44] = (char*)malloc(607);
	text[45] = (char*)malloc(607);
	text[46] = (char*)malloc(746);
	text[47] = (char*)malloc(746);
	text[48] = (char*)malloc(6000);
	text[49] = (char*)malloc(1280);
	text[16] = (char*)realloc(text[16], 104);
	free(text[42]);
	free(text[44]);
	free(text[46]);
	free(text[48]);
	text[33] = (char*)realloc(text[33], 200);
	text[33][0] = 'a';
	text[33][199] = 'a';
	text[32][0] = 'a';
	text[32][226] = 'a';
	text[34][0] = 'a';
	text[34][8671] = 'a';
	text[43][0] = 'a';
	text[43][120] = 'a';
	text[45][0] = 'a';
	text[45][606] = 'a';*/

	//-- REALLOC TEST --//
	/*char	*text = (char*)malloc(10);
	for (int i = 11; i < 100; i++)
	{
		text = (char*)realloc(text, i);
		show_alloc_mem();
	}*/


	//-- REALLOC DEFRAGMENTING TEST --//
	/*char	*text = (char*)malloc(10);
	char	*text2 = (char*)malloc(10);
	char	*text3 = (char*)malloc(10);
	show_alloc_mem();
	free(text2);
	show_alloc_mem();
	text = (char*)realloc(text, 11);
	show_alloc_mem();*/

	/*char	*text = (char*)malloc(10);
	char	*text2 = (char*)malloc(20);
	ft_printf("Mem after malloc:\n"); show_alloc_mem(); ft_printf("\n");
	free(text);
	ft_printf("Mem after free:\n"); show_alloc_mem(); ft_printf("\n");
	text = (char*)malloc(5);
	ft_printf("Mem after malloc:\n"); show_alloc_mem(); ft_printf("\n");
	text = (char*)realloc(text, 5);
	ft_printf("Mem after realloc:\n"); show_alloc_mem(); ft_printf("\n");*/

	//-- FREE DEFRAGMENTATION TEST --//

	/*void	*ptr = malloc(50);
	void	*ptr2 = malloc(50);
	void	*ptr3 = malloc(50);
	void	*ptr4 = malloc(50);
	show_alloc_mem();
	ft_printf("\nFreeing ptr2 and 3\n");
	free(ptr4);
	free(ptr3);
	show_alloc_mem();
	ft_printf("\nNew malloc\n");
	void *ptr5 = malloc(90);
	show_alloc_mem();*/

	//-- DEFRAG TEST --//
	/*char	*text = (char*)malloc(90);
	char	*text2 = (char*)malloc(90);
	char	*text3 = (char*)malloc(90);
	show_alloc_mem();
	free(text2);
	ft_printf("Free\n");
	show_alloc_mem();
	text2 = (char*)malloc(57);
	ft_printf("New malloc\n");
	show_alloc_mem();
	free(text2);
	ft_printf("Free\n");
	show_alloc_mem();
	text2 = (char*)malloc(1);
	ft_printf("New malloc\n");
	show_alloc_mem();
	free(text2);
	ft_printf("Free\n");
	show_alloc_mem();*/

	/*char	*text1 = (char*)malloc(10);
	char	*text2 = (char*)malloc(10);
	free(text1);
	//text1 = (char*)malloc(5);
	//char *text3 = (char*)malloc(1);
	show_alloc_mem();
	free(text1);
	show_alloc_mem();*/
	return (0);
}