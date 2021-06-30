/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:53:00 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/30 11:40:11 by lnicosia         ###   ########.fr       */
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

void	remove_page(t_page *page, size_t type)
{
	// Unmapping the actual memory
	if (type != LARGE)
		munmap(page->start, type);
	else
		munmap(page->start, page->used_space);
	if (type == TINY)
		g_memory.tiny = page->next;
	else if (type == SMALL)
		g_memory.small = page->next;
	else
		g_memory.large = page->next;
	// Unmapping the metadata
	munmap(page, sizeof(*page));
}

int		check_page(void *ptr, t_page *page, size_t type)
{
	t_malloc	*mem;
	t_page		*to_remove;

	while (page)
	{
		// Check if the ptr is in the next page so we can remove the node
		// easily if empty afterwards
		if (page->next && (ptr >= page->next->start
			&& ptr <= page->next->start + type))
		{
			mem = page->next->mem;
			while (mem)
			{
				if (mem->start == ptr)
				{
					mem->used = 0;
					// If large type, keep the total size
					if (type != LARGE)
						page->next->used_space -= mem->size;
					break ;
				}
				mem = mem->next;
			}
			// If our plage is now empty, unmap it
			if (page->next->used_space == 0 || type == LARGE)
			{
				to_remove = page->next;
				page->next = page->next->next;
				// Unmapping the actual memory
				if (type != LARGE)
					munmap(to_remove, type);
				else
					munmap(to_remove,
					to_remove->used_space + PAGE_METADATA + BLOCK_METADATA);
			}
			return (1);
		}
		// Specific case if the ptr is in the first page
		if (ptr >= page->start && ptr <= page->start + type)
		{
			mem = page->mem;
			while (mem)
			{
				if (mem->start == ptr)
				{
					mem->used = 0;
					// If large type, keep the total size
					if (type != LARGE)
						page->used_space -= mem->size;
					break ;
				}
				mem = mem->next;
			}
			if (page->used_space == 0 || type == LARGE)
			{
				if (type == TINY)
					g_memory.tiny = page->next;
				else if (type == SMALL)
					g_memory.small = page->next;
				else
					g_memory.large = page->next;
				// Unmapping the actual memory
				if (type != LARGE)
					munmap(page, type);
				else
					munmap(page, page->used_space + PAGE_METADATA + BLOCK_METADATA);
			}
			return (1);
		}
		page = page->next;
	}
	return (0);
}

void	free2(void *ptr)
{
	if (!ptr)
		return ;
	if (check_page(ptr, g_memory.tiny, TINY))
	{
		return ;
	}
	if (check_page(ptr, g_memory.small, SMALL))
	{
		return ;
	}
	// Specific case for large ones, need to remove the page directly
	if (check_page(ptr, g_memory.large, LARGE))
	{
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