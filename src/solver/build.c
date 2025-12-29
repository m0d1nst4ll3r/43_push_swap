/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:48:42 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/23 09:47:27 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void	build_stack(t_solver *d)
{
	int		i;
	int		val;
	t_stack	*new;

	i = 1;
	while (d->av[i])
	{
		if (ft_atoi_strict(d->av[i], &val))
			error_out(*d);
		new = stack_new(val);
		if (!new)
			error_out(*d);
		stack_add_back(&d->stacka, new);
		i++;
	}
}
