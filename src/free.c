/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:53:00 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/01 09:28:38 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int		check_page(void *ptr, t_page *page, size_t type)
{
	t_malloc	*mem;
	t_page		*prev;

	prev = NULL;
	while (page)
	{
		// Check if the ptr is in the next page so we can remove the node
		// easily if empty afterwards
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
						page->used_space -= mem->size + BLOCK_METADATA;
					break ;
				}
				mem = mem->next;
			}
			// If our plage is now empty, unmap it
			if (page->used_space == PAGE_METADATA || type == LARGE)
			{
				// Specific case if it's the first node
				if (prev == NULL)
				{
					if (type == TINY)
						g_memory.tiny = page->next;
					else if (type == SMALL)
						g_memory.small = page->next;
					else
						g_memory.large = page->next;
				}
				else
					prev->next = page->next;
				// Unmapping the actual memory
				if (type != LARGE)
					munmap(page, type);
				else
					munmap(page, page->used_space);
			}
			return (1);
		}
		prev = page;
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