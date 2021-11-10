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

// Commands---------------------------------------

void	ft_sa(int *A, int key)
{
	int a;

	a = A[0];
	A[0] = A[1];
	A[1] = a;
	if (key)
		write(1, "sa\n", 3);
}

void	ft_sb(int *B, int key)
{
	int b;

	b = B[0];
	B[0] = B[1];
	B[1] = b;
	if (key)
		write(1, "sb\n", 3);
}

void	ft_ss(int *A, int *B)
{
	ft_sa(A, 0);
	ft_sb(B, 0);
	write(1, "ss\n", 3);
}

void	ft_pa(int *A, int *B, int ac, int *ac_a, int *ac_b)
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
    }
}

void    ft_pb(int *A, int *B, int ac, int *ac_a, int *ac_b)
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
    }
}

void	ft_ra(int *A, int ac, int key)
{
	int a;
	int i;

	i = -1;
	a = A[0];
	while (++i < ac - 1)
		A[i] = A[i + 1];
	A[i] = a;
	if (key)
		write(1, "ra\n", 3);
}

void	ft_rb(int *B, int ac, int key)
{
	int b;
	int i;

	i = -1;
	b = B[0];
	while (++i < ac - 1)
		B[i] = B[i + 1];
	B[i] = b;
	if (key)
		write(1, "rb\n", 3);
}

void	ft_rr(int *A, int *B, int ac_a, int ac_b)
{
	ft_ra(A, ac_a, 0);
	ft_rb(B, ac_b, 0);
	write(1, "rr\n", 3);
}

void	ft_rra(int *A, int ac, int key)
{
	int a;

	a = A[ac - 1];
	while (ac--)
		A[ac] = A[ac - 1];
	A[0] = a;
	if (key)
		write(1, "rra\n", 4);
}

void	ft_rrb(int *B, int ac, int key)
{
	int b;

	b = B[ac - 1];
	while (ac--)
		B[ac] = B[ac - 1];
	B[0] = b;
	if (key)
		write(1, "rrb\n", 4);
}

void	ft_rrr(int *A, int *B, int ac_a, int ac_b)
{
	ft_rra(A, ac_a, 0);
	ft_rrb(B, ac_b, 0);
	write(1, "rrr\n", 4);
}

// --------------------------------------------------

int		ft_finder_b(int *B, int x, int *in_b, int ac_b, int ac)
{
	int i;

	i = -1;
	*in_b = 0;
	while (++i < ac_b)
	{
		if ((x == B[i] - 1 && B[i] != -1) || (x == 0 && B[i] == ac - 1))
		{
			*in_b = i;
			return (1);
		}
		if ((x == B[i] + 1 && B[i] != -1) || (x == ac - 1 && B[i] == 0))
		{
			*in_b = i;
			return (2);
		}
	}
	return (0);
}

int		ft_finder_a(int	*A, int	*B, int i, int *in_b_mark, int	*in_b, int ac_a, int ac_b, int ac)
{

	int	j;
	int	k;

	j = 0;
	k = ac_a - 1;
	while (A[j] != i || A[k] != i)
	{	
		if (ac_b)
		{
			*in_b_mark = ft_finder_b(B, A[j], in_b, ac_b, ac);
			if (*in_b_mark)
				return (j);
			*in_b_mark = ft_finder_b(B, A[k], in_b, ac_b, ac);
			if (*in_b_mark)
				return (k);
		}
		j++;
		k--;
	}
	if (A[j] == i)
		return (j);
	return (k);
}

// ------------------------------------------------------------------------------
void 	ft_slide_rr(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int *x_operations)
{
	while (a_pos)
	{
		if (b_pos)
		{
			ft_rr(A, B, ac_a, ac_b);
			b_pos--;
			*x_operations += 1;
		}
		else
		{
			ft_ra(A, ac_a, 1);
			*x_operations += 1;
		}
		a_pos--;
	}
	while (b_pos)
	{
		ft_rb(B, ac_b, 1);
		*x_operations += 1;
		b_pos--;
	}
}

