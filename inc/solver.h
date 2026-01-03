/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 14:53:10 by rapohlen          #+#    #+#             */
/*   Updated: 2025/12/30 16:42:40 by rapohlen         ###   ########.fr       */
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

#include <stdbool.h>
#include "libft.h"

/*	PuSH_SWaP - v1
 *
 *	Program steps:
 *
 * Note: every operation that we make is not directly printed but instead
 *  added to a list which will be optimized once at the end (e.g transform
 *  ra rb to rr, or remove consecutive pa pb).
 *
 * 0. Init values:
 *		a. All 3 lists to NULL
 *		b. val_arr and lis_arr malloc'd to argc - 1
 *		c. op_keys and op_funcs to defined keys and their funcs
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
 *		a. If value > pivot, pb
 *		b. Else, pb + rb
 * 4. Push back to A
 *		a. Figure out the lowest-cost value from B to push to A, push it
 *	  See push-back section for explanations. Note that it is possible to
 *	   optimize by simulating moves in advance, but for now we do it naively
 * 5. Rotate A back into place
 *		a. B is empty and A is sorted, but we are not done
 * 6. Optimize op list
 *		a. ra rb transformed to rr
 *		b. same for rrr
 *		c. consecutive pa pb removed
 *	  Normally we should already have optimized ra rb, etc... but we make a
 *	   last pass just in case
 * 7. Print operations, free all, exit
 *
 * Done!
*/

/*	Push back explanation
 *
 * We want to push values from B to A, but we want to do it efficiently
 * To do so, we calculate the amount of operations that each value requires to
 *	be placed at the right spot in A, and will move the value with the lowest
 *	cost
 * We do not calculate all the costs for all the values, e.g a value already
 *	5 spots away from the top of B (cost of 5 rotations + 1 push) can never beat
 *	a 4-cost value
 *
 * The cost calculation goes like this:
 *	- At least 1 operation is always needed (pa)
 *	- How far is the value from the top of stack B? Both ways (for rr, rrr)
 *	- How far is the value right after it from the top of stack A? Both ways
 *	- How many operations as a result? Same-way rotations can be merged
 * Then, compare that value to the lowest cost found thus far
 * If cost is 1 (can just pa), do it right away
 * If value is so far from the top of B that it can't beat the lowest cost,
 *	give up (we proceed incrementally, both ways at once e.g 1 down, 1 up,
 *	2 down, 2 up, 3 down, 3 up etc...)
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
 * op_strings	contains ordered strings of operations
 * op_funcs		contains ordered functions of operations
 * stacka		-
 * stackb		-
 * op_list		list of operations (e.g sa, pb, ra) printed at the end
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

// stack_util.c
t_stack *stack_new(int val);
void	stack_add_front(t_stack **head, t_stack *elem);
void	stack_add_back(t_stack **head, t_stack *elem);
t_stack	*stack_unlink(t_stack **head);

// util.c
int		bsearch_higher(int *arr, int len, int val);
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

// build.c
void	build_stack(t_solver *d);

// lis.c
void	write_lis(t_solver *d);

// ?
// also may need a sub-func given complexity
int		get_pivot(t_solver *d); // 4th
void	push_non_lis(t_solver *d); // 5th
void	push_back(t_solver *d); // 6th, extremely complex, needs a ton of sub funcs
void	rotate_into_order(t_solver *d); // 7th, easy


// exit.c
void	exit_prog(t_solver d, unsigned char retval);
void	error_out(t_solver d);

#endif
