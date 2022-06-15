/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:44:20 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/13 17:17:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

int		is_power_of_two(size_t nb)
{
	return (nb != 0 && (nb & (nb - 1)) == 0);
}

int		new_block(t_malloc *mem, size_t alignment, size_t size)
{
	t_malloc	*new;
	void		*aligned_ptr;

	//ft_printf("New block\n");
	//ft_printf("Size = %ld (0x%X)\n", size, size);
	aligned_ptr = mem->start + size;
	//ft_printf("at pos %p\n", aligned_ptr);
	if ((size_t)aligned_ptr % alignment != 0)
		aligned_ptr += alignment - (size_t)aligned_ptr % alignment;
	new = aligned_ptr;
	// Cast as void* so we add BLOCK_METADATA bytes
	// and not BLOCK_METADATA * sizeof(t_malloc)
	new->start = (void*)new + BLOCK_METADATA;
	//ft_printf("new = %p\n", new->start);
	ssize_t next_size;
	if (mem->next)
		next_size = (ssize_t)mem->next - (ssize_t)new->start;
	else
		next_size = (ssize_t)mem->size - ((ssize_t)new->start - (ssize_t)mem->start);
	//ft_printf("new size = %ld\n", new->size);
	if (next_size <= (ssize_t)BLOCK_METADATA)
		//ft_printf("Not enough space\n");
		return (1);
	new->size = (size_t)next_size;
	new->used = 0;
	new->next = mem->next;
	mem->size = size;
	mem->next = new;
	return (0);
}
