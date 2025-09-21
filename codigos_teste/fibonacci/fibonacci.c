#include <stdio.h>

int fibonacci_recursivo (int num_fibo){

    if (num_fibo <= 1){
        return num_fibo;
    }

    return fibonacci_recursivo(num_fibo - 1) + fibonacci_recursivo(num_fibo - 2);
}

int fibonacci_iterativo (int num_fibo){

    long long a = 0, b = 1, proximo;

    for(int i = 2; i <= num_fibo; i++){
        proximo = a + b;
        a = b;
        b = proximo;
    }

    return b;
}

int main (){
    int num_fibo, op;

    printf("Escreva o número da sequência Fibonacci a ser calculado (Ex: 50): ");
    scanf("%d",&num_fibo);

    if (num_fibo < 0) {
        printf("O número deve ser não-negativo.\n");
        return 1;
    }

    printf("Qual método calcular o número de Fibonacci? \n");
    printf("1 - Recursivo (mais consumo de memória) \n");
    printf("2 - Iterativo (mais eficiente) \n");
    scanf("%d",&op);


    switch(op){

        case 1:{
            printf("Calculando F(%d) usando o método recursivo...\n", num_fibo);
            long long resultado_rec = fibonacci_recursivo(num_fibo);
            printf("O número de Fibonacci na posição %d é: %lld\n", num_fibo, resultado_rec);
            return 1;
        }

        case 2:{
            printf("Calculando F(%d) usando o método iterativo...\n", num_fibo);
            long long resultado_it = fibonacci_iterativo(num_fibo);
            printf("O número de Fibonacci na posição %d é: %lld\n", num_fibo, resultado_it);
            return 1;
        }
        default:
            printf("Opção inválida. Escolha 1 ou 2.\n");
            return 1;
    }

    return 0;
}

