/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:41:12 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/30 10:16:30 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void	show_page_content(t_page *page)
{
	t_malloc	*mem;

	mem = page->mem;
	while (mem)
	{
		ft_printf("%p - %p : ", mem->start, mem->start + mem->size);
		if (mem->used == 1)
			ft_printf("{cyan}%d bytes{reset}\n", mem->size);
		else
			ft_printf("{green}AVAILABLE{reset}\n");
		mem = mem->next;
	}
}

void	show_alloc_mem(void)
{
	t_page	*page;

	page = g_memory.tiny;
	while (page)
	{
		ft_printf("{bold}TINY : %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->used_space, TINY);
		show_page_content(page);
		page = page->next;
	}
	page = g_memory.small;
	while (page)
	{
		ft_printf("{bold}SMALL : %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->used_space, SMALL);
		show_page_content(page);
		page = page->next;
	}
	page = g_memory.large;
	while (page)
	{
		ft_printf("{bold}LARGE : %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->used_space, page->used_space);
		show_page_content(page);
		page = page->next;
	}
}