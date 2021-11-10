#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(const char *str)
{
	long	output;
	int		sign;

	output = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str < 14))
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		output = output * 10 + *str++ - '0';
	return ((int)(output * sign));
}

int	ft_atoi_maxint(const char *str)
{
	unsigned int	output;
	int				sign;
	int 			i;
	int				j;

	output = 0;
	sign = 1;
	i = 0;
	j = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] < 14))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j < 11)
	{
		output = output * 10 + str[i] - '0';
		i++;
	}
	if ((output > 2147483648 && sign < 0) || (output > 2147483647 && sign > 0)
			|| str[i] != '\0')
		return (1);
	return (0);
}

void	ft_bzero(void *dest, size_t n)

{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = 0;
		i++;
	}
}

void	ft_print_mass_a_b(int *A, int *B, int ac)
{
	int i;
	
	i = -1;
	printf ("A: ");
	while (++i < ac)
		printf ("%d ", A[i]);
	printf ("\n");
	i = -1;
	printf ("B: ");
	while (++i < ac)
		printf ("%d ", B[i]);
	printf ("\n");
}

// Commands---------------------------------------

void	ft_sa(int *A, int key, int *x_operations)
{
	int a;

	a = A[0];
	A[0] = A[1];
	A[1] = a;
	if (key)
		write(1, "sa\n", 3);
	*x_operations += 1;
}

void	ft_sb(int *B, int key, int *x_operations)
{
	int b;

	b = B[0];
	B[0] = B[1];
	B[1] = b;
	if (key)
		write(1, "sb\n", 3);
	*x_operations += 1;
}

void	ft_ss(int *A, int *B, int *x_operations)
{
	ft_sa(A, 0, x_operations);
	ft_sb(B, 0, x_operations);
	write(1, "ss\n", 3);
}

void	ft_pa(int *A, int *B, int ac, int *ac_a, int *ac_b, int *x_operations)
{
    if (B[0] != -1)
    {
        int    i;

        i = ac - 1;
        while (i)
        {
            A[i] = A[i - 1];
            i--;
        }
        A[0] = B[0];
        while (i < ac - 1 && B[i] != -1)
        {
            B[i] = B[i + 1];
            i++;
        }
        if (B[ac - 1] != -1)
          B[ac - 1] = -1;
		*ac_a += 1;
		*ac_b -= 1;
        write(1, "pa\n", 3);
		*x_operations += 1;
    }
}

void    ft_pb(int *A, int *B, int ac, int *ac_a, int *ac_b, int *x_operations)
{
    if (A[0] != -1)
    {
        int    i;

        i = ac - 1;
        while (i)
        {
            B[i] = B[i - 1];
            i--;
        }
        B[0] = A[0];
        while (i < ac - 1 && A[i] != -1)
        {
            A[i] = A[i + 1];
            i++;
        }
        if (A[ac - 1] != -1)
          A[ac - 1] = -1;
		*ac_a -= 1;
		*ac_b += 1;
        write(1, "pb\n", 3);
		*x_operations += 1;
    }
}

void	ft_ra(int *A, int ac_a, int key, int *x_operations)
{
	int a;
	int i;

	if (ac_a > 1)
	{
		i = -1;
		a = A[0];
		while (++i < ac_a - 1)
			A[i] = A[i + 1];
		A[i] = a;
	}
	if (key)
		write(1, "ra\n", 3);
	*x_operations += 1;
}

void	ft_rb(int *B, int ac_b, int key, int *x_operations)
{
	int b;
	int i;

	if (ac_b > 1)
	{
		i = -1;
		b = B[0];
		while (++i < ac_b - 1)
			B[i] = B[i + 1];
		B[i] = b;
	}
	if (key)
		write(1, "rb\n", 3);
	*x_operations += 1;
}

void	ft_rr(int *A, int *B, int ac_a, int ac_b, int *x_operations)
{
	ft_ra(A, ac_a, 0 ,x_operations);
	ft_rb(B, ac_b, 0, x_operations);
	write(1, "rr\n", 3);
}

