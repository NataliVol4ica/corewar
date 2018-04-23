/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_store.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:29:56 by nkolosov          #+#    #+#             */
/*   Updated: 2018/03/19 14:29:57 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

extern t_global	g_g;

void			proc_store(void *data)
{
	t_process	*proc;
	t_codes		cod_b;
	int			toskip;
	int			arg[2];

	toskip = COMMAND;
	proc = (t_process*)data;
	cod_b = coding_byte(proc->pc + toskip);
	toskip += CODING_BYTE;
	//ft_printf("field %#x : %b %b %b\n", get_field_val(proc->pc), cod_b.t[0], cod_b.t[1], cod_b.t[2]);
	if (cod_b.t[0] != TREG || (cod_b.t[1] != TREG && cod_b.t[1] != TIND))
	{
		print_move(proc, count_total_skip(cod_b, 1, 2, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 2, proc->label_size));
		return ;
	}
	if (!parse_arg(cod_b.t[0], proc, &arg[0], &toskip) ||
		!parse_arg(cod_b.t[1], proc, &arg[1], &toskip))
	{
		print_move(proc, count_total_skip(cod_b, 1, 2, proc->label_size));
		proc->pc = set_pos(proc->pc + count_total_skip(cod_b, 1, 2, proc->label_size));
		return ;
	}
	//ft_printf("P%5d | st r%d ", proc->secret_num + 1, arg[0]);
	if (cod_b.t[1] == TREG)
	{
	//	ft_printf("r%d\n", arg[1]);
		proc->registry[arg[1]] = proc->registry[arg[0]];
	}
	else
	{
	//	ft_printf("%d\n", arg[1]);
		set_int(proc->pc + ((short)(arg[1]) % IDX_MOD), 4, proc->registry[arg[0]], proc->index);
	}
	print_move(proc, toskip);
	proc->pc = set_pos(proc->pc + toskip);
}
