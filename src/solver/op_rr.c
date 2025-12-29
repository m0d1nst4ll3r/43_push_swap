/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:07:51 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/23 09:45:19 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	do_rrx(t_stack **head)
{
	if (!*head || !(*head)->next)
		return ;
	*head = (*head)->prev;
}

void	do_rra(t_solver *d)
{
	add_op(d, RRA_KEY);
	do_rrx(&d->stacka);
}

void	do_rrb(t_solver *d)
{
	add_op(d, RRB_KEY);
	do_rrx(&d->stackb);
}

void	do_rrr(t_solver *d)
{
	add_op(d, RRR_KEY);
	do_rrx(&d->stacka);
	do_rrx(&d->stackb);
}
