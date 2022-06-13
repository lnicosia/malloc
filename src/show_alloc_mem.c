/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:41:12 by lnicosia          #+#    #+#             */
/*   Updated: 2022/06/13 10:59:31 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

size_t	show_page_content_plus(t_page *page)
{
	t_malloc	*mem;
	size_t		total;
	size_t		full_total;

	total = 0;
	full_total = PAGE_METADATA;
	mem = page->mem;
	while (mem)
	{
		if (mem->used != 0)
			total += mem->size;
		full_total += mem->size + BLOCK_METADATA;
		ft_printf("%p - %p : ", mem->start, mem->start + mem->size);
		if (mem->used == 0)
			ft_printf("{green}%ld bytes FREE{reset}", mem->size);
		else
			ft_printf("{cyan}%ld / %ld bytes", mem->size, total);
		ft_printf("{cyan} (%ld total){reset}", full_total);
		if ((size_t)mem->start % (size_t)16 != 0)
			custom_error("{red} NOT ALIGNED!!{reset}");
		ft_printf("\n");
		mem = mem->next;
	}
	return total;
}


void	show_alloc_mem_plus(void)
{
	t_page	*page;
	size_t	total;

	total = 0;
	page = g_memory.tiny;
	pthread_mutex_lock(&g_mutex);
	while (page)
	{
		ft_printf("{bold}TINY : %p - %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->start + TINY, page->used_space, TINY);
		ft_printf("%p - %p (page metadata) : ", page->start, page->start + PAGE_METADATA);
		ft_printf("{cyan}%ld bytes / %ld (%ld total){reset}\n",
			PAGE_METADATA, PAGE_METADATA, PAGE_METADATA);
		total += show_page_content_plus(page);
		page = page->next;
	}
	page = g_memory.small;
	while (page)
	{
		ft_printf("{bold}SMALL : %p - %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->start + SMALL, page->used_space, SMALL);
		ft_printf("%p - %p (page metadata): ", page->start, page->start + PAGE_METADATA);
		ft_printf("{cyan}%ld bytes / %ld (%ld total){reset}\n",
			PAGE_METADATA, PAGE_METADATA, PAGE_METADATA);
		total += show_page_content_plus(page);
		page = page->next;
	}
	page = g_memory.large;
	while (page)
	{
		ft_printf("{bold}LARGE : %p {cyan}(%dB/%dB){reset}\n", page->start,
		page->used_space, page->used_space);
		total += show_page_content_plus(page);
		page = page->next;
	}
	if (total <= 1)
		ft_printf("Total : %ld octet\n", total);
	else
		ft_printf("Total : %ld octets\n", total);
	pthread_mutex_unlock(&g_mutex);
}

size_t	show_page_content(t_page *page)
{
	t_malloc	*mem;
	size_t		total;


	total = 0;
	mem = page->mem;
	while (mem)
	{
		if (mem->used == 1)
		{
			ft_printf("0x%X - 0x%X : ", mem->start, mem->start + mem->size);
			total += mem->size;
			ft_printf("%ld octets", mem->size);
			ft_printf("\n");
		}
		mem = mem->next;
	}
	return total;
}

void	show_alloc_mem(void)
{
	t_page	*page;
	size_t	total;

	total = 0;
	page = g_memory.tiny;
	pthread_mutex_lock(&g_mutex);
	while (page)
	{
		ft_printf("TINY : 0x%X\n", page->start);
		total += show_page_content(page);
		page = page->next;
	}
	page = g_memory.small;
	while (page)
	{
		ft_printf("SMALL : 0x%X\n", page->start);
		total += show_page_content(page);
		page = page->next;
	}
	page = g_memory.large;
	while (page)
	{
		ft_printf("LARGE : 0x%X\n", page->start);
		total += show_page_content(page);
		page = page->next;
	}
	if (total <= 1)
		ft_printf("Total : %ld octet\n", total);
	else
		ft_printf("Total : %ld octets\n", total);
	pthread_mutex_unlock(&g_mutex);
}
