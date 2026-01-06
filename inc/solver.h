/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:53:10 by rapohlen          #+#    #+#             */
/*   Updated: 2026/01/06 15:06:09 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVER_H
# define SOLVER_H

# define PA_STR		"pa"
# define PB_STR		"pb"
# define SA_STR		"sa"
# define SB_STR		"sb"
# define SS_STR		"ss"
# define RA_STR		"ra"
# define RB_STR		"rb"
# define RR_STR		"rr"
# define RRA_STR	"rra"
# define RRB_STR	"rrb"
# define RRR_STR	"rrr"
# define PA			0
# define PB			1
# define SA			2
# define SB			3
# define SS			4
# define RA			5
# define RB			6
# define RR			7
# define RRA		8
# define RRB		9
# define RRR		10
# define N_OP		11
# define ERROR		"Error\n"
# define A			0
# define B			1

# include <stdbool.h>
# include "libft.h"

/*	PuSH_SWaP - v1
 *
 *	Program steps:
 *
 * Note: Every operation that we make is not directly printed but instead
 *  added to a list which will be optimized once at the end (e.g transform
 *  ra rb to rr, or remove consecutive pa pb).
 *		 Additionally, op functions have guardrails built into them, e.g
 *	requesting a "rb" when stack b is empty or has only 1 element does NOT
 *	write "rb" into the op list.
 *
 * 0. Init values:
 *		a. All 3 lists to NULL
 *		b. lis_len and lis_sub malloc'd to num_elem (argc - 1)
 *		c. op_strings and op_funcs to defined strings and their funcs
 * 1. Build stack A
 *		a. Read argv in loop, build stack
 *			(an invalid argument causes program exit and "Error" print)
 *		b. Check if stack is reverse-sorted, if so, do a "sa"
 *		   This tiny optimization gains enough ops to pass checks
 * 2. Calculate LIS and pivot
 *		a. Figure out where in stack A the longest LIS starts
 *		b. Using the address from step a, build the LIS and write it in stack A
 *		c. Build a non-LIS array, sort it and write the pivot value
 * 3. Push non-LIS values to B
 *		a. If value >= pivot, pb
 *		b. Else, pb + rb
 * 4. Push back to A
 *		a. Figure out the lowest-cost value from B to push to A, push it
 *		   See push_back c file for explanations
 * 5. Rotate A back into place
 *		a. B is empty and A is sorted, but we are not done
 * 6. Optimize op list
 *		a. Consecutive pa pb, sa sa, ra rra, etc... removed
 *		b. Consecutive ra rb transformed to rr, etc... rrr, ss
 *	  This allows us to simplify earlier code and avoid unnecessary complexity
 *	  Optimizations are done here rather than when writing operations in
 * 7. Print operations, free all, exit
*/

/*	Stack list: circular, two-way
 *
 * next, prev	list links
 * val			integer value
 * lis			whether value is part of longest increasing subsequence
 *				if it is, it will stay in A
*/
typedef struct s_stack
{
	struct s_stack	*next;
	struct s_stack	*prev;
	int				val;
	bool			lis;
}	t_stack;

/*	Op list: two-way
 *
 * next			list link
 * op			operation key (e.g 0, 1, 2) used with op_funcs/op_strings arrays
*/
typedef struct s_op
{
	struct s_op		*next;
	struct s_op		*prev;
	unsigned char	op;
}	t_op;

/*	Main program structure:
 *
 * av			-
 * num_elem		number of elems to sort (ac - 1)
 * pivot		middle value out of all values in stack B, used to pre-sort B
 * lis_len		used for calculating LIS (storing LIS len values)
 *				also re-used for calculating pivot
 * lis_sub		used for calculating LIS (storing subsequence indexes)
 * op_strings	contains ordered operation strings
 * op_funcs		contains ordered oepration functions
 * stacka		-
 * stackb		-
 * op_list		list of operations (e.g sa, pb, ra) to be printed at the end
 * last_op		last member of op_list, to avoid wasted instructions
*/
typedef struct s_solver
{
	char	**av;
	int		num_elem;
	int		pivot;
	int		*lis_len;
	int		*lis_sub;
	char	*op_strings[N_OP];
	void	(*op_funcs[N_OP])(struct s_solver *);
	t_stack	*stacka;
	t_stack	*stackb;
	t_op	*op_list;
	t_op	*last_op;
}	t_solver;

// util.c
int		bsearch_higher(int *arr, int len, int val);
void	fill_int_array(int *arr, int len, int val);

// stack_util.c
t_stack	*stack_new(int val);
void	stack_add_front(t_stack **head, t_stack *elem);
void	stack_add_back(t_stack **head, t_stack *elem);
t_stack	*stack_unlink(t_stack **head);
int		is_reverse_sorted(t_stack *head);

// op_util.c
void	add_op(t_solver *d, unsigned char op);
void	print_op_list(t_op *list, char *op_strings[N_OP]);

// op_timize.c
void	optimize_op_list(t_op **op_list);

// op_p.c
// op_r.c
// op_rr.c
// op_s.c
// op.c
void	do_sa(t_solver *d);
void	do_sb(t_solver *d);
void	do_ss(t_solver *d);
void	do_ra(t_solver *d);
void	do_rb(t_solver *d);
void	do_rr(t_solver *d);
void	do_rra(t_solver *d);
void	do_rrb(t_solver *d);
void	do_rrr(t_solver *d);
void	do_pa(t_solver *d);
void	do_pb(t_solver *d);
void	do_op(t_solver *d, char op);

// build.c
void	build_stack(t_solver *d);

// lis_get.c
// lis_write.c
// lis.c
t_stack	*get_lis_addr(t_stack *head, int *arr);
void	get_lis_values(t_solver d, t_stack *head);
void	write_boolean_flags(t_stack *head, int *lis_len, int *lis_sub,
			int num_elem);
void	write_lis(t_solver d);

// pivot.c
int		get_pivot(t_stack *head, int *arr);

// push_ahead.c
void	push_ahead(t_solver *d);

// push_back_cost.c
// push_back.c
void	compute_next_move(t_stack *stacka, t_stack *stackb, int *len, int *rot);
void	push_back(t_solver *d);

// final_rotate.c
void	final_rotate(t_solver *d);

// exit.c
void	exit_prog(t_solver d, unsigned char retval);
void	error_out(t_solver d);

#endif
