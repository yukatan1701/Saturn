#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <data_structures/bitset.h>
#include <data_structures/bitset_tree.h>

void
test_null_bitset()
{
    for (unsigned int i = 1; i <= 16; ++i)
    {
        bitset_t bs_ibit = init_bitset(i);
        print_bitset(&bs_ibit);
        free_bitset(&bs_ibit);
    }
}

void
test_set_bitset()
{
    for (unsigned int i = 1; i <= 16; ++i)
    {
        bitset_t bs_ibit = init_bitset(i);
        BITSET(bs_ibit.data, i - 1);
        print_bitset(&bs_ibit);
        free_bitset(&bs_ibit);
    }
}

int
factorial(unsigned int n)
{
    unsigned int f = 1;
    for (unsigned int i = 1; i <= n; ++i)
        f *= i;
    return f;
}

void
test_specific_tree(int k, int n)
{
    printf("Init new tree (%d, %d).\n", k, n);
    tree_t tree = init_bitset_tree_iteratively(k, n);
    print_bitset_tree_word(&tree);
    tree_iterator_t it = init_bitset_tree_iterator(&tree);
    printf("Iterator:\n");
    while (it.node)
    {
        print_bitset(&it.bitset);
        set_t *set = get_nums_by_iterator_with_offset(&it);
        printf("Set: ");
        print_set(set);
        printf("\n");
        next_iterator_pos(&it);
        free_set(&set);
    }
    free_bitset_tree_iterator(&it);
    free_bitset_tree(&tree);
    printf("\n");
}

char check_bitset(bitset_t bitset, unsigned expected)
{
    size_t n = 0;
    for (size_t i = 0; i < bitset.length; ++i)
        n += (BITTEST(bitset.data, i) > 0);
    return n == expected;
}

void
test_bitset_tree()
{
    size_t k = 4, n = 6;
    tree_t tree = init_bitset_tree_iteratively(k, n);
    //print_bitset_tree(&tree);
    tree_iterator_t it = init_bitset_tree_iterator(&tree);
    print_bitset_tree_word(&tree);
    printf("Iterator:\n");
    while (it.node)
    {
        print_bitset(&it.bitset);
        assert(check_bitset(it.bitset, k) && "Invalid count of ones!");
        next_iterator_pos(&it);
    }
    free_bitset_tree_iterator(&it);
    free_bitset_tree(&tree);

    printf("Iteratively:\n");
    test_specific_tree(2, 4);
    test_specific_tree(4, 4);
    test_specific_tree(0, 4);
    test_specific_tree(0, 0);
}

int
main()
{
    test_null_bitset();

    test_set_bitset();

    test_bitset_tree();

    return 0;
}