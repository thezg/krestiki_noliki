#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<Windows.h>
#include<string.h>
#include<conio.h>

int vivodpole(char *a);
int proverka_vvoda(char *pole, int hod_human);
int proverka_na_pobedu(char *pole, int *chekwin);
int searching_winmove_or_blockmove(char *pole, char metkanugn, char metkabreak, int *input_index_cell);
int movekrestik(char *pole, int nomer_free_cell, int *ocenka_kletki);
int movenolik(char *pole, int nomer_free_cell, int *ocenka_kletki);
int hod_kompa(char *pole, int *free_cells, int *ocenka_free_cells, int endindex);

int main()
{
    if (SetConsoleCP(CP_UTF8)==0 || SetConsoleOutputCP(CP_UTF8)==0)
    {
        printf("Error!\n");
        return 0;
    }
    srand(time(NULL));
    char pole[10]={"*********\0"};
    char numbers_of_cells[10]={"012345678\0"};
    int free_cells[8], ocenka_free_cells[8],chekwin=0, nomer_vstavki_nolika, number_input, proverka_na_oshibki, n;
    n=strlen(pole);
    char nolik='0', krestik='x';
    printf("\nВы играете в игру Крестики Нолики. Вы ходите первый за нолики\n");
    printf("номера ячеек\n");
    if (vivodpole(numbers_of_cells)!=0)
    {
        printf("Error! Ошибка при передаче аргументов в функцию при выполнении программы\n");
        printf("Нажмите любую кнопку, чтобы завершить программу\n");
        getch();
        return 0;
    }
    if (vivodpole(pole)!=0)
    {
        printf("Error! Ошибка при передаче аргументов в функцию при выполнении программы\n");
        printf("Нажмите любую кнопку, чтобы завершить программу\n");
        getch();
        return 0;
    }
    int endindex=9;
    while (endindex!=0)
    {
        printf("введите номер ячейки, в которую хотите походить\n");
        scanf("%d",&nomer_vstavki_nolika);
        fflush(stdin);
        proverka_na_oshibki=proverka_vvoda(pole, nomer_vstavki_nolika);
        if (proverka_na_oshibki==2) continue;
        pole[nomer_vstavki_nolika]=nolik;
        endindex=0;
        for (int i=0; i<n; i++)
        {
            if (pole[i]=='*'){
                free_cells[endindex]=i;
                endindex++;
            }
        }
        if (vivodpole(pole)!=0)
        {
            printf("Error! Ошибка при передаче аргументов в функцию при выполнении программы\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
        if (endindex==0)
        {
            printf("Ничья\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
        if (proverka_na_pobedu(pole, &chekwin)!=0)
        {
            printf("Error! Произошла ошибка при передаче аргументов в функцию при выполнении программы\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
        if (chekwin==1)
        {
            printf("Вы победили\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
        if (hod_kompa(pole, free_cells, ocenka_free_cells, endindex)!=0)
        {
            printf("Error! Произошла ошибка при передаче аргументов в функцию при выполнении программы\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
        if (vivodpole(pole)!=0)
        {
            printf("Error! Произошла ошибка при передаче аргументов в функцию при выполнении программы\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
        if (proverka_na_pobedu(pole, &chekwin)!=0)
        {
            printf("Error! Произошла ошибка при передаче аргументов в функцию при выполнении программы\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
        if (chekwin==1)
        {
            printf("Вы проиграли\n");
            printf("Нажмите любую кнопку, чтобы завершить программу\n");
            getch();
            return 0;
        }
    }
    return 0;
}

int vivodpole(char *a)
{
    if (a==NULL) return 1;
    int n=strlen(a);
    if (n==0) return 1;
    for(int i=0; i<9; i+=3)
    {
        printf("+---+---+---+\n");
        printf("| %c | %c | %c |\n",a[i], a[i+1],a[i+2]);
        if (i==6)
            printf("+---+---+---+\n\n");
    }
    return 0;
}
int proverka_vvoda(char *pole, int hod_human)
{
    if (pole==NULL) return 1;
    int n=strlen(pole);
    if (n==0) return 1;
    if (hod_human<0 || hod_human>8)
    {
        printf("вы ввели несуществующий номер ячейки, повторите ввод\n");
        return 2;
    }
    if (pole[hod_human]!='*')
    {
        printf("Эта ячейка уже занята, введите заново\n");
        return 2;
    }
    return 0;
}

int proverka_na_pobedu(char *pole, int *chekwin)
{//проверка на выигрыш
    if (pole==NULL) return 1;
    if (chekwin==NULL) return 2;
    int n=strlen(pole);
    if (n==0) return 1;
    for (int k=0; k<3; k++)
    {//по горизонтали
        if (pole[k*3]==pole[k*3+1] && pole[k*3]==pole[k*3+2] && pole[k*3]!='*')
        {
            *chekwin=1;
            break;
        }
        if (pole[k]==pole[k+3] && pole[k+3]==pole[k+6] && pole[k]!='*')
        { //по вертикали
            *chekwin=1;
            break;
        }
        if (k==2)
        {//по диагоналям
            k+=2;
            if (pole[k]==pole[k-4] && pole[k]==pole[k+4] && pole[k]!='*')
            {
                *chekwin=1;
                break;
            }
            else if(pole[k]==pole[k-2] && pole[k]==pole[k+2] && pole[k]!='*')
            {
                *chekwin=1;
                break;
            }
        }
    }
    return 0;
}

int searching_winmove_or_blockmove(char *pole, char metkanugn, char metkabreak, int *input_index_cell)
{
    if (pole==NULL) return 1;
    if (input_index_cell==NULL) return 4;
    int n=strlen(pole);
    if (n==0) return 1;
    *input_index_cell=-1;
    for (int i=0; i<9; i+=3)
    {
        int k=0, a=0;
        for (int j=0; j<3; j++)
        {
            if (pole[i+j]==metkabreak)
            {
                k=0;
                break;
            }
            else if(pole[i+j]==metkanugn) k++;
            else if(pole[i+j]=='*') a=i+j;
        }
        if (k==2)
        {
            *input_index_cell=a;
            return 0;
        }
    }
    for (int i=0; i<3; i++)
    {
        int k=0, a=0;
        for (int j=0; j<9; j+=3)
        {
            if (pole[i+j]==metkabreak)
            {
                k=0;
                break;
            }
            else if(pole[i+j]==metkanugn) k++;
            else if(pole[i+j]=='*') a=i+j;
        }
        if (k==2)
        {
            *input_index_cell=a;
            return 0;
        }
    }
    int k=0, a=0;
    for (int i=0; i<9; i+=4)
    {
        if (pole[i]==metkabreak)
        {
            k=0;
            break;
        }
        else if (pole[i]==metkanugn) k+=1;
        else if (pole[i]=='*') a=i;
    }
    if (k==2)
    {
        *input_index_cell=a;
        return 0;
    }
    k=0, a=0;
    for (int i=2; i<8; i+=2)
    {
        if (pole[i]==metkabreak)
        {
            k=0;
            break;
        }
        else if (pole[i]==metkanugn) k+=1;
        else if (pole[i]=='*') a=i;
    }
    if (k==2) *input_index_cell=a;
    return 0;
}
int movekrestik(char *pole, int nomer_free_cell, int *ocenka_kletki)
{
    if (pole==NULL) return 1;
    if (ocenka_kletki==NULL) return 3;
    int n=strlen(pole);
    if (n==0) return 1;
    *ocenka_kletki=0;
    int stop=0, chekwin=0;
    char nolik='0', krestik='x';
    pole[nomer_free_cell]=krestik;
    for (int i=0; i<n; i++)
    {
        if (pole[i]=='*') stop++;
    }
    if (proverka_na_pobedu(pole, &chekwin)!=0) return 4;
    if (stop==0 && chekwin==0)
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=0;
        return 0;
    }
    if (chekwin==1)
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=1;
        return 0;
    }
    int winmove=-1, blockmove=-1;
    if (searching_winmove_or_blockmove(pole, nolik, krestik, &winmove)!=0) return 5;
    if (winmove!=-1)
    {
        if (movenolik(pole, winmove, ocenka_kletki)!=0) return 6;
        pole[nomer_free_cell]='*';
        return 0;
    }
    if (searching_winmove_or_blockmove(pole, krestik, nolik, &blockmove)!=0) return 7;
    if (blockmove!=-1)
    {
        if (movenolik(pole, blockmove, ocenka_kletki)!=0) return 8;
        pole[nomer_free_cell]='*';
        return 0;
    }
    int j=0, chek_na_nichiu=0;
    while (j<9)
    {
        if (j==4) j+=2;
        if (pole[j]=='*')
        {
            if (movenolik(pole, j, ocenka_kletki)!=0) return 9;
            if (*ocenka_kletki==-1){
                pole[nomer_free_cell]='*';
                return 0;
            }
            if (*ocenka_kletki==0) chek_na_nichiu++;
        }
        j+=2;
    }
    if (pole[4]=='*')
    {
        if (movenolik(pole, 4, ocenka_kletki)!=0) return 10;
    }
    if (*ocenka_kletki==-1)
    {
        pole[nomer_free_cell]='*';
        return 0;
    }
    j=1;
    while (j<9)
    {
        if (pole[j]=='*')
        {
            if (movenolik(pole, j, ocenka_kletki)!=0) return 11;
            if (*ocenka_kletki==-1)
            {
                pole[nomer_free_cell]='*';
                return 0;
            }
            if (*ocenka_kletki==0) chek_na_nichiu++;
        }
        j+=2;
    }
    if (chek_na_nichiu!=0)
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=0;
        return 0;
    }
    else
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=1;
        return 0;
    }
}

int movenolik(char *pole, int nomer_free_cell, int *ocenka_kletki){
    if (pole==NULL) return 1;
    if (ocenka_kletki==NULL) return 3;
    int n=strlen(pole);
    if (n==0) return 1;
    *ocenka_kletki=0;
    int stop=0, chekwin=0;
    char nolik='0', krestik='x';
    pole[nomer_free_cell]=nolik;
    for (int i=0; i<n; i++)
    {
        if (pole[i]=='*') stop++;
    }
    if (proverka_na_pobedu(pole, &chekwin)!=0) return 4;
    
    if (stop==0 && chekwin==0)
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=0;
        return 0;
    }
    if (chekwin==1)
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=-1;
        return 0;
    }
    int winmove=-1, blockmove=-1;
    if (searching_winmove_or_blockmove(pole, krestik, nolik, &winmove)!=0) return 5;
    if (winmove!=-1)
    {
        if (movekrestik(pole, winmove, ocenka_kletki)!=0) return 6;
        pole[nomer_free_cell]='*';
        return 0;
    }
    if (searching_winmove_or_blockmove(pole, nolik, krestik, &blockmove)!=0) return 7;
    if (blockmove!=-1)
    {
        if (movekrestik(pole, blockmove, ocenka_kletki)!=0) return 8;
        pole[nomer_free_cell]='*';
        return 0;
    }
    int j=0, chek_na_nichiu=0;
    while (j<9)
    {
        if (pole[j]=='*')
        {
            if (movekrestik(pole, j, ocenka_kletki)!=0) return 9;
            if (*ocenka_kletki==1)
            {
                pole[nomer_free_cell]='*';
                return 0;
            }
            if (*ocenka_kletki==0) chek_na_nichiu++;
        }
        j+=2;
    }
    int i=1;
    while (i<9)
    {
        if (pole[i]=='*')
        {
            if (movekrestik(pole, i, ocenka_kletki)!=0) return 10;
            if (*ocenka_kletki==1)
            {
                pole[nomer_free_cell]='*';
                return 0;
            }
            if (*ocenka_kletki==0) chek_na_nichiu++;
        }
        i+=2;
    }
    if (chek_na_nichiu!=0)
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=0;
        return 0;
    }
    else
    {
        pole[nomer_free_cell]='*';
        *ocenka_kletki=-1;
        return 0;
    }
}
int hod_kompa(char *pole, int *free_cells, int *ocenka_free_cells, int endindex)
{
    if (pole==NULL) return 1;
    if (free_cells==NULL) return 2;
    if (ocenka_free_cells==NULL) return 3;
    int n=strlen(pole);
    if (n==0) return 1;
    char krestik='x';
    for (int b=0; b<endindex; b++)
    {
        if (movekrestik(pole, free_cells[b], &ocenka_free_cells[b])!=0) return 4;
    }
    int pobednie_kletki[8], kletki_nichiy[8], kolichestvo_pobedn_kletok=0, kolichestvo_nichiy_kletok=0;
    for (int i=0; i<endindex; i++)
    {
        if (ocenka_free_cells[i]==1)
        {
            pobednie_kletki[kolichestvo_pobedn_kletok]=free_cells[i];
            kolichestvo_pobedn_kletok++;
        }
        if (ocenka_free_cells[i]==0)
        {
            kletki_nichiy[kolichestvo_nichiy_kletok]=free_cells[i];
            kolichestvo_nichiy_kletok++;
        }
    }
    if (kolichestvo_pobedn_kletok!=0) pole[pobednie_kletki[rand()%kolichestvo_pobedn_kletok]]=krestik;
    else if (kolichestvo_nichiy_kletok!=0) pole[kletki_nichiy[rand()%kolichestvo_nichiy_kletok]]=krestik;
    else pole[free_cells[rand()%endindex]]=krestik;
    return 0;
}