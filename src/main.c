/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:29:55 by lnicosia          #+#    #+#             */
/*   Updated: 2022/06/13 10:58:57 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>

#include "malloc.h"
#include "libft.h"

#define MAX_ALLOC 5000
#define INCR 3


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

	/*struct rlimit limits;

	if (getrlimit(RLIMIT_AS, &limits) == -1)
		ft_perror("getrlimit: ");
	printf("Soft limit = %ld\n", limits.rlim_cur);
	printf("Hard limit = %ld\n", limits.rlim_max);*/

	//show_alloc_mem_plus();
	//-- FILL PAGE TEST --//
	/*char	*text000[250];
	for (int i = 0; i < 250; i++)
	{
		text000[i] = (char*)malloc(40);
	}
	text000[227][4] = 4;
	ft_printf("After mallocs:\n");
	show_alloc_mem_plus();
	for (int i = 0; i < 250; i++)
	{
		free(text000[i]);
	}
	ft_printf("After frees:\n");
	show_alloc_mem_plus();*/

	//-- BASIC TEST --//
	/*if (ac < 2)
		return 0;
	char *text = (char*)malloc(10);show_alloc_mem_plus();
	char *text2 = (char*)malloc(5);show_alloc_mem_plus();
	char *text3 = (char*)malloc(2);show_alloc_mem_plus();
	char *text4 = (char*)malloc(40);show_alloc_mem_plus();
	char *text5 = (char*)malloc(41);show_alloc_mem_plus();

	ft_printf("text addrr = %p\n", text);
	ft_bzero(text, ft_strlen(av[1] + 1));
	ft_strcpy(text, av[1]);
	ft_putendl(text);
	show_alloc_mem_plus();
	ft_printf("{bold}{yellow}Freeing text2{reset}\n");
	free(text2);ft_printf("Free ok\n");show_alloc_mem_plus();
	ft_printf("{bold}{yellow}Freeing text{reset}\n");
	free(text);ft_printf("Free ok\n");show_alloc_mem_plus();
	ft_printf("{bold}{yellow}Freeing text3{reset}\n");
	free(text3);ft_printf("Free ok\n");show_alloc_mem_plus();
	ft_printf("{bold}{yellow}Freeing text4{reset}\n");
	free(text4);ft_printf("Free ok\n");show_alloc_mem_plus();
	char *text9 = (char*)malloc(5);
	ft_printf("{bold}{yellow}New malloc{reset}\n");
	show_alloc_mem_plus();
	char *text10 = (char*)malloc(68);
	ft_printf("{bold}{yellow}New malloc{reset}\n");
	show_alloc_mem_plus();
	ft_printf("{bold}{yellow}Freeing text5{reset}\n");
	free(text5);ft_printf("Free ok\n");show_alloc_mem_plus();
	ft_printf("{bold}{yellow}Freeing text9{reset}\n");
	free(text9);ft_printf("Free ok\n");show_alloc_mem_plus();
	ft_printf("{bold}{yellow}Freeing text10{reset}\n");
	free(text10);ft_printf("Free ok\n");show_alloc_mem_plus();*/

	//-- REALLOC SMALLER TEST --//
	/*char	*text = (char*)malloc(10000);
	ft_strcpy(text, "bonjo");
	ft_printf("Text = %p (%s)\n", text, text);
	//char	*text2 = (char*)malloc(512);
	show_alloc_mem_plus();
	text = (char*)realloc(text, 900);
	//text[3] = 0;
	ft_printf("Text = %p (%s)\n", text, text);
	show_alloc_mem_plus();
	free(text);
	ft_printf("Free\n");
	show_alloc_mem_plus();*/

	//-- VIM CRASH REPRODUCTION TEST --//

	/*ft_printf("VIM crash test\n");
	char	*text[1000];
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
	text[45][606] = 'a';
	show_alloc_mem_plus();*/

	//-- MALLOC FAIL TEST --//
	/*size_t nb = 9223372036854775807;
	if (malloc(nb) == NULL)
	{
		ft_printf("Too big malloc\n");
		perror("");
	}
	show_alloc_mem_plus();*/

	//-- REALLOC TEST --//
	/*char	*text0 = (char*)malloc(10);
	show_alloc_mem_plus();
	ft_printf("{yellow}Start of reallocs{reset}\n");
	for (int i = 11; i < 100; i++)
	{
		text0 = (char*)realloc(text0, i);
		show_alloc_mem_plus();
	}
	free(text0);*/

	//-- REALLOC DEFRAGMENTING TEST --//
	/*char	*text = (char*)malloc(10);
	char	*text2 = (char*)malloc(10);
	char	*text3 = (char*)malloc(10);
	show_alloc_mem_plus();
	free(text2);
	show_alloc_mem_plus();
	text = (char*)realloc(text, 15);
	show_alloc_mem_plus();*/

	/*char	*text = (char*)malloc(10);
	char	*text2 = (char*)malloc(20);
	ft_printf("Mem after malloc:\n"); show_alloc_mem_plus(); ft_printf("\n");
	free(text);
	ft_printf("Mem after free:\n"); show_alloc_mem_plus(); ft_printf("\n");
	text = (char*)malloc(5);
	ft_printf("Mem after malloc:\n"); show_alloc_mem_plus(); ft_printf("\n");
	text = (char*)realloc(text, 5);
	ft_printf("Mem after realloc:\n"); show_alloc_mem_plus(); ft_printf("\n");*/

	//-- FREE DEFRAGMENTATION TEST --//

	/*void	*ptr = malloc(50);
	void	*ptr2 = malloc(50);
	void	*ptr3 = malloc(50);
	void	*ptr4 = malloc(50);
	show_alloc_mem_plus();
	ft_printf("\nFreeing ptr4 and 3\n");
	free(ptr4);
	show_alloc_mem_plus();
	free(ptr3);
	show_alloc_mem_plus();
	ft_printf("\nNew malloc\n");
	void *ptr5 = malloc(90);
	show_alloc_mem_plus();
	void *ptr6 = malloc(40);
	show_alloc_mem_plus();
	free(ptr5);
	show_alloc_mem_plus();*/

	//-- MALLOC DEFRAG TEST --//
	/*char	*text = (char*)malloc(90);
	char	*text2 = (char*)malloc(90);
	char	*text3 = (char*)malloc(90);
	show_alloc_mem_plus();
	free(text2);
	ft_printf("Free\n");
	show_alloc_mem_plus();
	text2 = (char*)malloc(57);
	ft_printf("New malloc\n");
	show_alloc_mem_plus();
	free(text2);
	ft_printf("Free\n");
	show_alloc_mem_plus();
	text2 = (char*)malloc(1);
	ft_printf("New malloc\n");
	show_alloc_mem_plus();
	free(text2);
	ft_printf("Free\n");
	show_alloc_mem_plus();
	text2 = (char*)malloc(95);
	ft_printf("New malloc\n");
	show_alloc_mem_plus();*/

	/*char	*text1 = (char*)malloc(10);
	char	*text2 = (char*)malloc(10);
	char	*text3 = (char*)malloc(10);
	char	*text4 = (char*)malloc(10);
	show_alloc_mem_plus();
	free(text1);
	//text1 = (char*)malloc(5);
	//free(text3);
	//text3 = (char*)malloc(1);
	show_alloc_mem_plus();
	free(text3);
	show_alloc_mem_plus();
	free(text2);
	show_alloc_mem_plus();
	free(text4);
	show_alloc_mem_plus();*/

	// DEFRAG TEST //

	/*ft_printf("\n{bold}{cyan}Part 1: Reusing freed node with a different alignement{reset}\n\n");
	void	*ptr = malloc(1000);
	void	*ptr1 = malloc(1000);
	void	*ptr2 = malloc(1000);
	free(ptr1);
	show_alloc_mem_plus();
	ptr1 = memalign(64, 1000);
	show_alloc_mem_plus();
	free(ptr);show_alloc_mem_plus();
	free(ptr1);show_alloc_mem_plus();
	free(ptr2);show_alloc_mem_plus();
	ft_printf("{bold}{green}Last free done. Res:\n{reset}");
	show_alloc_mem_plus();

	ft_printf("\n{bold}{cyan}Part 2: Reusing freed node with a different alignement and size{reset}\n\n");
	ptr = malloc(1000);
	ptr1 = malloc(1000);
	ptr2 = malloc(1000);show_alloc_mem_plus();
	free(ptr1);
	show_alloc_mem_plus();
	ptr1 = memalign(64, 512);
	show_alloc_mem_plus();
	free(ptr);show_alloc_mem_plus();
	free(ptr1);show_alloc_mem_plus();
	free(ptr2);show_alloc_mem_plus();
	ft_printf("{bold}{green}Last free done. Res:\n{reset}");
	show_alloc_mem_plus();

	ft_printf("\n{bold}{cyan}Part 3: reusing freed last node with increased size{reset}\n\n");
	ptr = malloc(1000);
	ptr1 = malloc(1000);
	free(ptr1);
	show_alloc_mem_plus();
	ptr1 = malloc(1024);
	show_alloc_mem_plus();
	free(ptr);show_alloc_mem_plus();
	free(ptr1);show_alloc_mem_plus();
	ft_printf("{bold}{green}Last free done. Res:\n{reset}");
	show_alloc_mem_plus();*/

	// TEST1 //
	/*ft_printf("\n{bold}{cyan}TEST1...{reset}\n");
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		void	*data;
		if (!(data = malloc(i)))
			return (-1);
		ft_memset(data, 'a', i);
		free(data);
		//ft_printf("i = %d\n", i);
	}
	ft_printf("{bold}{green}TEST1 OK{reset}\n");
	show_alloc_mem_plus();

	// TEST2 //
	ft_printf("{bold}{cyan}TEST2...{reset}\n");
	void *data2[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data2[i] = malloc(i)))
			return (-1);
		ft_memset(data2[i], 'a', i);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char	cmp[i];
		char	zzzz[i+1];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data2[i], i) != 0) {
			memcpy(zzzz, data2[i], i);
			zzzz[i] = 0;
			ft_dprintf(STDERR_FILENO, "Segment %lu is corrupted ( '%s' )", i, zzzz);
			return -1;
		}
		free(data2[i]);
	}
	ft_printf("{bold}{green}TEST2 OK{reset}\n");
	show_alloc_mem_plus();*/

	// TEST3 //
	/*ft_printf("{bold}{cyan}TEST3...{reset}\n");
	void *data3[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data3[i] = malloc(i)))
			return (-1);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		ft_memset(data3[i], 'a', i);
		free(data3[i]);
	}
	ft_printf("{bold}{green}TEST3 OK{reset}\n");
	show_alloc_mem_plus();*/

	// TEST4 //
	/*ft_printf("{bold}{cyan}TEST4...{reset}\n");
	void *data4[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data4[i] = malloc(i)))
			return -1;
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		ft_memset(data4[i], 'a', i);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data4[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %lu is corrupted", i);
			return -1;
		}
		free(data4[i]);
	}
	ft_printf("{bold}{green}TEST4 OK{reset}\n");
	show_alloc_mem_plus();*/

	// TEST5 //
	/*ft_printf("{bold}{cyan}TEST5...{reset}\n");
	void *data5[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data5[i] = malloc(i)))
			return -1;
		ft_memset(data5[i], 'a', i);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data5[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %lu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data5[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %lu is corrupted", i);
			return -1;
		}
		free(data5[i]);
	}
	ft_printf("{bold}{green}TEST5 OK{reset}\n");
	show_alloc_mem_plus();*/

	// TEST6 //
	/*ft_printf("{bold}{cyan}TEST6...{reset}\n");
	void *data6[MAX_ALLOC];
	for (size_t len = 1; len < MAX_ALLOC; len += INCR)
	{
		char cmp[len];

		ft_memset(cmp, 'a', len);
		for (size_t i = 1; i < MAX_ALLOC; i += INCR)
		{
			if (!(data6[i] = malloc(len)))
			{
				ft_printf("A malloc failed\n");
				perror("");
				return -1;
			}
			ft_memset(data6[i], 'a', len);
		}
		//ft_printf("Data init\n");
		for (size_t i = 1; i < MAX_ALLOC; i += INCR)
		{
			if (memcmp(cmp, data6[i], len) != 0)
			{
				ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )", i, __LINE__);
				return -1;
			}
		}
		//ft_printf("memcmp 1 ok\n");
		for (size_t i = 1; i < MAX_ALLOC; i += INCR)
		{
			if (memcmp(cmp, data6[i], len) != 0)
			{
				ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted ( %d )", i, __LINE__);
				return -1;
			}
			free(data6[i]);
		}
		//ft_printf("free ok\n");
	}
	ft_printf("{bold}{green}TEST6 OK{reset}\n");
	show_alloc_mem_plus();*/

	// TEST7 //
	/*ft_printf("{bold}{cyan}TEST7...{reset}\n");
	void *data7[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data7[i] = realloc(NULL, i)))
			return -1;
		ft_memset(data7[i], 'a', i);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data7[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data7[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
		free(data7[i]);
	}
	ft_printf("{bold}{green}TEST7 OK{reset}\n");
	show_alloc_mem_plus();

	// TEST8 //
	ft_printf("{bold}{cyan}TEST8...{reset}\n");
	void *data8[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data8[i] = malloc(i)))
			return -1;
		if (!(data8[i] = realloc(data8[i], i)))
			return -1;
		ft_memset(data8[i], 'a', i);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data8[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data8[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
		free(data8[i]);
	}
	ft_printf("{bold}{green}TEST8 OK{reset}\n");
	show_alloc_mem_plus();

	// TEST9 //
	ft_printf("{bold}{cyan}TEST9...{reset}\n");
	void *data9[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data9[i] = malloc(i)))
			return -1;
		ft_memset(data9[i], 'a', i);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data9[i] = realloc(data9[i], i)))
			return -1;
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data9[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data9[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data9[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
		free(data9[i]);
	}
	ft_printf("{bold}{green}TEST9 OK{reset}\n");
	show_alloc_mem_plus();

	// TEST10 //
	ft_printf("{bold}{cyan}TEST10...{reset}\n");
	void *data10[MAX_ALLOC];
	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		if (!(data10[i] = malloc(i)))
			return -1;
		ft_memset(data10[i], 'a', i);
	}
	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		if (!(data10[i] = realloc(data10[i], i / 2)))
			return -1;
		char		cmp[i / 2];

		ft_memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data10[i], i / 2) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i / 2];

		ft_memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data10[i], i / 2) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 2; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i / 2];

		ft_memset(cmp, 'a', i / 2);
		if (memcmp(cmp, data10[i], i / 2) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
		free(data10[i]);
	}
	ft_printf("{bold}{green}TEST10 OK{reset}\n");
	show_alloc_mem_plus();

	// TEST11 //
	ft_printf("{bold}{cyan}TEST11...{reset}\n");
	void *data11[MAX_ALLOC];
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data11[i] = malloc(i)))
			return -1;
		ft_memset(data11[i], 'a', i);
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data11[i] = realloc(data11[i], i * 2)))
			return -1;
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data11[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	//show_alloc_mem_plus();
	//ft_printf("\n\n");
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data11[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (size_t i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data11[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "Segment %zu is corrupted", i);
			return -1;
		}
		free(data11[i]);
	}
	ft_printf("{bold}{green}TEST11 OK{reset}\n");
	show_alloc_mem_plus();*/


	// TEST12 //
	/*ft_printf("{bold}{cyan}TEST12...{reset}\n");
	void *data12[MAX_ALLOC];
	ssize_t i;
	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data12[i] = malloc(i)))
			return -1;
		ft_memset(data12[i], 'a', i);
	}
	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		if (!(data12[i] = realloc(data12[i], i * 2)))
			return -1;
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data12[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "cmp 1 Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (i = 1; i < MAX_ALLOC; i += INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data12[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "cmp 2 Segment %zu is corrupted", i);
			return -1;
		}
	}
	for (i = i - INCR; i > 0; i -= INCR)
	{
		char		cmp[i];

		ft_memset(cmp, 'a', i);
		if (memcmp(cmp, data12[i], i) != 0) {
			ft_dprintf(STDERR_FILENO, "cmp 3 Segment %zu is corrupted", i);
			return -1;
		}
		free(data12[i]);
	}
	ft_printf("{bold}{green}TEST12 OK{reset}\n");
	show_alloc_mem_plus();*/
	return (0);
}
