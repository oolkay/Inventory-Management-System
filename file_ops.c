#include "utils.h"

//this function returns how many stocks we have
int id_nbr()
{
    FILE *fp = fopen("stocks.txt", "r");;
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

//this function copiess text from copy.txt to src.txt
void copy_to_src(char file[])
{
    FILE *cpy = fopen(file, "w+");
    FILE *src = fopen("cpy.txt", "r+");
    char cursor = fgetc(src);
    while (cursor != EOF)
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fclose(src);
    fclose(cpy);
}

//this function deletes given product in txt
int delete_product(int pid, int p_nbr, char file[])
{
    FILE *src = fopen(file, "r+");
    FILE *cpy = fopen("cpy.txt", "w+");
    int n;
    char cursor;
    int flag = 0;

    cursor = fgetc(src);
    //skipping first line of file
    while (cursor != '\n')
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    if (p_nbr > 1)
        fprintf(cpy, "\n");
    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        //if this line does not contains given product, just copy to copy.txt
        if (pid != n)
        {
            if (flag == 1 && file[0] == 'p')
                n--;
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n' && n + 1 != p_nbr && n != p_nbr)
                fprintf(cpy, "\n");
        }
        //else it does contains given product, just skip to the next line
        else
        {
            flag = 1;
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
                cursor = fgetc(src);
        }
    }
    fclose(src);
    fclose(cpy);
    copy_to_src(file);
    return (1);
}

//this function add products
int add_product(int p_nbr)
{
    FILE *fp = fopen("products.txt", "r+");
    char type;
    char name[20];
    char brand[20];
    double price;

    //scanning variables
    printf("Please enter type of the product: ");
    scanf(" %c", &type);
    printf("Please enter name of the product: ");
    scanf("%s", name);
    printf("Please enter brand of the product: ");
    scanf("%s", brand);
    printf("Please enter price of the product: ");
    scanf("%lf", &price);

    if (p_nbr == 0)
        fprintf(fp, "%s", "pID,Type,Name,Brand,Price");
    while (fgetc(fp) != EOF);
    fprintf(fp, "\n%d,%c,%s,%s,%.2lf", p_nbr+1, type, name, brand, price);
    fclose(fp);
    return (1);
}

//this function is used as strcmp but it is not quite similar though
int my_strcmp(char str[], char flag)
{
    FILE *fp;
    char cursor;
    int i = 0;

    if (flag == 'p')
        fp = fopen("products.txt", "r+");
    if (flag == 's')
        fp = fopen("stocks.txt", "r+");
    cursor = fgetc(fp);
    while (cursor != '\n' && cursor != EOF)
    {
        i = 0;
        while (cursor == str[i])
        {
            cursor = fgetc(fp);
            i++;
        }
        if (str[i] == '\0' && (cursor == ',' || cursor == '\n'
            || cursor == EOF))
        {
            fclose (fp);
            return (1);
        }
        cursor = fgetc(fp);
    }
    fclose(fp);
    return (0);
}

//this function update product's given feature 
int update_product(int p_nbr)
{
    int pid;
    char new_f[20];
    char updated_text[20];
    char cursor;
    int n;
    int cnt = 0;
    int comma = 0;
    int feature_place;

    FILE *src = fopen("products.txt", "r+");
    FILE *cpy = fopen("cpy.txt", "w+");

    printf("Which product you want to update: ");
    scanf("%d", &pid);
    printf("Please enter the name of the future that you want to update: ");
    scanf("%s", new_f);
    printf("Please enter the name that you want to update as: ");
    scanf("%s", updated_text);
    
    //controlling if user trying to change pid
    if (new_f[0] == 'p' && new_f[1] == 'I' && new_f[2] == 'D')
    {
        printf("pID can not be updated\n");
        fclose(src);
        fclose(cpy);
        return (0);
    }
    cursor = fgetc(src);
    //skipping new line
    while (cursor != '\n')
    {
        if (cursor == ',')//counting comma
            cnt++;
        if (cursor == new_f[0] && my_strcmp(new_f, 'p') == 1)
            feature_place = cnt;            
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fprintf(cpy, "\n");
    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        //if the given pid not equals to the scanned pid, in other words pid
        //that we do not want to update
        if (pid != n)
        {
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n')
                fprintf(cpy, "\n");
        }//the product that we want to update
        else
        {
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                if (comma != feature_place)//counting comma
                {
                    fprintf(cpy, "%c", cursor);
                    if (cursor == ',')
                        comma++;
                    cursor = fgetc(src);
                }
                else if (comma == feature_place)
                {
                    fprintf(cpy, "%s", updated_text);
                    cursor = fgetc(src);
                    while (cursor != ',' && cursor != EOF && cursor != '\n')
                    {
                        cursor = fgetc(src);
                    }
                    comma++;
                }
                if (cursor == '\n')
                    fprintf(cpy, "\n");
            }
        }
    }
    fclose(src);
    fclose(cpy);
    copy_to_src("products.txt");
}

