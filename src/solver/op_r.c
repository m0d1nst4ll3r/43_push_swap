/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:11:44 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/30 16:44:21 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	do_rx(t_stack **head)
{
	if (!*head || !(*head)->next)
		return ;
	*head = (*head)->next;
}

void	do_ra(t_solver *d)
{
	add_op(d, RA);
	do_rx(&d->stacka);
}

void	do_rb(t_solver *d)
{
	add_op(d, RB);
	do_rx(&d->stackb);
}

void	do_rr(t_solver *d)
{
	add_op(d, RR);
	do_rx(&d->stacka);
	do_rx(&d->stackb);
}
