#include "includes/ft_printf.h"
#include <stdio.h>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "");
    int c = 42;
	int d = 5;
	int e = 4;
	int a =  printf("%s", 'c');
    //int b =  printf("%.30f", 10000000.25558476549);

   // printf("\na = [%i]",a);
    //printf("\nb = [%i]\n", b);

/*
    a =  ft_printf("%4.S\n", L"我是一只猫。");;
    b =   printf("%4.S\n", L"我是一只猫。");;

    printf("a = [%i]",a);
    printf("\nb = [%i]\n", b);*/

/*
     a =  ft_printf("%15.3s\n", "I am 42");
     b =   printf("%15.3s\n", "I am 42");

    printf("a = [%i]",a);
    printf("\nb = [%i]\n", b);

    a =  ft_printf("%15.2s\n", "I am 42");
    b =   printf("%15.2s\n", "I am 42");

    printf("a = [%i]",a);
    printf("\nb = [%i]\n", b);

    a =  ft_printf("%15.1s\n", "I am 42");
    b =   printf("%15.1s\n", "I am 42");

    printf("a = [%i]",a);
    printf("\nb = [%i]\n", b);

    a =  ft_printf("%15.0s\n", "I am 42");
    b =   printf("%15.0s\n", "I am 42");

    printf("a = [%i]",a);
    printf("\nb = [%i]\n", b);*/
    return (0);
}

/*
 * printf("%15.4s", "42")
15 - 4 = 11
15 - 3 = 12
15 - 2 = 13
15 - 1 = 14
15 - 0 = 15

4 - 7 = -3
3 - 7 = -4
2 - 7 = -5
*/