int add_feature(int p_nbr)
{
    FILE *src = fopen("products.txt", "r+");
    FILE *cpy = fopen("cpy.txt", "w+");
    char cursor;
    char feature[20];
    int cnt = 0;
    int flag = 0;
    printf("Enter the name of the new feature: ");
    scanf("%s", feature);
    
    cursor = fgetc(src);
    while (cursor != EOF)
    {
        while (cursor != '\n' && cursor != EOF)//skipping and copying first line
        {
            fprintf(cpy, "%c", cursor);
            cursor = fgetc(src);
        }
        if (cursor == '\n')
            flag = 1;
        else if (cursor == EOF)
            flag = 2;
        if (cnt == 0)
            fprintf(cpy, ",%s", feature);
        else
            fprintf(cpy, ",%c", '0');
        if (flag == 1)
        {
            fprintf(cpy, "\n");
            cursor = fgetc(src);
        }
        cnt++;
    }
    fclose(src);
    fclose(cpy);
    copy_to_src("products.txt");
}

int add_stock(int p_nbr)
{
    int sid;
    int pid;
    int current_stock;
    char branch[20];

    //SCAN AND CONTROL PART
    if (p_nbr == 0)
    {
        printf("there is no product so invalid operation\n");
        return (0);
    }
    FILE *fp = fopen("stocks.txt", "r+");
    int s_nbr = id_nbr();
    printf("Enter pID: ");
    scanf("%d", &pid);
    while (pid <= 0 || pid > p_nbr)
    {
        printf("Invalid pid\nEnter pID again: ");
        scanf("%d", &pid);
    }
    printf("Enter product's branch: ");
    scanf("%s", branch);
    printf("Enter product's current stock: ");
    scanf("%d", &current_stock);
    //SCAN AND CONTROL PART END

    //ADDING PART, reads until eof than fprints
    if (s_nbr == 0)
        fprintf(fp, "sID,pID,Branch,Current_stock");
    while (fgetc(fp) != EOF);
    fprintf(fp, "\n%d,%d,%s,%d", s_nbr+1, pid, branch, current_stock);
    fclose(fp);
}

int delete_stock(char str[], int sid)
{
    //Declarations and control part
    FILE *src = fopen(str, "r+");
    FILE *cpy = fopen("cpy.txt", "w+");
    int s_nbr = id_nbr();
    char cursor;
    int flag = 0;
    int n;
    if (sid <= 0 || sid > s_nbr)
    {
        printf("Invalid stock id");
        fclose(src);
        fclose(cpy);
        return (0);
    }//declare and control part end

    //skipping the first line
    cursor = fgetc(src);
    while (cursor != '\n')
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    if (s_nbr > 1)//else it is eof
        fprintf(cpy, "\n");

    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        if (sid != n)//the stock that we dont want to delete part
        {
            if (flag == 1 && str[0] == 's')
                n--;
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n' && n + 1 != s_nbr && n != s_nbr)
                fprintf(cpy, "\n");
        }
        else //the stock that we want to delete part
        {
            flag = 1;
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
                cursor = fgetc(src);
        }
    }
    fclose(src);
    fclose(cpy);

    //copying from cpy.txt to the file
    cpy = fopen(str, "w+");
    src = fopen("cpy.txt", "r+");
    cursor = fgetc(src);
    while (cursor != EOF)
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fclose(src);
    fclose(cpy);
    return (1);

}

