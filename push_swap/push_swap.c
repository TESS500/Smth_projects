#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void	*ft_calloc(size_t num, size_t size)
{
	void			*mass;

	if (!num || !size)
	{
		num = 1;
		size = 1;
	}
	mass = malloc(num * size);
	if (!(mass))
		return (0);
	ft_bzero(mass, num * size);
	return (mass);
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

void    ft_pa(int *A, int *B, int ac, int *ac_a, int *ac_b)
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
        while (i < ac - 2 && B[i] != -1)
        {
            B[i] = B[i + 1];
            i++;
        }
        if (B[ac - 1] != -1)
          B[ac - 1] = -1;
        *ac_a += 1;
        *ac_b -= 1;
        write(1, "pb\n", 3);
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
        while (i < ac - 2 && A[i] != -1)
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

void	ft_rr(int *A, int *B, int ac)
{
	ft_ra(A, ac, 0);
	ft_rb(B, ac, 0);
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

void	*ft_rrr(int *A, int *B, int ac, int key)
{
	ft_rra(A, ac, 0);
	ft_rrb(B, ac, 0);
	if (key)
		write(1, "rrr\n", 4);
}
// --------------------------------------------------

void    ft_is_missposition(int  *A, int *B, int count_misspos, int *list_of_misspos, int to_rot, int ac)
{
    int   i = 0;
    int   j;
    int   b = 0;
    int previous;
    int ac_a = ac;
    int ac_b = 0;

    while (i < ac)
    {
        j = 0;
        if (i == ac - 1)
          i = -1;
        if (i != -1)
        {
          while (list_of_misspos[i] == 0 && i < ac - 2)
            i++;
        }
        if (list_of_misspos[ac - 1] == 0);
            i = -1;
        while (A[j] != i && !(A[j] == B[1] + 1 && B[1] != -1)
						&& !(A[j] == B[0] + 1 && B[0] != -1))
            j++;
        if (j < ac_a / 2 )
        {
            while (j)
            {
                ft_ra(A, ac_a, 1);
                j--;
            }
        }
        else
        {
            while (j < ac_a)
            {
                ft_rra(A, ac_a, 1);
                j++;
            }
        }
		if ((A[j] == B[1] + 1 && B[1] != -1) || (A[j] == B[0] + 1 && B[0] != -1))
		{
			if (A[j] == B[1] + 1 && B[1] != -1)
				ft_sb(B, 1);
			ft_pa(A, B, ac, &ac_a, &ac_b);
		}
        if (list_of_misspos[i] == 2)
        {
            ft_sa(A, 1);
            to_rot--;
            list_of_misspos[i] = 0;
            i++;
        }
        else if (list_of_misspos[i] == 1)
        {
            if (A[j] == i)
            {
                ft_pb(A, B, ac, &ac_a, &ac_b);
                i++;
                list_of_misspos[A[j]] = 0;
                count_misspos--;
            }
		}
    }
}

// --------------------------------------------------
void    ft_first_last(int *A, int ac)
{
  int i;
  int j;
  int first;
  int second;
  int last;

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
			A[i] = j;
		i++;
	}
	j++;
	first = second;
  }
}

int ft_module(int a)
{
    if (a < 0)
        a *= -1;
    return (a);
}

//-------------------------------------------------

int        ft_count_missposition(int *A, int ac, int *rot, int *lst_of_miss)
{
    int		i;
    int 	diff_pos;
    int		count_misspos;
    int		found;
    int		loop_chk;
    int		first_chk;
    int		f_swap;
	int		f_swap_release;
    
    f_swap = 0;
	f_swap_release = 0;
    found = 0;
    count_misspos = 0;
    i = 0;
	while (A[0] == A[ac - 1] - 1)
	{
		ft_rra(A, ac, 1);
		ft_sa(A, 1);
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
			lst_of_miss[(int)A[i]] = 1;
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
				lst_of_miss[(int)A[i]] = 2;
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

void	ft_move(int *A, int ac)
{
	int	i;

	i = 0;
	while (A[i] != 0)
		i++;
	if (i < ac / 2)
		while (A[0])
			ft_ra(A, ac, 1);
	else
		while (A[0])
			ft_rra(A, ac, 1);
	
}

void	ft_sw_pu(int *A, int *B, int ac)
{
    int count_misspos;
	int	last;
	int	to_rotate;
	int	*list_of_misspos;
	int i = 0;
	to_rotate = 0;
	list_of_misspos = ft_calloc(ac, sizeof(int));
	if (!list_of_misspos)
			exit (1);
	ft_first_last(A, ac);
    count_misspos = ft_count_missposition(A, ac, &to_rotate, list_of_misspos);
	if (count_misspos || to_rotate)
		ft_is_missposition(A, B, count_misspos, list_of_misspos, to_rotate, ac);
	ft_move(A, ac);
    printf("count_misspos: %d\ncount_to_rotate: %d\n", count_misspos, to_rotate);
}

//---------------------------------------------------
int		ft_stack_sorted(int *A, int *B, int ac)
{
	int		i;

	i = -1;
	while (++i < ac - 1)
		if (A[i] > A[i + 1])
			return (0);
	return (1);
}

int	main (int ac, char **av)
{
	int 	i;
	int 	*A;
	int		*B;

	A = malloc(sizeof(int) * (ac - 1));
	B = malloc(sizeof(int) * (ac - 1));
	i = 1;
	while (i < ac)
	{
		B[i - 1] = -1;
		A[i - 1] = atoi(av[i]);
		i++;
	}
	ac--;
	// start
	ft_sw_pu(A, B, ac);
	// finish
	if (ft_stack_sorted(A, B, ac))
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	i = -1;
	while (++i < ac)
		printf ("%d  ", A[i]);
}
