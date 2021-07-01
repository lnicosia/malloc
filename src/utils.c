/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 11:44:20 by lnicosia          #+#    #+#             */
/*   Updated: 2021/07/01 13:58:49 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libft.h"

void	new_block(t_malloc *mem, size_t size)
{
	t_malloc	*new;
	
	new = mem->start + size;
	// Cast as void* so we add BLOCK_METADATA bytes
	// and not BLOCK_METADATA * sizeof(t_malloc)
	new->start = (void*)new + BLOCK_METADATA;
	new->size = mem->size - size - BLOCK_METADATA;
	new->used = 0;
	new->next = mem->next;
	mem->size = size;
	mem->next = new;
}