int update_stock()
{
    //DECLARATIONS SCANNING AND CONTROLLING PART
    int sid;
    char new_f[20];
    char updated_text[20];
    char cursor;
    int n;
    int cnt = 0;
    int comma = 0;
    int feature_place;

    FILE *src = fopen("stocks.txt", "r+");
    FILE *cpy = fopen("cpy.txt", "w+");

    printf("Which product you want to update: ");
    scanf("%d", &sid);
    printf("Please enter the name of the future that you want to update: ");
    scanf("%s", new_f);
    printf("Please enter the name that you want to update as: ");
    scanf("%s", updated_text);
    
    if (new_f[0] == 's' && new_f[1] == 'I' && new_f[2] == 'D')
    {
        printf("sID can not be updated\n");
        fclose(src);
        fclose(cpy);
        return (0);
    }//DECLARATIONS SCANNING AND CONTROL END

    cursor = fgetc(src);
    while (cursor != '\n')//skip the first line
    {
        if (cursor == ',')
            cnt++;
        if (cursor == new_f[0] && my_strcmp(new_f, 's') == 1)//finds the position
            feature_place = cnt;;            
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fprintf(cpy, "\n");

    while (cursor != EOF)
    {
        fscanf(src, "%d", &n);
        if (sid != n)//the stock that we dont want to update
        {//it is basic copy loop
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                fprintf(cpy, "%c", cursor);
                cursor = fgetc(src);
            }
            if (cursor == '\n')
                fprintf(cpy, "\n");
        }
        else//the stock that we want to update
        {
            fprintf(cpy, "%d", n);
            cursor = fgetc(src);
            while (cursor != '\n' && cursor != EOF)
            {
                if (comma != feature_place)//it is not the feature that we want to update
                {
                    fprintf(cpy, "%c", cursor);
                    if (cursor == ',')
                        comma++;
                    cursor = fgetc(src);
                }
                else if (comma == feature_place)//it is the feature that we want to update
                {
                    fprintf(cpy, "%s", updated_text);
                    cursor = fgetc(src);
                    while (cursor != ',' && cursor != EOF && cursor != '\n')
                    {
                        cursor = fgetc(src);
                    }
                    comma++;
                }
                if (cursor == '\n')
                    fprintf(cpy, "\n");
            }
        }
    }
    fclose(src);
    fclose(cpy);

    //copying cpy.txt to stocks.txt
    cpy = fopen("stocks.txt", "w+");
    src = fopen("cpy.txt", "r+");
    cursor = fgetc(src);
    while (cursor != EOF)
    {
        fprintf(cpy, "%c", cursor);
        cursor = fgetc(src);
    }
    fclose(src);
    fclose(cpy);
}

int file_ops(int p_nbr)
{
    int n = 1;
    int pid;
    int sid;

    while (n > 0 && n < 8)
    {
        printf("\n\n--->FILE OPERATIONS<----\n");
        printf("************************\n");
        printf("* 1) Add product       *\n");
        printf("* 2) Delete product    *\n");
        printf("* 3) Update product    *\n");
        printf("* 4) Add feature       *\n");
        printf("* 5) Add stock         *\n");
        printf("* 6) Delete stock      *\n");
        printf("* 7) Update stock      *\n");
        printf("* 8) Back to menu      *\n");
        printf("************************\n");
        printf("Choose an operation: ");
        scanf("%d", &n);
        switch(n)
        {
            case 1:
                add_product(p_nbr);
                p_nbr++;
                break;
            case 2:
                printf("Enter the pID that you want to delete: ");
                scanf("%d", &pid);
                if (p_nbr == 0 || pid > p_nbr || pid <= 0)
                {
                    printf("invalid pid\n");
                    break;
                }
                if (delete_product(pid, p_nbr, "products.txt") == 1)
                    p_nbr--;
                break;
            case 3:
                update_product(p_nbr);
                break;
            case 4:
                add_feature(p_nbr);
                break;
            case 5:
                add_stock(p_nbr);
                break;
            case 6:
                printf("Enter the sID that you want to delete: ");
                scanf("%d", &sid);
                delete_stock("stocks.txt", sid);
                break;
            case 7:
                update_stock(p_nbr);
                break;
            case 8:
                printf("Returning back to the menu....\n\n\n");
                return (p_nbr);
                break;
        }
    }
    return (p_nbr);
}