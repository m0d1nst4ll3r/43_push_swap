/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:57:51 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/30 15:30:41 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	do_sx(t_stack **head)
{
	t_stack	*tmp;

	if (!*head || (*head)->next == *head)
		return ;
	tmp = (*head)->next;
	if ((*head)->next != (*head)->prev)
	{
		(*head)->next->next->prev = *head;
		(*head)->prev->next = (*head)->next;
		(*head)->next->prev = (*head)->prev;
		(*head)->prev = (*head)->next;
		(*head)->next = (*head)->next->next;
		tmp->next = *head;
	}
	*head = tmp;
}

void	do_sa(t_solver *d)
{
	add_op(d, SA_KEY);
	do_sx(&d->stacka);
}

void	do_sb(t_solver *d)
{
	add_op(d, SB_KEY);
	do_sx(&d->stackb);
}

void	do_ss(t_solver *d)
{
	add_op(d, SS_KEY);
	do_sx(&d->stacka);
	do_sx(&d->stackb);
}