void	ft_rra(int *A, int ac_a, int key, int *x_operations)
{
	int a;

	if (ac_a > 1)
	{
		a = A[ac_a - 1];
		while (--ac_a)
			A[ac_a] = A[ac_a - 1];
		A[0] = a;
	}
	if (key)
		write(1, "rra\n", 4);
	*x_operations += 1;
}

void	ft_rrb(int *B, int ac_b, int key, int *x_operations)
{
	int b;

	if (ac_b > 1)
	{
		b = B[ac_b - 1];
		while (ac_b--)
			B[ac_b] = B[ac_b - 1];
		B[0] = b;
	}
	if (key)
		write(1, "rrb\n", 4);
	*x_operations += 1;
}

void	ft_rrr(int *A, int *B, int ac_a, int ac_b, int *x_operations)
{
	ft_rra(A, ac_a, 0, x_operations);
	ft_rrb(B, ac_b, 0, x_operations);
	write(1, "rrr\n", 4);
}

// --------------------------------------------------

void	ft_find_zero(int *A, int *in_a, int ac_a)
{
	int i;

	i = -1;
	*in_a = 0;
	while(++i < ac_a)
	{
		if (A[i] == 0)
		{
			*in_a = i;
			return;
		}
	}
}

int		ft_finder_b(int *B, int x, int z, int *in_b, int ac_b)
{
	int start;
	int end;
	int index;

	*in_b = 0;
	index = 1;
	while (z - index > x)
	{
		start = 0;
		end = ac_b - 1;
		while (start <= end)
		{
			if (z - index == B[start])
			{
				*in_b = start;
				return (1);
			}
			else if (z - index == B[end])
			{
				*in_b = end;
				return (1);
			}
			start++;
			end--;
		}
		index++;
	}
	return (0);
}

int		ft_finder_b_to_up(int *B, int x, int z, int *in_b, int ac_b)
{
	int start;
	int end;
	int index;

	*in_b = 0;
	index = 1;
	while (x + index <= z)
	{
		start = 0;
		end = ac_b - 1;
		while (start <= end)
		{
			if (x + index == B[start])
			{
				*in_b = start;
				return (1);
			}
			else if (x + index == B[end])
			{
				*in_b = end;
				return (1);
			}
			start++;
			end--;
		}
		index++;
	}
	return (0);
}

void	ft_move(int *A, int ac, int index, int *x_operations)
{
	int	i;

	i = 0;
	while (A[i] != index)
		i++;
	if (i <= ac / 2)
		while (A[0] != index)
			ft_ra(A, ac, 1, x_operations);
	else
		while (A[0] != index)
			ft_rra(A, ac, 1, x_operations);
}

//-------------------------------------------------------------------------------
void 	ft_slide_rr(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int key, int *x_operations)
{
	if (key == 1)
		b_pos++;
	while (a_pos)
	{
		if (b_pos)
		{
			ft_rr(A, B, ac_a, ac_b, x_operations);
			b_pos--;
		}
		else
			ft_ra(A, ac_a, 1, x_operations);
		a_pos--;
	}
	while (b_pos)
	{
		ft_rb(B, ac_b, 1, x_operations);
		b_pos--;
	}
}

void 	ft_slide_rrr(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int key, int *x_operations)
{
	if (key == 1)
		b_pos++;
	while (a_pos < ac_a)
	{
		if (b_pos < ac_b)
		{
			ft_rrr(A, B, ac_a, ac_b, x_operations);
			b_pos++;
		}
		else
			ft_rra(A, ac_a, 1, x_operations);
		a_pos++;
	}
	while (b_pos < ac_b)
	{
		ft_rrb(B, ac_b, 1, x_operations);
		b_pos++;
	}
}

