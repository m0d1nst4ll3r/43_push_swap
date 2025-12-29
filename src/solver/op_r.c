/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:11:44 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/23 09:45:06 by rapohlen         ###   ########.fr       */
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
	add_op(d, RA_KEY);
	do_rx(&d->stacka);
}

void	do_rb(t_solver *d)
{
	add_op(d, RB_KEY);
	do_rx(&d->stackb);
}

void	do_rr(t_solver *d)
{
	add_op(d, RR_KEY);
	do_rx(&d->stacka);
	do_rx(&d->stackb);
}