void 	ft_slide_rrr(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int *x_operations)
{
	while (a_pos < ac_a)
	{
		if (b_pos < ac_b)
		{
			ft_rrr(A, B, ac_a, ac_b);
			b_pos++;
			*x_operations += 1;
		}
		else
		{
			ft_rra(A, ac_a, 1);
			*x_operations += 1;
		}
		a_pos++;
	}
	while (b_pos < ac_b)
	{
		ft_rrb(B, ac_b, 1);
		*x_operations += 1;
		b_pos++;
	}
}

void 	ft_slide_ra_rrb(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int *x_operations)
{
	while (a_pos)
	{
		ft_ra(A, ac_a, 1);
		a_pos--;
		*x_operations += 1;
	}
	while (b_pos < ac_b)
	{
		ft_rrb(B, ac_b, 1);
		b_pos++;
		*x_operations += 1;
	}
}

void 	ft_slide_rra_rb(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int *x_operations)
{
	while (a_pos < ac_a)
	{
		ft_rra(A, ac_a, 1);
		a_pos++;
		*x_operations += 1;
	}
	while (b_pos)
	{
		ft_rb(B, ac_b, 1);
		b_pos--;
		*x_operations += 1;
	}
}

void	ft_slide_a_b(int *A, int *B, int a_pos, int b_pos, int ac_a, int ac_b, int *x_operations)
{
	if (a_pos <= ac_a / 2 && b_pos <= ac_b / 2)
		ft_slide_rr(A, B, a_pos, b_pos, ac_a, ac_b, x_operations);
	if (a_pos > ac_a / 2 && b_pos > ac_b / 2)
		ft_slide_rrr(A, B, a_pos, b_pos, ac_a, ac_b, x_operations);
	if (a_pos <= ac_a / 2 && b_pos > ac_b / 2)
		ft_slide_ra_rrb(A, B, a_pos, b_pos, ac_a, ac_b, x_operations);
	if (a_pos > ac_a / 2 && b_pos <= ac_b / 2)
		ft_slide_rra_rb(A, B, a_pos, b_pos, ac_a, ac_b, x_operations);
}

// ------------------------------------------------------------------------------
void	ft_is_missposition(int	*A, int *B, int count_misspos, int *list_of_misspos, int to_rot, int ac, int *x_operations)
{
	int	i;
	int	j;
	int k;
	int ac_a;
	int ac_b;
	int w_lock;
	int in_b;
	int in_b_mark;

	w_lock = 1;
	i = 0;
	ac_a = ac;
	ac_b = 0;
	while (count_misspos || to_rot || ac_b)
	{
		while (w_lock && i < ac && list_of_misspos[i] == 0)
		{
			if (i != ac - 1)
				i++;
			else
				w_lock = 0;
		}
		in_b_mark = 0;
		j = ft_finder_a(A, B, i, &in_b_mark, &in_b, ac_a, ac_b, ac);
		ft_slide_a_b(A, B, j, in_b, ac_a, ac_b, x_operations);
		if (in_b_mark)
		{
			if (in_b_mark == 1)
			{
				ft_ra(A, ac_a, 1);
				*x_operations += 1;
			}
			ft_pa(A, B, ac, &ac_a, &ac_b);
			*x_operations += 1;
		}
		if (list_of_misspos[A[0]] == 2)
		{
			list_of_misspos[A[0]] = 0;
			ft_sa(A, 1);
			*x_operations += 1;
			to_rot--;
			i++;
		}
		if (list_of_misspos[A[0]] == 1)
		{
			list_of_misspos[A[0]] = 0;
			ft_pb(A, B, ac, &ac_a, &ac_b);
			*x_operations += 1;
			count_misspos--;
			i++;
		}
	}
}

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