void 	ft_slide_ra_rrb(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int key, int *x_operations)
{
	if (key == 1)
		b_pos++;
	while (a_pos)
	{
		ft_ra(A, ac_a, 1, x_operations);
		a_pos--;
	}
	while (b_pos < ac_b)
	{
		ft_rrb(B, ac_b, 1, x_operations);
		b_pos++;
	}
}

void 	ft_slide_rra_rb(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int key, int *x_operations)
{
	if (key == 1)
		b_pos++;
	while (a_pos < ac_a)
	{
		ft_rra(A, ac_a, 1, x_operations);
		a_pos++;
	}
	while (b_pos)
	{
		ft_rb(B, ac_b, 1, x_operations);
		b_pos--;
	}
}

void	ft_slide_a_b(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int key, int *x_operations)
{
	if (key == 0)
	{
		if (a_pos <= ac_a / 2 && b_pos <= ac_b / 2)
			ft_slide_rr(A, B, a_pos, b_pos, ac_a, ac_b, 0, x_operations);
		else if (a_pos > ac_a / 2 && b_pos > ac_b / 2)
			ft_slide_rrr(A, B, a_pos, b_pos, ac_a, ac_b, 0, x_operations);
		else if (a_pos <= ac_a / 2 && b_pos > ac_b / 2)
			ft_slide_ra_rrb(A, B, a_pos, b_pos, ac_a, ac_b, 0,x_operations);
		else if (a_pos > ac_a / 2 && b_pos <= ac_b / 2)
			ft_slide_rra_rb(A, B, a_pos, b_pos, ac_a, ac_b, 0, x_operations);
	}
	else
	{
		if (a_pos <= ac_a / 2 && b_pos <= ac_b / 2)
			ft_slide_rr(A, B, a_pos, b_pos, ac_a, ac_b, 1, x_operations);
		else if (a_pos > ac_a / 2 && b_pos > ac_b / 2)
			ft_slide_rrr(A, B, a_pos, b_pos, ac_a, ac_b, 1, x_operations);
		else if (a_pos <= ac_a / 2 && b_pos > ac_b / 2)
			ft_slide_ra_rrb(A, B, a_pos, b_pos, ac_a, ac_b, 1,x_operations);
		else if (a_pos > ac_a / 2 && b_pos <= ac_b / 2)
			ft_slide_rra_rb(A, B, a_pos, b_pos, ac_a, ac_b, 1, x_operations);
	}
}

// ------------------------------------------------------------------------------

int		ft_stack_not_sorted(int *mass, int ac)
{
	int		i;

	i = -1;
	while (++i < ac - 1)
		if (!(mass[i] == mass[i + 1] - 1
			|| (mass[i] == ac - 1 && mass[i + 1] == 0)))
			return (1);
	return (0);
}

int		ft_stack_not_sorted_for_half_ac_a(int *mass, int ac)
{
	int		i;

	i = -1;
	while (++i < ac - 1)
		if (!(mass[i] == mass[i + 1] - 1
			|| (mass[i] == ac - 1 && mass[i + 1] == ac / 2)))
			return (1);
	return (0);
}

int		ft_diff_quaters(int x, int y, int ac)
{
	if ((x <= ac / 2 && y <= ac / 2)
			|| (x > ac / 2 && y > ac / 2))
		return (0);
	else if (x > ac / 2 && y <= ac / 2)
		if (x - y > ac / 2)
			return (-1);
		else
			return (1);
	else
		if (y - x <= ac / 2)
			return (0);
		else
			return (1);
}

int		ft_is_miss_counter_plus_minus(int *l, int *m, int *count_of_steps, int *i, int *ii, int *iii, int ac_a, int ac)
{
	while (*count_of_steps <= ac_a)
	{
		if (*count_of_steps % 2)
		{
			*i = *l;
			*ii = *l + 1;
			*iii = *l + 2;
			*l += 1;
		}
		else
		{
			*i = *m;
			*ii = *m - 1;
			*iii = *m - 2;
			*m -= 1;
		}
		*count_of_steps += 1;
		return (1);
	}
	return (0);
}

