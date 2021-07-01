/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:34:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/01 14:01:47 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define EXTERN
#include "malloc.h"

void	*new_page(size_t size, size_t type)
{
	t_page	*page;
	t_page	**page_addr;
	t_page	*new;
	size_t	map_size;

	if (type == TINY)
	{
		page = g_memory.tiny;
		page_addr = &g_memory.tiny;
		map_size = type;
	}
	else if (type == SMALL)
	{
		page = g_memory.small;
		page_addr = &g_memory.small;
		map_size = type;
	}
	else
	{
		page = g_memory.large;
		page_addr = &g_memory.large;
		map_size = size + PAGE_METADATA + BLOCK_METADATA;
	}
	while (page && page->next)
		page = page->next;
	if ((new = mmap(0, map_size, PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS | MAP_SHARED, -1, 0)) == MAP_FAILED)
	{
		ft_perror("Map error:");
		return (0);
	}
	new->start = new;
	new->used_space = size + PAGE_METADATA + BLOCK_METADATA;
	new->mem = new->start + PAGE_METADATA;
	new->mem->start = new->start + PAGE_METADATA + BLOCK_METADATA;
	new->mem->size = size;
	new->mem->used = 1;
	if (!page)
		*page_addr = new;
	else
		page->next = new;
	return (new->mem->start);
}

void	*malloc2(size_t size)
{
	t_page		*page;
	t_malloc	*mem;
	t_malloc	*prev;
	size_t		type;

	if (size <= TINY_BLOCK)
	{
		page = g_memory.tiny;
		type = TINY;
	}
	else if (size <= SMALL_BLOCK)
	{
		page = g_memory.small;
		type = SMALL;
	}
	else
	{
		page = g_memory.large;
		type = LARGE;
	}
	// Searching if we have some space available in our existing pages
	// except for large ones
	while (type != LARGE && page)
	{
		prev = NULL;
		// Check if there is enough space left for a new block
		if (page->used_space + size + BLOCK_METADATA <= type)
		{
			// Defragmenting:
			// Before setting up a new block, check if
			// there is a big enough one unused
			mem = page->mem;
			while (mem)
			{
				if (mem->used == 0 && mem->size >= size)
				{
					// If we're not gonna use all the space
					// and we can create a new block after this one, do it
					if (mem->size - size > 32)
						new_block(mem, size);
					mem->used = 1;
					page->used_space += size + BLOCK_METADATA;
					return (mem->start);
				}
				// Save prev node to connect the new one with it
				prev = mem;
				mem = mem->next;
			}
			// Specific case when we have only one node
			if (prev == NULL)
				prev = mem;
			prev->next = prev->start + prev->size;
			// Cast as void* so we add BLOCK_METADATA bytes
			// and not BLOCK_METADATA * sizeof(t_malloc)
			prev->next->start = (void*)prev->next + BLOCK_METADATA;
			prev->next->size = size;
			prev->next->used = 1;
			page->used_space += size + BLOCK_METADATA;
			return (prev->next->start);
		}
		page = page->next;
	}
	// We didnt find any space in our existing plage, let's create some
	// Failed to create a new page metadata
	return (new_page(size, type));
}