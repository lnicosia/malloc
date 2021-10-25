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

void	new_block(t_malloc *mem, size_t alignment, size_t size)
{
	t_malloc	*new;
	void		*aligned_ptr;
	
	//ft_printf("New block\n");
	aligned_ptr = mem->start + size;
	if ((size_t)aligned_ptr % alignment != 0)
		aligned_ptr += alignment - (size_t)aligned_ptr % alignment;
	if ((size_t)aligned_ptr % alignment != 0)
		ft_printf("T'as foiré ton calcul connard\n");
	new = aligned_ptr + size;
	// Cast as void* so we add BLOCK_METADATA bytes
	// and not BLOCK_METADATA * sizeof(t_malloc)
	new->start = (void*)new + BLOCK_METADATA;
	new->size = (size_t)aligned_ptr - (size_t)mem->start
	+ mem->size - size - BLOCK_METADATA;
	if (size <= BLOCK_METADATA)
		return ;
	new->used = 0;
	new->next = mem->next;
	mem->size = size;
	mem->next = new;
}