// int		ft_is_miss_counter_only_up(int *l, int *m, int *count_of_steps, int *i, int *ii, int *iii, int ac_a, int ac)
// {
// 	while (*count_of_steps <= ac_a)
// 	{
//         *i = *l;
//         *ii = *l + 1;
//         *iii = *l + 2;
// 		*l += 1;
// 		*count_of_steps += 1;
// 		return (1);
// 	}
// 	return (0);
// }

int		ft_is_miss_counter_only_down(int *l, int *m, int *count_of_steps, int *i, int *ii, int *iii, int ac_a, int ac)
{
	while (*count_of_steps <= ac_a)
	{
		if (*count_of_steps == 1)
		{
			*i = 0;
			*ii = *m;
			*iii = *m - 1;
		}
		else 
		{
			*i = *m;
			*ii = *m - 1;
			*iii = *m - 2;
			*m -= 1;
		}
		*count_of_steps += 1;
		return (1);
	}
	return (0);
}

// void	ft_sorted_massives(int *A, int *B, int *ac_a, int *ac_b, int ac, int *x_operations)
// {
// 	int a_not_sort;
// 	int b_not_sort;
// 	int i;
// 
// 	// if (ft_stack_not_sorted(A, *ac_a))
// 	// 	a_not_sort = 1;
// 	// if (ft_stack_not_sorted(B, *ac_b))
// 	// 	b_not_sort = 1;
// 	// if (a_not_sort)
// 	while (*ac_a > ac / 2)
// 	{
// 		i = 0;
// 		if (A[i] < ac / 2)
// 		{
// 			if (A[0] > A[1] && A[1] < ac / 2)
// 				ft_ra(A, *ac_a, 1, x_operations);
// 			ft_ra(A, *ac_a, 1, x_operations);
// 		}
// 		if (A[0] >= ac / 2)
// 			ft_pb(A, B, ac, ac_a, ac_b, x_operations);
// 		// ft_print_mass_a_b(A, B, ac);
// 	}
// }

// ------------------------------------------------------------------------------

// void	ft_is_missposition_to_up(int *A, int *B, int *ac_a, int *ac_b, int ac, int *x_operations)
// {
// 	int i;
// 	int ii;
// 	int	iii;
// 	int in_b;
//     ft_print_mass_a_b(A, B, ac);
//     if (A[*ac_a - 1] == ac - 1)
//         ii = -1;
//     else
//         ii = A[*ac_a - 1];
//     if (ft_finder_b(B, ii, ii + 2, &in_b, *ac_b))
//     {
//         ft_slide_a_b(A, B, 0, in_b, *ac_a, *ac_b, 0, x_operations);
//         ft_pa(A, B, ac, ac_a, ac_b, x_operations);
// 
//     }
//     else
//     {
//         while (A[0] != ii + 1)
//             ft_pb(A, B, ac, ac_a, ac_b, x_operations);
//     }
//     ft_print_mass_a_b(A, B, ac);
//     return;
// }

