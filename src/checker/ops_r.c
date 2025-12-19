/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_r.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:11:44 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/16 18:54:51 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	do_rx(t_stack **stack)
{
	t_stack	*last;

	if (!*stack || !(*stack)->next)
		return ;
	last = get_last(*stack);
	last->next = *stack;
	*stack = last->next->next;
	last->next->next = NULL;
}

void	do_ra(t_checker *d)
{
	do_rx(&d->stacka);
}

void	do_rb(t_checker *d)
{
	do_rx(&d->stackb);
}

void	do_rr(t_checker *d)
{
	do_rx(&d->stacka);
	do_rx(&d->stackb);
}
