#include "../../includes/mini_shell.h"

void	init_split_info(t_split *split_info)
{
	split_info->i = 0;
	split_info->array_index = 0;
	split_info->len = 0;
	split_info->brk_flg = 1;
	split_info->k = 0;
	split_info->j = 0;
}
