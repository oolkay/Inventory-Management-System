#include "utils.h"

//this function cpy stocks to the filtered.txt
void cpy_stocks_to_filtered()
{
    FILE *src = fopen("stocks.txt", "r");
    FILE *dest = fopen("filtered.txt", "w+");
    char cursor = fgetc(src);
    while (cursor != EOF)
    {
        fprintf(dest, "%c", cursor);
        cursor = fgetc(src);
    }
    fclose(src);
    fclose(dest);
}

//this function is similar to the strcmp from string.h
int ft_strcmp(char str[], char branch[])
{
    int i = 0;
    while (str[i] != '\0' && branch[i] != '\0')
    {
        if (str[i] != branch[i])
            return (-1);
        i++;
    }
    if ((str[i] || branch[i]) && (str[i] != branch[i]))
        return (-1);
    else
        return (1);
}

//this function lists stock with given branch
void list_stock_branch(int s_nbr)
{
    FILE *stock = fopen("stocks.txt","r+");
    char cursor;
    cursor = fgetc(stock);
    char branch_inp[20];
    printf("Enter branch name: ");
    scanf("%s", branch_inp);
    while (cursor != '\0'  && cursor != '\n')
    {
        cursor = fgetc(stock);
    }
    printf("sid,pid,Branch,Stock\n");
    for (int i=1; i <= s_nbr ; i++)
    {
        int pid,sid,current_stock;
        char branch[16];
        fscanf(stock,"%d,%d,%[^,],%d\n", &sid, &pid, branch, &current_stock);
        if (ft_strcmp(branch_inp,branch)==1)
        {
            printf("%d,%d,%s,%d\n",sid,pid,branch,current_stock);
        }
    }
    fclose(stock);
}

//this function list products that out of stock
void list_out_of_stock(int s_nbr)
{
    FILE *stock = fopen("stocks.txt","r+");
    char cursor;
    cursor = fgetc(stock);
    char branch_inp[20];
    printf("Enter branch name: ");
    scanf("%s", branch_inp);
    while (cursor != '\0'  && cursor != '\n')
    {
        cursor = fgetc(stock);
    }
    printf("sid,pid,Branch,Stock\n");
    for (int i=1; s_nbr>=i ; i++)
    {
        int pid,sid,current_stock;
        char branch[16];
        fscanf(stock,"%d,%d,%[^,],%d\n",&sid,&pid,branch,&current_stock);
        if (current_stock == 0 && ft_strcmp(branch_inp,branch) == 1)
        {
            printf("%d,%d,%s,%d\n",sid,pid,branch,current_stock);
        }
    }
    fclose(stock);
}

//this function query stock with given branch
int query_stock()
{
    int pid, sid, n;
    int s_nbr = id_nbr();
    int i = 0;
    char cursor;
    char branch[20];
    int result = 0;
    int current_stock;
    FILE *stock = fopen("stocks.txt","r+");

    cursor = fgetc(stock);
    printf("Enter product's pID: ");
    scanf("%d", &pid);
    printf("Enter product's branch: ");
    scanf("%s", branch);
    while (cursor != '\n')
        cursor = fgetc(stock);
    while (i < s_nbr)
    {
        char str[20];
        fscanf(stock,"%d,%d,%[^,],%d\n",&sid,&n,str,&current_stock);
        if (pid == n && ft_strcmp(str, branch) == 1)
            result += current_stock;
        i++;
    }
    fclose(stock);
    printf("\n#The total stock of the given product in given branch is: %d#\n\n",result);
}

//submenu for stock status part3
void stock_status(int p_nbr)
{
    int n = 1;
    int pid;
    int s_nbr = id_nbr();
    while (n > 0 && n <= 3)
    {
        printf("\n\n----->STOCK OPERATIONS<-----\n");
        printf("*************************************\n");
        printf("* 1) Query the stock by branch      *\n");
        printf("* 2) List stocks in specified branch*\n");
        printf("* 3) List out-of-stock products     *\n");
        printf("* 4) Back to menu                   *\n");
        printf("*************************************\n");
        printf("Choose an operation: ");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                query_stock();
                break;
            case 2:
                list_stock_branch(s_nbr);
                break;
            case 3:
                list_out_of_stock(s_nbr);
                break;
            case 4:
                printf("\n\n\n");
                return ;
                break;
        }
    }
}