void	ft_is_missposition(int	*A, int *B, int *ac_a, int *ac_b, int ac, int *first, int *x_operations)
{
	int i;
	int ii;
	int	iii;
	int in_b;
	int	quat;
	int l;
	int m;
	int count_of_steps;
	int tmp;
	int tmp_last;

	l = 0;
	m = *ac_a - 1;
	count_of_steps = 1;
	tmp = A[ac / 2];
	tmp_last = A[ac - 1];
	i = 0;
	ii = ac - 1;
	// while (ft_is_miss_counter_plus_minus(&l, &m, &count_of_steps, &i, &ii, &iii, *ac_a, ac))
	ft_print_mass_a_b(A, B, ac);
	// if (!(A[i] + 1 == A[ii]  && i <= *ac_a / 2)
	// 		&& !(A[ii] == A[i] - 1  && i > *ac_a / 2)
	// 		&& !(A[i] == ac - 1 && A[ii] == 0 && i <= *ac_a / 2)
	// 		&& !(A[ii] == ac - 1 && A[i] == 0 && i > *ac_a / 2))
	while (A[i] != tmp)
	{
		if (!ft_stack_not_sorted(A, ac))
			return;
		ft_print_mass_a_b(A, B, ac);
		if (A[i] < tmp)
		{
			if (A[i + 1] < tmp)
			{
				if (A[i] > A[i + 1])
				{
					if (A[i] - A[i + 1] < 10)
					{
						ft_slide_a_b(A, B, i, 0, *ac_a, *ac_b, 0, x_operations);
						ft_sa(A, 1, x_operations);
					}
					else
					{
						ft_slide_a_b(A, B, i, 0, *ac_a, *ac_b, 0, x_operations);
						ft_pb(A, B, ac, ac_a, ac_b, x_operations);
					}
					i = -1;
				}
				else
				{
					if (ft_finder_b(B, -1, A[i], &in_b, *ac_b))
					{
						ft_slide_a_b(A, B, i, in_b, *ac_a, *ac_b, 0, x_operations);
						ft_pa(A, B, ac, ac_a, ac_b, x_operations);
						i = -1;
					}
					else if (ft_finder_b(B, A[i], A[i + 1], &in_b, *ac_b))
					{
						ft_slide_a_b(A, B, i + 1, in_b, *ac_a, *ac_b, 0, x_operations);
						ft_pa(A, B, ac, ac_a, ac_b, x_operations);
						i = -1;
					}
				}
			}
			else if (A[i + 1] != tmp)
			{
				ft_slide_a_b(A, B, i + 1, 0, *ac_a, *ac_b, 0, x_operations);
				ft_pb(A, B, ac, ac_a, ac_b, x_operations);
				i = -1;
			}
		}
		else
		{
			ft_slide_a_b(A, B, i, 0, *ac_a, *ac_b, 0, x_operations);
			ft_pb(A, B, ac, ac_a, ac_b, x_operations);
			i = -1;
		}
		count_of_steps++;
		i++;
	}
	i++;
	count_of_steps++;
	while (A[i] != tmp_last || A[i] == tmp_last)
	{
		if (!ft_stack_not_sorted(A, ac))
			return;
		ft_print_mass_a_b(A, B, ac);
		if (A[i] == tmp_last)
		{
			if (A[i] < tmp)
			{
				ft_slide_a_b(A, B, i, in_b, *ac_a, *ac_b, 0, x_operations);
				ft_pb(A, B, ac, ac_a, ac_b, x_operations);
				return;
			}
			if (ft_finder_b(B, tmp, A[i], &in_b, *ac_b))
			{
				ft_slide_a_b(A, B, i, in_b, *ac_a, *ac_b, 0, x_operations);
				ft_pa(A, B, ac, ac_a, ac_b, x_operations);
				i = -1;
			}
			else if (ft_finder_b(B, A[i], ac, &in_b, *ac_b))
			{
				ft_slide_a_b(A, B, i + 1, in_b, *ac_a, *ac_b, 0, x_operations);
				ft_pa(A, B, ac, ac_a, ac_b, x_operations);
				tmp_last = A[0];
				i = -1;
			}
			else
			{
				ft_slide_a_b(A, B, i + 1, in_b, *ac_a, *ac_b, 0, x_operations);
				return;
			}	
		}
		else if (A[i] > tmp)
		{
			if (A[i + 1] > tmp)
			{
				if (A[i] > A[i + 1])
				{
					ft_slide_a_b(A, B, i, 0, *ac_a, *ac_b, 0, x_operations);
					ft_sa(A, 1, x_operations);
					i = -1;
				}
				else
				{
					if (ft_finder_b(B, tmp, A[i], &in_b, *ac_b))
					{
						ft_slide_a_b(A, B, i, in_b, *ac_a, *ac_b, 0, x_operations);
						ft_pa(A, B, ac, ac_a, ac_b, x_operations);
						i = -1;
					}
					else if (ft_finder_b(B, A[i], A[i + 1], &in_b, *ac_b))
					{
						ft_slide_a_b(A, B, i + 1, in_b, *ac_a, *ac_b, 0, x_operations);
						ft_pa(A, B, ac, ac_a, ac_b, x_operations);
						i = -1;
					}
				}
			}
			else
			{
				ft_slide_a_b(A, B, i + 1, 0, *ac_a, *ac_b, 0, x_operations);
				ft_pb(A, B, ac, ac_a, ac_b, x_operations);
				i = -1;
			}
		}
		else
		{
			ft_slide_a_b(A, B, i, 0, *ac_a, *ac_b, 0, x_operations);
			ft_pb(A, B, ac, ac_a, ac_b, x_operations);
			i = -1;
		}
		i++;
		count_of_steps++;
	}
}

