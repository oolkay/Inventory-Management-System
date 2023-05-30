#include "utils.h"

//this function returns the given feature's position
//returns 2 if there is 2 comma before given feature
int find_feature_place(char feature[])
{
    FILE *fp = fopen("filtered.txt", "r+");
    char cursor = fgetc(fp);
    int i = 0;
    int cnt = 0;
    int comma = 0;

    while (cursor != '\n' && cursor != EOF)
    {
        i = 0;
        if (cursor == ',')
            comma++;
        while (cursor == feature[i])
        {
            cursor = fgetc(fp);
            i++;
        }
        if (feature[i] == '\0' && (cursor == ',' || cursor == '\n'))
        {
            fclose(fp);
            return (comma);
        }
        cursor = fgetc(fp);
    }
    fclose(fp);
    return (0);
}

//this function list products
void list_products()
{
    FILE *fp = fopen("products.txt", "r");
    char cursor = fgetc(fp);

    printf("\n\n");
    printf("-->PRODUCTS<--\n");
    while (cursor != EOF)
    {
        printf("%c", cursor);
        cursor = fgetc(fp);
    }
    printf("\n\n");
}

//this function cpy products to filtered.txt
void cpy_products_to_filtered()
{
    FILE *src = fopen("products.txt", "r");
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

//this function filters the products with given feature name and value
int filter_the_txt(char feature_name[], int p_nbr, char f_value[], double min, double max)
{
    int pid;
    double price;
    int deletedpid[p_nbr];
    int i = 0, j = 0;
    int comma = 0;
    int cnt = 0;
    FILE *fp = fopen("products.txt", "r+");
    char cursor = fgetc(fp);

    comma = find_feature_place(feature_name);
    while (cursor != '\n')
        cursor = fgetc(fp);
    while (cursor != EOF)
    {
        i = 0;
        cnt = 0;
        fscanf(fp, "%d", &pid);
        if (cnt == ',')
            cnt++;
        while (cnt < comma)
        {
            cursor = fgetc(fp);
            if (cursor == ',')
                cnt++;
        }
        if (comma == 4)
        {
            fscanf(fp, "%lf", &price);
            if (price < min || price > max)
            {
                deletedpid[j] = pid;
                j++;
            }
        }
        else
        {
            cursor = fgetc(fp);
            while (f_value[i] == cursor)
            {
                cursor = fgetc(fp);
                i++;
            }
            if (!(f_value[i] == '\0' && (cursor == ',' || cursor == '\n' || cursor == EOF)))
            {
                deletedpid[j] = pid;
                j++;
            }
        }
        while (cursor != '\n' && cursor != EOF)
            cursor = fgetc(fp);
    }
    fclose(fp);
    while (j-1 >= 0)
    {
        delete_product(deletedpid[j-1], p_nbr, "filtered.txt");
        j--;
    }
}

void filter_products(int p_nbr)
{
    int j = 0;
    int i = 0;
    char filter[80];
    char filteredlist[p_nbr][50];
    double min, max;
    printf("Please enter feature names you want to filter\n");
    printf("Seperate them with comma(Brand,Samsung,Type,O)\n");
    cpy_products_to_filtered();
    scanf("%s", filter);
    while (filter[i] != '\0')
    {
        if (filter[i] == ',')
            i++;
        char f_name[20];
        char f_value[20];
        j = 0;
        //trimming filter for ex: Type
        while(filter[i] != ',' && filter[i] != '\0')
        {
            f_name[j] = filter[i];
            i++;
            j++;
        }
        f_name[j] = '\0';
        if (ft_strcmp(f_name,"Price") == 1)
        {
            printf("Please enter the min and max price: ");
            scanf("%lf %lf",&min, &max);
        }
        j = 0;
        if (filter[i] == ',')
            i++;
        //trimming filter value for ex: D
        while (filter[i] != ',' && filter[i] != '\0')
        {
            f_value[j] = filter[i];
            i++;
            j++;
        }
        f_value[j] = '\0';
        filter_the_txt(f_name, p_nbr, f_value, min, max);
    }
    i = 0;
    j = 0;
    file_to_arr(filteredlist, "filtered.txt");
    printf("\n\n");
    if (filteredlist[i][j])
    {
        printf(" pID , Type , Name , Brand , Price\n");
        while (filteredlist[i][j] != 0)
        {
            printf("%s\n", filteredlist[i]);
            i++;
        }
    }
    printf("\n\n");

}

//submenu for part2
int query_products(int p_nbr)
{
    int n = 1;
    int pid;
    while (n > 0 && n < 3)
    {
        printf("\n\n-->QUERY OPERATIONS<--\n");
        printf("************************\n");
        printf("* 1) List all products *\n");
        printf("* 2) Filter products   *\n");
        printf("* 3) Back to main menu *\n");
        printf("************************\n");
        printf("Choose an operation: ");
        scanf("%d", &n);

        switch(n)
        {
            case 1:
                list_products();
                break;
            case 2:
                filter_products(p_nbr);
                break;
            case 3:
                return (0);
                break;
        }
    }
}