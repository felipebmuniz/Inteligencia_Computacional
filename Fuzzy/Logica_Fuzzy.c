#include <stdio.h>
#include<math.h>

int main() {
    float p, vc, vr;
    printf("Passe em ordem os a seguir: \nPressao dos freios: ");
    scanf("%f", &p);
    printf("Velocidade do carro: ");
    scanf("%f", &vc);
    printf("Velocidade da roda: ");
    scanf("%f", &vr);

    //Definição da pressão dos freios nas condições dadas no exemplo
    int i;
    float pressao_S_M_F[] = {((-0.6*p+30)/30),((30-abs((p-50)*1.5))/30),(((0.6*p)-30)/30)};

    for (i = 0; i < 3; i++) {
        if (pressao_S_M_F[i] < 0) {
            pressao_S_M_F[i] = 0;
        }
    }

    //Definição da veloocidade das rodas nas condições dadas no exemplo
    float vrodas_S_M_F[] = {((-0.5*vr+30)/30),((30-abs((vr-50)))/30),((0.5*vr-20)/30)};
    for (i = 0; i < 3; i++) {
        if (vrodas_S_M_F[i] < 0) {
            vrodas_S_M_F[i] = 0;
        }
    }

    //Definição da velocidade do carro nas condições dadas no exemplo
    float vcarro_S_M_F[] = {((-0.5*vc+30)/30),((30-abs((vc-50)))/30),((0.5*vc-20)/30)};
    for (i = 0; i < 3; i++) {
        if (vcarro_S_M_F[i] < 0) {
            vcarro_S_M_F[i] = 0;
        }
    }

    float Regra1 = pressao_S_M_F[1];

    float Regra2;
    if ((pressao_S_M_F[2] < vcarro_S_M_F[2]) && (pressao_S_M_F[2] < vrodas_S_M_F[2])) {
        Regra2 = pressao_S_M_F[2];
    } else if ((vcarro_S_M_F[2] < pressao_S_M_F[2]) && (vcarro_S_M_F[2] < vrodas_S_M_F[2])) {
        Regra2 = vcarro_S_M_F[2];
    } else {
        Regra2 = vrodas_S_M_F[2];
    }

    float Regra3;
    if ((pressao_S_M_F[2] < vcarro_S_M_F[2]) && (pressao_S_M_F[2] < vrodas_S_M_F[0])) {
        Regra3 = pressao_S_M_F[2];
    } else if ((vcarro_S_M_F[2] < pressao_S_M_F[2]) && (vcarro_S_M_F[2] < vrodas_S_M_F[0])) {
        Regra3 = vcarro_S_M_F[2];
    } else {
        Regra3 = vrodas_S_M_F[0];
    }

    float Regra4 = pressao_S_M_F[0];

    printf("\n%f %f %f\n\n%f %f %f\n\n%f %f %f\n\n %f %f %f %f\n", pressao_S_M_F[0], pressao_S_M_F[1], pressao_S_M_F[2], vcarro_S_M_F[0], vcarro_S_M_F[1], vcarro_S_M_F[2], vrodas_S_M_F[0], vrodas_S_M_F[1], vrodas_S_M_F[2], Regra1, Regra2, Regra3, Regra4);

    float apertarFreio = (Regra1 + Regra2)*30;
    float liberarFreio = (Regra3 + Regra4)*30;

    double Superior = 0.0;
    double Inferior = 0.0;
    double pa[100];
    int x;
    for(x = 0; x <= 100; x++) {
        double func_A = 0.0;
        double func_L = 0.0;
        double auxA = apertarFreio;
        if (x >= 0 && x <= ((10*auxA)/3)) {
            func_A = x * 0.3;
        } else {
            func_A = auxA;
        }
        double auxL = liberarFreio;
        if (x >= 0 && x <= (((-10)*auxL + 300)/3)) {
            func_L = auxL;
        } else {
            func_L = (-0.3) * x + 30;
        }

        if (func_A >= func_L) {
            pa[x] = func_A;
        } else {
            pa[x] = func_L;
        }
    }

    for (i = 0; i <= 100; i++) {
        Superior = (Superior + pa[x])*x;
        Inferior += pa[x];
    }
    printf("\nPressao final: %lf\n", (Superior/Inferior));
}