#ifndef UTILS_H
# define UTILS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int query_products(int p_nbr);
int file_ops(int pid);
int delete_product(int pid, int p_nbr, char file[]);
void stock_status(int p_nbr);
int id_nbr();
int delete_stock(char str[], int sid);
int ft_strcmp(char str[], char branch[]);
void brand_stack_control(int p_nbr, char brand[50]);
int query_stock();
void file_to_arr(char list[][50], char str[]);


#endif