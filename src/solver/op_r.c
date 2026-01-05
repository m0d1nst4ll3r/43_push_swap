/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_r.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:11:44 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/05 19:50:52 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static int	do_rx(t_stack **head)
{
	if (!*head || (*head)->next == *head)
		return (0);
	*head = (*head)->next;
	return (1);
}

void	do_ra(t_solver *d)
{
	if (do_rx(&d->stacka))
		add_op(d, RA);
}

void	do_rb(t_solver *d)
{
	if (do_rx(&d->stackb))
		add_op(d, RB);
}

// Reminder: we will optimize op list anyway, it's fine not to write RR yet
void	do_rr(t_solver *d)
{
	do_ra(d);
	do_rb(d);
}
