#include <stdio.h>
#include <stdlib.h>

int main(){

    // variáveis de entrada
    int press;
    int velR;
    int velC;

    /*regras
        1.  se: pressão média;
            então aplicar freio
        2.  se: pressão alta;
            e velocidade do carro alta;
            e velocidade das rodas alta;
            então aplicar freio
        3.  se: pressão alta;
            e velocidade do carro alta;
            e velocidade das rodas baixa;
            então liberar freio
        4.  se: pressão baixa;
            então liberar freio
    */

    // 1ª parte: determinar os valores das variaveis de entrada
    printf("insira os valores de pressao do pedal, velocidade das rodas e velocidade do carro\n");

    printf("pressao do pedal(0-100):\n");
    do{
        scanf("%d", &press);
    }while(press < 0 || press > 100);

    printf("velocidade das rodas(0-100):\n");
    do{
        scanf("%d", &velR);
    }while(velR < 0 || velR > 100);

    printf("velocidade do carro(0-100):\n");
    do{
        scanf("%d", &velC);
    }while(velC < 0 || velC > 100);

    // 2ª parte: determinar os valores das variáveis difusas
    //pressão do pedal

    double pH = 0.0;// H = {(50, 0), (100, 1)}
    double pM = 0.0;// M = {(30, 0), (50,1), (70, 0)}
    double pL = 0.0;// L = {(0, 1), (50, 0)}

    if(press >= 50 && press <=100){
        pH = (press - 50)/50.0;
    }else pH = 0.0;

    if(press >= 30 && press <= 70){
        if(press < 50)
            pM = (press - 30)/20.0;
        else pM = (70 - press)/20.0;
    }else pM = 0.0;

    if(press >= 0 && press <= 50){
        pL = (50 - press)/50.0;
    }else pL = 0.0;


    //velocidade das rodas

    double vrF = 0.0;// F = {(40, 0), (100, 1)}
    double vrM = 0.0;// M = {(20, 0), (50,1), (80, 0)}
    double vrS = 0.0;// S = {(0, 1), (60, 0)}

    if(velR >= 40 && velR <=100){
        vrF = (velR - 40)/60.0;
    }else vrF = 0.0;

    if(velR >= 20 && velR <= 80){
        if(velR < 50)
            vrM = (velR - 20)/30.0;
        else vrM = (80 - velR)/30.0;
    }else vrM = 0.0;

    if(velR >= 0 && velR <= 60){
        vrS = (60 - velR)/60.0;
    }else vrS = 0.0;


    //velocidade do carro

    double vcF = 0.0;// F = {(40, 0), (100, 1)}
    double vcM = 0.0;// M = {(20, 0), (50,1), (80, 0)}
    double vcS = 0.0;// S = {(0, 1), (60, 0)}

    if(velC >= 40 && velC <=100){
        vcF = (velC - 40)/60.0;
    }else vcF = 0.0;

    if(velC >= 20 && velC <= 80){
        if(velC < 50)
            vcM = (velC - 20)/30.0;
        else vcM = (80 - velC)/30.0;
    }else vcM = 0.0;

    if(velC >= 0 && velC <= 60){
         vcS= (60 - velC)/60.0;
    }else vcS = 0.0;


    // 3ª parte: aplicação dos valores nebulosos às regras

    double apertar = 0.0;// regras 1 e 2
    double soltar = 0.0;// regras 3 e 4
    double r1 = 0.0;
    double r2 = 0.0;
    double r3 = 0.0;
    double r4 = 0.0;

    r1 = pM;

    if(pH <= vrF && pH <= vcF){
        r2 = pH;
    }else if(vrF <= pH && vrF <= vcF){
        r2 = vrF;
    }else r2 = vcF;

    if(pH <= vrS && pH <= vcF){
        r3 = pH;
    }else if(vrS <= pH && vrS <= vcF){
        r3 = vrS;
    }else r3 = vcF;

    r4 = pL;

    apertar = r1 + r2;
    soltar = r3 + r4;

    // 4ª parte: encontrar o centróide, este sendo nossa saída desnebulizada

    double x;
    double y;
    double somaS = 0.0;
    double somaI = 0.0;

    //caso apertar seja maior que soltar, levaremos em conta a função ascendente, caso contrário, descendente

    if(apertar > soltar){
        for(x = 0.0; x <= 100.0; x += 0.0001){
            y = x/100.0;
            if(y < soltar){
                somaS += x*soltar;
                somaI += soltar;
            }else if(y >= apertar){
                somaS += x*apertar;
                somaI += apertar;
            }else{
                somaS += x*y;
                somaI += y;
            }
        }
    }else{
        for(x = 0.0; x <= 100.0; x += 0.0001){
            y = (100-x)/100.0;
            if(y > soltar){
                somaS += x*soltar;
                somaI += soltar;
            }else if(y <= apertar){
                somaS += x*apertar;
                somaI += apertar;
            }else{
                somaS += x*y;
                somaI += y;
            }
        }
    }

    printf("O resultado da pressao final eh: %.3lf\n", (somaS/somaI));

}
