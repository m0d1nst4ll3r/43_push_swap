/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:52:48 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 04:53:46 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solver.h"

static void	init_op(char *op_strings[N_OP], void (*op_funcs[N_OP])(t_solver *))
{
	op_strings[PA] = PA_STR;
	op_strings[PB] = PB_STR;
	op_strings[SA] = SA_STR;
	op_strings[SB] = SB_STR;
	op_strings[SB] = SS_STR;
	op_strings[RA] = RA_STR;
	op_strings[RB] = RB_STR;
	op_strings[RR] = RR_STR;
	op_strings[RRA] = RRA_STR;
	op_strings[RRB] = RRB_STR;
	op_strings[RRR] = RRR_STR;
	op_funcs[PA] = do_pa;
	op_funcs[PB] = do_pb;
	op_funcs[SA] = do_sa;
	op_funcs[SB] = do_sb;
	op_funcs[SS] = do_ss;
	op_funcs[RA] = do_ra;
	op_funcs[RB] = do_rb;
	op_funcs[RR] = do_rr;
	op_funcs[RRA] = do_rra;
	op_funcs[RRB] = do_rrb;
	op_funcs[RRR] = do_rrr;
}

static void	init_prog(t_solver *d, int ac, char **av)
{
	d->av = av;
	d->num_elem = ac - 1;
	init_op(d->op_strings, d->op_funcs);
	d->stacka = NULL;
	d->stackb = NULL;
	d->op_list = NULL;
	d->lis_sub = NULL;
	d->lis_len = malloc(sizeof(*d->lis_len) * d->num_elem);
	if (!d->lis_len)
		error_out(*d);
	d->lis_sub = malloc(sizeof(*d->lis_len) * d->num_elem);
	if (!d->lis_sub)
		error_out(*d);
}

// See header file for program steps
int	main(int ac, char **av)
{
	t_solver	data;

	if (ac < 2)
		return (0);
	init_prog(&data, ac, av);
	build_stack(&data);
	if (data.num_elem > 1 && is_reverse_sorted(data.stacka))
		do_op(&data, SA);
	write_lis(data);
	data.pivot = get_pivot(data.stacka, data.lis_len);
	push_ahead(&data);
	push_back(&data);
	final_rotate(&data);
	optimize_op_list(&data.op_list);
	print_op_list(data.op_list, data.op_strings);
}
