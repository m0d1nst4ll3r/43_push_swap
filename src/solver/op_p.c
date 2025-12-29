/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_p.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:10:49 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/22 22:00:27 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	do_px(t_stack **stack_from, t_stack **stack_to)
{
	t_stack	*elem;

	if (!*stack_from)
		return ;
	elem = stack_unlink(stack_from);
	stack_add_front(stack_to, elem);
}

void	do_pa(t_solver *d)
{
	add_op(d, PA_KEY);
	do_px(&d->stackb, &d->stacka);
}

void	do_pb(t_solver *d)
{
	add_op(d, PB_KEY);
	do_px(&d->stacka, &d->stackb);
}
