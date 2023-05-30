#include "utils.h"

//this function finds how many product
//that file contains
int find_product_nbr()
{
    FILE *fp = fopen("products.txt", "r");;
    int result = 0;
    char c;

    while ((c = fgetc(fp)))
    {
        if (c == EOF)
            break;
        if (c == '\n')
            result++;
    }
    fclose(fp);
    return result;
}

//this function queries the stock, find min max median
int query_stock3(int pid, int *min, int *max, int *median)
{
    int sid, n, indx = 0;
    int s_nbr = id_nbr();
    int list[s_nbr];
    int i = 0, j = 0;
    char cursor;
    int current_stock;
    FILE *stock = fopen("stocks.txt","r+");

    cursor = fgetc(stock);
    while (cursor != '\n') //skipping newline
        cursor = fgetc(stock);
    while (i < s_nbr)
    {
        char str[20];
        fscanf(stock,"%d,%d,%[^,],%d\n",&sid,&n,str,&current_stock);
        if (pid == n)
        {
            list[indx] = current_stock;
            indx++;
        }
        i++;
    }
    fclose(stock);
    i = 0;
    int tmp = 0;
    if (indx == 0)
    {
        *min = 0;
        *max = 0;
        *median = 0;
    }
    else
    {
        while (i < indx-1)//sort
        {
            j = i + 1;
            while (j < indx)
            {
                if (list[j] < list[i])
                {
                    tmp = list[j];
                    list[j] = list[i];
                    list[i] = tmp;
                }
                j++;
            }
            i++;
        }
        *min = list[0];
        *max = list[indx - 1];
        *median = list[(indx/2)];
    }
}

void export_report(int p_nbr, char brand[50])
{
    int min,max,median;
    FILE *product = fopen("products.txt","r");
    FILE *report = fopen("report.txt","w+");
    fprintf(report,"pID - Min Stock - Max Stock - Median Stock\n");
    char c;
    while ((c = fgetc(product)) &&  c != '\n' && c != EOF); //skipping first line
    for (int i = 0; i < p_nbr; i++)
    {
        int pID;
        char type;
        char name[20];
        double price;
        char tmp_brand[10];
        fscanf(product,"%d,%c,%[^,],%[^,],%lf",&pID, &type, name, tmp_brand, &price);
        if (ft_strcmp(tmp_brand,brand) == 1)
        {
            query_stock3(pID ,&min, &max, &median); // this function find min,median,max stock of the given brand
            fprintf(report,"%d,%d,%d,%d\n",pID,min,max,median);//printing it to the report.txt
        }
        while ((c = fgetc(product)) &&  c != '\n' && c != EOF); //skipping next line
    }
    fclose(product);
    fclose(report);

    //printing it to the shell
    report = fopen("report.txt","r");
    c = fgetc(report);
    while (c != EOF)
    {
        printf("%c", c);
        c = fgetc(report);
    }
    fclose(report);
}

void menu()
{
    int n = 1;
    int p_nbr = 0;
    while (n == 1 || n == 2 || n== 3 || n== 4 || n == 5)
    {
        p_nbr = find_product_nbr();
        printf("---------------------->MAIN MENU<------------------------\n");
        printf("-----------------------------------------------------------\n");
        printf("|Welcome operator, please select an option to continue:   |\n");
        printf("|1- File operations                                       |\n");
        printf("|2- Query products                                        |\n");
        printf("|3- Check stock status                                    |\n");
        printf("|4- Stock control by brand                                |\n");
        printf("|5- Export report                                         |\n");
        printf("|6- Exit                                                  |\n");
        printf("-----------------------------------------------------------\n");
        printf("Option: ");
        scanf("%d", &n);

        switch (n)
        {
            case 1:
                p_nbr = file_ops(p_nbr);
                break;
            case 2:
                query_products(p_nbr);
                break;
            case 3:
                stock_status(p_nbr);
                break;
            case 4:
                char brand[50];
                printf("Enter brand: ");
                scanf("%s", brand);
                brand_stack_control(p_nbr, brand);
                break;
            case 5:
                export_report(p_nbr, brand);
                break;
            case 6:
                return ;
        }
    }
}

int main()
{
    menu();
    return (0);
}