// void	ft_is_missposition_over(int	*A, int *B, int *ac_a, int *ac_b, int ac, int *ac_tmp_for_a, int *x_operations)
// {
// 	int i;
// 	int ii;
// 	int	iii;
// 	int	in_a;
// 	int in_b;
// 	int	quat;
// 	int l;
// 	int m;
// 	int count_of_steps;
// 	int *ac_tmp;
// 
// 	l = 0;
// 	m = *ac_a - 1;
// 	count_of_steps = 1;
// 	ac_tmp = ac_tmp_for_a;
// 	if (ft_stack_not_sorted(A, *ac_a) && !(*ac_a > 6 && ac > 11) && *ac_a > *ac_tmp / 2)
// 	{
// 		if (*ac_a == *ac_tmp / 2)
// 			*ac_tmp /= 2;
// 		while (ft_is_miss_counter(&l, &m, &count_of_steps, &i, &ii, &iii, *ac_a, *ac_tmp_for_a))
// 		{
// 			if (!(A[i] < A[ii] && (A[i] < *ac_tmp / 2 && A[ii] < *ac_tmp / 2)))
// 			{
// 				if (A[i] > A[ii] && (A[i] < *ac_tmp / 2 && A[ii] < *ac_tmp / 2))
// 				{
// 					ft_slide_a_b(A, B, i, 0, *ac_a, *ac_b, 0, x_operations);
// 					ft_sa(A, 1, x_operations);
// 					return;
// 				}
// 				if (A[i] >= *ac_tmp / 2)
// 				{
// 					if (ft_finder_b_to_up(B, A[i], *ac_tmp, &in_b, *ac_b))
// 						ft_slide_a_b(A, B, i, in_b, *ac_a, *ac_b, 1, x_operations);
// 					else if (ft_finder_b(B, (*ac_tmp / 2), A[i], &in_b, *ac_b))
// 						ft_slide_a_b(A, B, i, in_b, *ac_a, *ac_b, 0, x_operations);
// 					ft_pb(A, B, ac, ac_a, ac_b, x_operations);
// 					return;
// 				}
// 				if (A[ii] >= *ac_tmp / 2)
// 				{
// 					if (ft_finder_b_to_up(B, A[ii], *ac_tmp, &in_b, *ac_b))
// 						ft_slide_a_b(A, B, ii, in_b, *ac_a, *ac_b, 1, x_operations);
// 					else if (ft_finder_b(B, (*ac_tmp / 2), A[ii], &in_b, *ac_b))
// 						ft_slide_a_b(A, B, ii, in_b, *ac_a, *ac_b, 0, x_operations);
// 					ft_pb(A, B, ac, ac_a, ac_b, x_operations);
// 					return;
// 				}
// 			}
// 		}
// 	}
// 	else if (ft_stack_not_sorted(A, *ac_a))
// 	{
// 		while (ft_is_miss_counter(&l, &m, &count_of_steps, &i, &ii, &iii, *ac_a, *ac_tmp_for_a))
// 		{
// 			if (!(A[i] < A[ii]) && !(A[i] == *ac_a - 1 && A[ii] == 0))
// 			{
// 				ft_slide_a_b(A, B, i, 0, *ac_a, *ac_b, 0, x_operations);
// 				ft_sa(A, 1, x_operations);
// 				return;
// 			}
// 		}
// 	}
// 	else
// 	{
// 		if (ft_finder_b(B, ac - 2, ac, &in_b, *ac_b))
// 			ft_find_zero(A, &in_a, *ac_a);
// 		ft_slide_a_b(A, B, in_a, in_b, *ac_a, *ac_b, 0, x_operations);
// 		while (*ac_b)
// 			ft_pa(A, B, ac, ac_a, ac_b, x_operations);
// 	}
// 
// }
// ------------------------------------------------------------------------------

