/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 11:34:08 by lnicosia          #+#    #+#             */
/*   Updated: 2021/10/25 17:37:29 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define EXTERN
#include "malloc.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*new_page(size_t size, size_t type, size_t alignment)
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
		pthread_mutex_unlock(&g_mutex);
		return (0);
	}
	new->start = new;
	new->used_space = size + PAGE_METADATA + BLOCK_METADATA;
	new->mem = new->start + PAGE_METADATA;
	new->mem->start = new->start + PAGE_METADATA + BLOCK_METADATA;
	if ((size_t)new->mem->start % alignment != 0)
		new->mem->start += alignment - (size_t)new->mem->start % alignment;
	if ((size_t)new->mem->start % alignment != 0)
		ft_printf("T'as foiré ton calcul connard\n");
	new->mem = new->mem->start - BLOCK_METADATA;
	new->mem->size = size;
	new->mem->used = 1;
	new->next = NULL;
	if (!page)
		*page_addr = new;
	else
		page->next = new;
	//ft_printf("New page, returning [%p]\n", new->mem->start);
	//show_alloc_mem();
	pthread_mutex_unlock(&g_mutex);
	return (new->mem->start);
}

// Main function that takes the wanted alignment as arg
void	*memalign(size_t alignment, size_t size)
{
	t_page		*page;
	t_malloc	*mem;
	t_malloc	*new;
	t_malloc	*prev;
	void		*aligned_ptr;
	size_t		type;

	if (!is_power_of_two(alignment))
		return (NULL);
	pthread_mutex_lock(&g_mutex);
	//ft_printf("\nMalloc of %d\n", size);
	//if (size == 46)
	//	show_alloc_mem();
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
					// We found a free block with enough space
					// Alignment may have changed
					aligned_ptr = mem->start;
					if ((size_t)aligned_ptr % alignment != 0)
						aligned_ptr += alignment - (size_t)aligned_ptr % alignment;
					if ((size_t)aligned_ptr % alignment != 0)
						ft_printf("T'as foiré ton calcul connard\n");
					// Alignement didnt change, easy
					if (aligned_ptr == mem->start)
					{
						mem->used = 1;
						page->used_space += mem->size + BLOCK_METADATA;
						if (mem->size - size > BLOCK_METADATA
							&& mem->size - size % alignment == 0)
							new_block(mem, alignment, size);
						pthread_mutex_unlock(&g_mutex);
						return (mem->start);
					}
					// Check if if still have enough place after realigning
					if ((!mem->next && (size_t)aligned_ptr + size <= type)
						|| (mem->next && ((ssize_t)mem->next - (ssize_t)aligned_ptr >= (ssize_t)size)))
					{
						new = aligned_ptr - BLOCK_METADATA;
						new->start = aligned_ptr;
						new->used = 1;
						new->next = mem->next;
						// Update the size with the newly aligned ptr
						if (mem->next)
							new->size = (size_t)mem->next - (size_t)aligned_ptr;
						else
							new->size = size;
						// If we're not gonna use all the space
						// and we can create a new block after this one, do it
						void	*new_block_ptr = new->start + new->size;
						if ((size_t)new_block_ptr % 16 != 0)
							new_block_ptr += 16 - (size_t)new_block_ptr % 16;
						if ((size_t)new_block_ptr % 16 != 0)
							ft_printf("T'as foiré ton calcul connard\n");
						if (new->start + new->size - new_block_ptr > (long int)BLOCK_METADATA)
							new_block(new, 16, (size_t)new->start + new->size - (size_t)new_block_ptr);
						// Update prev
						if (prev)
						{
							if ((size_t)new - (size_t)prev->next > BLOCK_METADATA)
							{
								
							}
							// Update the used space
							// if we increase previous node's size
							if (prev->next != new)
								page->used_space += (size_t)new - (size_t)prev->next;
							prev->next = new;
							prev->size = (size_t)prev->next - (size_t)prev->start;
						}
						else
						{
							page->mem = new;
						}
						page->used_space += new->size + BLOCK_METADATA;
						//ft_printf("Free space used:\n");
						//show_alloc_mem();
						//ft_printf("Returning %p\n", new->start);
						pthread_mutex_unlock(&g_mutex);
						return (new->start);
					}
				}
				// Save prev node to connect the new one with it
				prev = mem;
				mem = mem->next;
			}
			aligned_ptr = prev->start + prev->size + BLOCK_METADATA;
			if ((size_t)aligned_ptr % alignment != 0)
				aligned_ptr += alignment - (size_t)aligned_ptr % alignment;
			if ((size_t)aligned_ptr % alignment != 0)
				ft_printf("T'as foiré ton calcul connard\n");
			// Check if we have enough space left at the end of the page
			if (aligned_ptr + size <= page->start + type)
			{
				prev->next = aligned_ptr - BLOCK_METADATA;
				// Cast as void* so we add BLOCK_METADATA bytes
				// and not BLOCK_METADATA * sizeof(t_malloc)
				prev->next->start = aligned_ptr;
				prev->next->size = size;
				prev->next->used = 1;
				prev->next->next = NULL;
				page->used_space += size + BLOCK_METADATA;
				//ft_printf("New block\n");
				//show_alloc_mem();
				//ft_printf("New block ok, returning");
				//ft_printf(" (%p)\n", prev->next->start);
				pthread_mutex_unlock(&g_mutex);
				return (prev->next->start);
			}
		}
		page = page->next;
	}
	// We didnt find any space in our existing plage, let's create some
	// Failed to create a new page metadata
	return (new_page(size, type, alignment));
}

void	*malloc(size_t size)
{
	return (memalign(16, size));
}