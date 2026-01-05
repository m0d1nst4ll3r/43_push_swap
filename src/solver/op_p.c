/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:10:49 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/05 19:53:57 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	do_px(t_stack **stack_from, t_stack **stack_to)
{
	t_stack	*elem;

	if (!*stack_from)
		return (0);
	elem = stack_unlink(stack_from);
	stack_add_front(stack_to, elem);
	return (1);
}

void	do_pa(t_solver *d)
{
	if (do_px(&d->stackb, &d->stacka))
		add_op(d, PA);
}

void	do_pb(t_solver *d)
{
	if (do_px(&d->stacka, &d->stackb))
		add_op(d, PB);
}