void	ft_first_last(int *A, int ac)
{
	int i;
	int j;
	int first;
	int second;
	int last;
	int *tmp;

	tmp = malloc(sizeof(int) * ac);
	i = 1;
	first = A[0];
	last = A[0];
	while (i < ac)
	{
		if (A[i] < first)
			first = A[i];
		else if (A[i] > last)
			last = A[i];
		i++;
	}
	j = 0;
	while (j < ac)
	{
		i = 0;
		second = last;
		while (i < ac)
		{
			if (A[i] > first && A[i] < second)
				second = A[i];
			if (A[i] == first)
				tmp[i] = j;
			i++;
		}
		j++;
		first = second;
	}
	i = -1;
	while (++i < ac)
		A[i] = tmp[i];
	free(tmp);
}

int		ft_chk_positions(int *A, int ac)
{
	int i;

	i = -1;
	while (++i < ac)
		if (A[i] != i)
			return (1);
	return(0);
}


int		ft_chk_dup(int *A, int ac)
{
	int i;
	int j;

	i = -1;
	while (++i < ac - 1)
	{
		j = i;
		while (++j < ac)
			if (A[i] == A[j])
				return (1);
	}
	return(0);
}

int		ft_sw_pu(int *A, int *B, int ac)
{
	int x_operations;
	int	ac_a;
	int	ac_b;
    int first;

	ac_a = ac;
	ac_b = 0;
	x_operations = 0;
    first = 0;
	if (ft_chk_dup(A, ac))
		return (1);
	ft_first_last(A, ac);
	// ft_sorted_massives(A, B, &ac_a, &ac_b, ac, &x_operations); // --------------
	while (ft_stack_not_sorted(A, ac))
	{
		ft_is_missposition(A, B, &ac_a, &ac_b, ac, &first, &x_operations);
		// else
		// 	ft_is_missposition_over(A, B, &ac_a, &ac_b, ac, &ac_tmp_for_a, &x_operations);
		// ft_print_mass_a_b(A, B, ac);
	}
    if (ft_chk_positions(A, ac))
        ft_move(A, ac, 0, &x_operations);
    printf("*x_operations: %d\n", x_operations);
	return (0);
}

//--------------------------------------------------

int		ft_intmax_chk(char **av, int ac)
{
	int i;
	int chk;

	chk = 0;
	i = -1;
	while (++i < ac && !chk)
		chk = ft_atoi_maxint(av[i + 1]);
	if (chk)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	int 	i;
	int 	*A;
	int		*B;

	ac--;
	if (ft_intmax_chk(av, ac))
	{
		write (1, "Error\n", 6);
		return (0);
	}
	A = malloc(sizeof(int) * ac);
	B = malloc(sizeof(int) * ac);
	i = -1;
	while (++i < ac)
	{
		B[i] = -1;
		A[i] = ft_atoi(av[i + 1]);
	}
	// start
	if (ft_sw_pu(A, B, ac))
	{
		write (1, "Error\n", 6);
		return (0);
	}
	// finish
	if (!ft_stack_not_sorted(A, ac))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	ft_print_mass_a_b(A, B, ac);
}