int		ft_count_missposition(int *A, int ac, int *rot, int *lst_of_miss, int *x_operations)
{
    int        i;
    int     diff_pos;
    int        count_misspos;
    int        found;
    int        loop_chk;
    int        first_chk;
    int        f_swap;
    int        f_swap_release;
    
    f_swap = 0;
    f_swap_release = 0;
    found = 0;
    count_misspos = 0;
    i = 0;
	
	if (A[0] == A[1] + 1 || A[0] == A[1] - ac + 1)
	{
        ft_sa(A, 1);
		*x_operations += 1;
	}
    while (A[0] == A[ac - 1] - 1 || A[0] == A[ac - 1] + ac - 1)
    {
        ft_rra(A, ac, 1);
        ft_sa(A, 1);
		*x_operations += 2;
    }
    while (A[i] != 0)
        i++;
    if (i == 0)
        first_chk = ac - 1;
    else
        first_chk = i - 1;
    if (A[first_chk] == 1)
    {
        if (first_chk == ac - 1)
        {
            ft_rra(A, ac, 1);
            ft_sa(A, 1);
			*x_operations += 2;
        }
        else
        {
            f_swap++;
            i--;
        }
    }
    diff_pos = ac - i;
    i = 0;
    loop_chk = 0;
    while (i < ac)
    {
        loop_chk++;
        if (A[i + f_swap] == 0)
        {
            diff_pos -= ac;
            if (f_swap)
                f_swap_release++;
            f_swap = 0;
        }
        if (A[i] - diff_pos != i && A[i] - diff_pos != loop_chk && !f_swap_release)
        {
            lst_of_miss[A[i]] = 1;
            count_misspos++;
            found++;
            diff_pos--;
        }
        if (A[i] - diff_pos == loop_chk)
        {
            if (loop_chk > ac - 1)
                loop_chk = 0;
            if (A[loop_chk] - diff_pos == i)
            {
                lst_of_miss[A[i]] = 2;
                *rot += 1;
                i++;
                loop_chk++;
                f_swap_release = 0;
            }
            else
            {
                diff_pos++;
                found--;
            }
        }
        i++;
    }
    if (!count_misspos && !*rot)
        free(lst_of_miss);
    return (count_misspos);
}

// ------------------------------------------------------------------------------
void	ft_move(int *A, int ac, int index, int *x_operations)
{
	int	i;

	i = 0;
	while (A[i] != index)
		i++;
	if (i < ac / 2)
	{
		while (A[0] != index)
		{
			ft_ra(A, ac, 1);
			*x_operations += 1;
		}
	}
	else
	{
		while (A[0] != index)
		{
			ft_rra(A, ac, 1);
			*x_operations += 1;
		}
	}
	
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

int		ft_sw_pu(int *A, int *B, int *list_of_misspos, int ac)
{
    int count_misspos;
	int	to_rotate;
	int i;
	int x_operations;

	x_operations = 0;
	to_rotate = 0;
	count_misspos = 0;
	if (ft_chk_dup(A, ac))
		return (1);
	ft_first_last(A, ac);
	while (ft_chk_positions(A, ac))
	{
		count_misspos = ft_count_missposition(A, ac, &to_rotate, list_of_misspos, &x_operations);
		if (count_misspos || to_rotate)
			ft_is_missposition(A, B, count_misspos, list_of_misspos, to_rotate, ac, &x_operations);
		ft_move(A, ac, 0, &x_operations);
	}
    printf("count_misspos: %d\ncount_to_rotate: %d\n*x_operations: %d\n", count_misspos, to_rotate, x_operations);
	return (0);
}

//---------------------------------------------------
int		ft_stack_sorted(int *A, int ac)
{
	int		i;

	i = -1;
	while (++i < ac - 1)
		if (A[i] > A[i + 1])
			return (0);
	return (1);
}

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

int	main (int ac, char **av)
{
	int 	i;
	int 	*A;
	int		*B;
	int		*list_of_misspos;

	ac--;
	if (ft_intmax_chk(av, ac))
	{
		write (1, "Error\n", 6);
		return (0);
	}
	A = malloc(sizeof(int) * ac);
	B = malloc(sizeof(int) * ac);
	list_of_misspos = malloc(sizeof(int) * ac);
	i = -1;
	while (++i < ac)
	{
		list_of_misspos[i] = 0;
		B[i] = -1;
		A[i] = ft_atoi(av[i + 1]);
	}
	// start
	if (ft_sw_pu(A, B, list_of_misspos, ac))
	{
		write (1, "Error\n", 6);
		return (0);
	}
	// finish
	if (ft_stack_sorted(A, ac))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	i = -1;
	while (++i < ac)
		printf ("%d  ", A[i]);
}
