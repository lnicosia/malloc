/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:41:12 by lnicosia          #+#    #+#             */
/*   Updated: 2021/06/25 19:38:15 by lnicosia         ###   ########.fr       */
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
		ft_printf("%p - %p : %d bytes\n", mem->start, mem->end, mem->size);
		mem = mem->next;
	}
}

void	show_alloc_mem(void)
{
	t_page	*page;
	size_t	i;

	ft_printf("%d tiny\n", g_memory.nb_tiny);
	ft_printf("%d small\n", g_memory.nb_small);
	ft_printf("%d large\n", g_memory.nb_large);
	page = g_memory.tiny;
	i = 0;
	while (i < g_memory.nb_tiny)
	{
		ft_printf("TINY : %p (%dB/%dB)\n", page->start,
		page->length, TINY);
		show_page_content(page);
		page = page->next;
		i++;
	}
}