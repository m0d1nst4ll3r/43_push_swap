/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 16:04:54 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/22 16:55:16 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

static void	init_prog(t_checker *d)
{
	d->stacka = NULL;
	d->stackb = NULL;
	d->op = NULL;
	d->ops[0] = do_sa;
	d->ops[1] = do_sb;
	d->ops[2] = do_ss;
	d->ops[3] = do_ra;
	d->ops[4] = do_rb;
	d->ops[5] = do_rr;
	d->ops[6] = do_rra;
	d->ops[7] = do_rrb;
	d->ops[8] = do_rrr;
	d->ops[9] = do_pa;
	d->ops[10] = do_pb;
	d->op_list[0] = SA;
	d->op_list[1] = SB;
	d->op_list[2] = SS;
	d->op_list[3] = RA;
	d->op_list[4] = RB;
	d->op_list[5] = RR;
	d->op_list[6] = RRA;
	d->op_list[7] = RRB;
	d->op_list[8] = RRR;
	d->op_list[9] = PA;
	d->op_list[10] = PB;
}

int	main(int ac, char **av)
{
	t_checker	d;

	if (ac < 2)
		return (0);
	init_prog(&d);
	if (build_stack(&d.stacka, av))
		error_out(d);
	if (check_duplicates(d.stacka))
		error_out(d);
	if (read_input(&d.op, d.op_list))
		error_out(d);
	apply_input(&d);
	if (d.stackb || !is_sorted(d.stacka))
		ft_printf(KO);
	else
		ft_printf(OK);
	exit_prog(d, 0);
}
