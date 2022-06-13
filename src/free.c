/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 12:53:00 by lnicosia          #+#    #+#             */
/*   Updated: 2022/06/13 10:27:50 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int		check_large_page(void *ptr, t_page *page)
{
	t_page		*prev;

	prev = NULL;
	while (page)
	{
		// Check if the ptr is in the next page so we can remove the node
		// easily if empty afterwards
		if (ptr == page->mem->start)
		{
			// Specific case if it's the first node
			if (prev == NULL)
				g_memory.large = page->next;
			else
				prev->next = page->next;
			// Unmapping the actual memory
			munmap(page, page->used_space);
			return (1);
		}
		prev = page;
		page = page->next;
	}
	return (0);
}

int		check_page(void *ptr, t_page *page, size_t type)
{
	t_malloc	*mem;
	t_malloc	*prev_mem;
	t_page		*prev;

	prev = NULL;
	while (page)
	{
		// Check if the ptr is in the next page so we can remove the node
		// easily if empty afterwards
		//ft_printf("Checking %p\n", page->start);
		if (ptr >= page->start && ptr <= page->start + type)
		{
			prev_mem = NULL;
			mem = page->mem;
			while (mem)
			{
				if (mem->start == ptr && page->used_space - mem->size - BLOCK_METADATA > PAGE_METADATA)
				{
					if (mem->used == 0)
					{
						custom_error("Error - Attempting double free on %p\n", ptr);
						return (1);
					}
					mem->used = 0;
					//ft_bzero(mem->start, mem->size);
					page->used_space -= mem->size + BLOCK_METADATA;
					// If the block after is free, merge with it
					if (mem->next && mem->next->used == 0)
					{
						// Add the addresses instead of the size
						// because of the alignment
						mem->size = (size_t)mem->next->start + mem->next->size - (size_t)mem->start;
						mem->next = mem->next->next;
						// Erase next node's metadata
						ft_bzero(mem->start, mem->size);
					}
					// If the block before is free, merge with it
					if (prev_mem && prev_mem->used == 0)
					{
						// Add the addresses instead of the size
						// because of the alignment
						prev_mem->size = (size_t)mem->start + mem->size - (size_t)prev_mem->start;
						prev_mem->next = mem->next;
						// Erase this node's metadata
						ft_bzero(prev_mem->start, prev_mem->size);
					}
					break ;
				}
				prev_mem = mem;
				mem = mem->next;
			}
			// If our plage is now empty, unmap it
			if (page->used_space <= PAGE_METADATA)
			{
				// Specific case if it's the first node
				if (prev == NULL)
				{
					if (type == TINY)
						g_memory.tiny = page->next;
					else if (type == SMALL)
						g_memory.small = page->next;
				}
				else
					prev->next = page->next;
				// Unmapping the actual memory
				//munmap(page, type);
			}
			return (1);
		}
		prev = page;
		page = page->next;
	}
	return (0);
}

void	free(void *ptr)
{
	//ft_printf("Freeing %p\n", ptr);
	//if (!ptr)
	//	show_alloc_mem_plus();
	//if ((size_t)ptr % (size_t)16 != 0)
			//custom_error("{red}FREE NOT ALIGNED!!{reset}\n");
	if (!ptr)
		return ;
	pthread_mutex_lock(&g_mutex);
	if (check_page(ptr, g_memory.tiny, TINY))
	{
		//ft_printf("Tiny free ok\n");
		pthread_mutex_unlock(&g_mutex);
		//show_alloc_mem_plus();
		return ;
	}
	if (check_page(ptr, g_memory.small, SMALL))
	{
		//ft_printf("Small free ok\n");
		pthread_mutex_unlock(&g_mutex);
		//show_alloc_mem();
		return ;
	}
	if (check_large_page(ptr, g_memory.large))
	{
		//ft_printf("Large free ok\n");
		pthread_mutex_unlock(&g_mutex);
		//show_alloc_mem();
		return ;
	}
	pthread_mutex_unlock(&g_mutex);
}
