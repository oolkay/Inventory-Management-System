#include "utils.h"

int query_stock2(int pid)
{
    int sid, n;
    int s_nbr = id_nbr();
    int i = 0;
    char cursor;
    int result = 0;
    int current_stock;
    FILE *stock = fopen("stocks.txt","r+");

    cursor = fgetc(stock);
    while (cursor != '\n')
        cursor = fgetc(stock);
    while (i < s_nbr)
    {
        char str[20];
        fscanf(stock,"%d,%d,%[^,],%d\n",&sid,&n,str,&current_stock);
        if (pid == n)
            result += current_stock;
        i++;
    }
    fclose(stock);
    return (result);
}

//this function fill the array from given txt file
void file_to_arr(char list[][50], char str[])
{
    int i = 0;
    int j = 0;
    FILE *fp = fopen(str, "r+");
    char cursor = fgetc(fp);
    if (str[0] == 'f' && str[1] == 'i')
    {
        while (cursor != '\n')
            cursor = fgetc(fp);
    }
    if (cursor == '\n')
        cursor = fgetc(fp);
    while (cursor != EOF)
    {
        j = 0;
        while (cursor != '\n' && cursor != EOF)
        {
            list[i][j] = cursor;
            cursor = fgetc(fp);
            j++;
        }
        list[i][j] = '\0';
        if (cursor == '\n')
            cursor = fgetc(fp);
        i++;
    }
    list[i][0] = 0;
    fclose(fp);
}

//submenu for part5
void brand_stack_control(int p_nbr, char brand[50])
{
    int i= 0,k=0;;
    int s_nbr = id_nbr();
    FILE *product = fopen("products.txt", "r+");
    FILE *stock = fopen("stocks.txt", "r+");
    FILE *tmp = fopen("cpy.txt", "w");
    char list[p_nbr][50];
    int total_stock=0;

    char c;
    while ((c = fgetc(product)) &&  c != '\n'); // skipping first line.
    while (i < p_nbr)
    {
        int pid;
        char name[50],tmp_brand[50];
        char type;
        double price;
        fscanf(product,"%d,%c,%[^,],%[^,],%lf", &pid, &type, name, tmp_brand, &price);
        //printf("pid: %d name: %s brand:%s:\n",pid,name,tmp_brand);
        if (ft_strcmp(brand, tmp_brand) == 1)
        {
            total_stock = query_stock2(pid);
            fprintf(tmp, "%d,%.2lf,%d\n",pid,price,total_stock);
        }
        while ((c = fgetc(product)) &&  c != '\n' && c != EOF); // skipping next line.
        i++;
    }
    i = 0;
    int j = 0;
    fclose(product);
    fclose(stock);
    fclose(tmp);
    file_to_arr(list, "cpy.txt");
    printf("\n\n");
    if (list[i][0] != 0)
    { 
        printf("pid, price, current_stock\n");
        while (list[i][0] != 0)
        {
            printf("%s\n", list[i]);
            i++;
        }
    }
    printf("\n\n");
}