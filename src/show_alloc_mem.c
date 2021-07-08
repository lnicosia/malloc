/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:41:12 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/08 16:15:43 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void	show_page_content(t_page *page)
{
	t_malloc	*mem;
	size_t		total;

	total = 32;
	mem = page->mem;
	while (mem)
	{
		ft_printf("%p - %p : ", mem->start, mem->start + mem->size);
		total += mem->size + 32;
		ft_printf("{cyan}%d bytes / %d total{reset}", mem->size, total);
		if (mem->used == 0)
			ft_printf("{green} (FREE){reset}");
		if ((size_t)mem->start % (size_t)16 != 0)
			custom_error("{red} NOT ALIGNED!!{reset}");
		ft_printf("\n");
		mem = mem->next;
	}
}

void	show_alloc_mem(void)
{
	t_page	*page;

	page = g_memory.tiny;
	pthread_mutex_lock(&g_mutex);
	while (page)
	{
		ft_printf("Printing tiny pages\n");
		ft_printf("{bold}TINY : %p - %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->start + TINY, page->used_space, TINY);
		show_page_content(page);
		page = page->next;
	}
	page = g_memory.small;
	while (page)
	{
		ft_printf("Printing small pages\n");
		ft_printf("{bold}SMALL : %p - %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->start + SMALL, page->used_space, SMALL);
		show_page_content(page);
		page = page->next;
	}
	page = g_memory.large;
	while (page)
	{
		ft_printf("Printing large pages\n");
		ft_printf("{bold}LARGE : %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->used_space, page->used_space);
		show_page_content(page);
		page = page->next;
	}
	pthread_mutex_unlock(&g_mutex);
}