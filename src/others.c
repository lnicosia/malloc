/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <lnicosia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 10:04:47 by lnicosia          #+#    #+#             */
/*   Updated: 2022/06/13 16:20:28 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>

#include "malloc.h"
#include "libft.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	if (nmemb == 0 || size == 0 || nmemb * size >= INT_MAX)
		return (NULL);
	if (!(ptr = malloc(nmemb * size)))
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

int		posix_memalign(void **memptr, size_t alignment, size_t size)
{
	if (alignment % sizeof(void*) != 0 || !is_power_of_two(alignment))
		return (EINVAL);
	if (!(*memptr = memalign(alignment, size)))
		return (ENOMEM);
	return (0);
}

void	*aligned_alloc(size_t alignment, size_t size)
{
	if (size % alignment != 0)
		return (0);
	return (memalign(alignment, size));
}

void	*valloc(size_t size)
{
	return (memalign((size_t)getpagesize(), size));
}


void	*pvalloc(size_t size)
{
	if ((size_t)size % (size_t)getpagesize() != 0)
		size += (size_t)getpagesize() - (size_t)size % (size_t)getpagesize();
	return (memalign((size_t)getpagesize(), size));
}
