/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 11:22:54 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/30 16:05:09 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

void	add_op(t_solver *d, unsigned char op)
{
	t_op	*new;

	new = malloc(sizeof(*new));
	if (!new)
		error_out(*d);
	new->next = NULL;
	new->prev = NULL;
	new->op = op;
	if (!d->op_list)
		d->op_list = new;
	else
	{
		d->last_op->next = new;
		new->prev = d->last_op;
	}
	d->last_op = new;
}

void	print_op_list(t_op *list, char *op_strings[N_OP])
{
	while (list)
	{
		ft_printf("%s\n", op_strings[list->op]);
		list = list->next;
	}
}
