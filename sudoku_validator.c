/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sudoku_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c2h6 <esafar@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:52:29 by c2h6              #+#    #+#             */
/*   Updated: 2022/09/25 11:52:32 by c2h6             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool    verify_line(int grid[9][9], int line_nb)
{
    int value_to_check;

    for (int i = 0; i < 9; i++)
    {
        value_to_check = grid[line_nb][i];

        for (int j = 0; j < 9; j++)
        {
            if (i != j)
            {
                if (value_to_check == grid[line_nb][j])
                    return (true);
            }
        }
    }

    return (false);
}

bool    verify_column(int grid[9][9], int column_nb)
{
    int value_to_check;

    for (int i = 0; i < 9; i++)
    {
        value_to_check = grid[i][column_nb];

        for (int j = 0; j < 9; j++)
        {
            if (i != j)
            {
                if (value_to_check == grid[j][column_nb])
                    return (true);
            }
        }
    }

    return (false);
}

bool    check_value_inside_subgrid(int grid[9][9], int value, int start_i, int start_j)
{
    int count = 0;

    int i = start_i;
    int j = start_j;

    for ( ; j < start_j + 3; j++)
    {
        i = start_i;
        for ( ; i < start_i + 3; i++)
        {
            if (value == grid[j][i])
            {
                count++;
                // printf("VALUE FOUND: %d - %d\n", value, count);
            }
        }
    }

    if (count > 1)
        return (true);
    return (false);
}

bool    verify_subgrid(int grid[9][9], int subgrid_nb)
{
    int value_to_check;

    int start_i;
    int start_j;

    if (subgrid_nb >= 0 && subgrid_nb <= 2)
        start_j = 0;
    else if (subgrid_nb >= 3 && subgrid_nb <= 5)
        start_j = 3;
    else if (subgrid_nb >= 6 && subgrid_nb <= 8)
       start_j = 6;

    if (subgrid_nb == 0 || subgrid_nb == 3 || subgrid_nb == 6)
        start_i = 0;
    else if (subgrid_nb == 1 || subgrid_nb == 4 || subgrid_nb == 7)
        start_i = 3;
    else if (subgrid_nb == 2 || subgrid_nb == 5 || subgrid_nb == 8)
        start_i = 6;

    // printf("\nsubgrid: %d | %d\n", start_i, start_j);

    int i = start_i;
    int j = start_j;

    for ( ; j < start_j + 3; j++)
    {
        i = start_i;
        for ( ; i < start_i + 3; i++)
        {
            value_to_check = grid[j][i];
            // printf("value to check [%d]\n", value_to_check);

            if (check_value_inside_subgrid(grid, value_to_check, start_i, start_j) == true)
                return (true);
        }
    }

    return (false);
}

void    sudoku_validator(int grid[9][9])
{
    bool output = true;

    for (int i = 0; i < 9; i++)
    {
        if (verify_line(grid, i) == true)
            output = false;
    }

    for (int j = 0; j < 9; j++)
    {
        if (verify_column(grid, j) == true)
            output = false;
    }

    for (int block = 0; block < 9; block++)
    {
        if (verify_subgrid(grid, block) == true)
            output = false;
    }

    if (output == false)
        printf("false\n");
    else
        printf("true\n");

    return ;
}

int main()
{
    int grid[9][9];

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            scanf("%d", &grid[i][j]);
            // printf("[%d]", grid[i][j]);
        }
        // printf("\n");
    }

	// test verify_line() function
    // printf("bool test: %d", verify_line(grid, 0));

	// test verify_column() function
    // printf("bool test: %d", verify_column(grid, 0));

	// test verify_subgrid() function
    // printf("bool test: %d", verify_subgrid(grid, 0));


    // Write an answer using printf(). DON'T FORGET THE TRAILING \n
    // To debug: fprintf(stderr, "Debug messages...\n");

    sudoku_validator(grid);

    return 0;
}
