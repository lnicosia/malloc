/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:53:00 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/28 12:28:27 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int		is_page_empty(t_page *page)
{
	t_malloc	*mem;

	mem = page->mem;
	while (mem)
	{
		if (mem->used == 1)
			return (0);
		mem = mem->next;
	}
	return (1);
}

void	remove_page(t_page *page)
{
	(void)page;
}

int		check_page(void *ptr, t_page *page)
{
	t_malloc	*mem;

	while (page)
	{
		// Check if our ptr is in this page
		if (ptr >= page->start && ptr <= page->start + TINY)
		{
			mem = page->mem;
			while (mem)
			{
				// Case where the first alloc is our ptr
				if (mem->start == ptr)
				{
					mem->used = 0;
					page->used_space -= mem->size;
					return (1);
				}
				mem = mem->next;
			}
		}
		page = page->next;
	}
	return (0);
}

void	free2(void *ptr)
{
	if (!ptr)
		return ;
	if (check_page(ptr, g_memory.tiny))
	{
		if (is_page_empty(g_memory.tiny))
			remove_page(g_memory.tiny);
		return ;
	}
	if (check_page(ptr, g_memory.small))
	{
		if (is_page_empty(g_memory.small))
			remove_page(g_memory.small);
		return ;
	}
	if (check_page(ptr, g_memory.large))
	{
		if (is_page_empty(g_memory.large))
			remove_page(g_memory.large);
		return ;
	}
}

void	*fatal_error(void)
{
	while (g_memory.tiny)
	{
		
	}
	return (0);
}