/*
 Aluno: Francisco Gilson Pereira Almeida Filho
 Matricula: 401066
 2020.1

 Enunciado: Construa um programa baseado em l�gica fuzzy (infer�ncia de Mamdani) que receba tr�s
 valores: press�o no pedal, velocidade da roda e velocidade do carro e que devolva a press�o no freio.

 Regras utilizadas:

     Regra1: Se a press�o no pedal for m�dia, ent�o aplicar o freio.
     Regra2: Se a press�o no pedal for alta, e a velocidade da roda e carro forem altas, ent�o aplicar o freio.
     Regra3: Se a press�o no pedal for alta, e a velocidade da roda e carro forem baixar, ent�o liberar o freio.
     Regra4: Se a press�o no pedal for baixa, ent�o liberar o freio.


Rela��es utilizadas:

Entradas:

    Press�o no freio:

    L - [0 - 50]
    M - [30 - 70]
    H - [50 - 100]

    Velocidade nas rodas e carro:

    S - [0 - 60]
    M - [20 - 80]
    F - [40 - 100]

Saidas:

    Aplica freio -
    Libera freio -
    
    
 Obs: Visando facilitar a vizualiza�ao das retas foi utilizado como valor
    maximo 30 ao inves de 1, nos calculos essas unidades s�o convertidas.

*/

//Defini��o de bibliotecas necess�rias
#include<stdio.h>
#include<math.h>


//Fun��o que aplica as regras do input da press�o no freio
double pressao_freio(double pp, int x){
	
	// Defin��o das regras para entrada da pressao
    double L = ((-0.6 * pp)+30);
    double M = (30-(fabs((pp - 50)*3/2)));
    double H = (0.6 * pp)-30;
	
	//Se algum dos valores for menor do que 0 corrige para 0
    if (L < 0){
        L = 0;
    }

    if (M < 0){
        M = 0;
    }

    if (H < 0){
        H = 0;
    }
	
	// Configura para o retorno necessario com base na entrada do paremtro x
	if( x == 1){
		
		return (L/30);
		
	}
	else if( x == 2){
		
		return (M/30);
		
	}
	else if( x == 3){
	
		return (H/30);
		
	}

}

//Fun��o que aplica as regras do input da velocidade do carro
double velocidade_carro(double vc, int x){
	
	// Defin��o das regras para entrada da velocidade do carro
    double S = ((-0.5*vc)+30);
    double M = (30-(fabs((vc-50))));
    double F = ((0.5*vc)-20);
    
	//Se algum dos valores for menor do que 0 corrige para 0
    if (S < 0){
        S = 0;
    }

    if (M < 0){
        M = 0;
    }

    if (F < 0){
        F = 0;
    }
    
    // Configura para o retorno necessario com base na entrada do paremtro x
	if( x == 1){
		
		return (S/30);
		
	}
	else if(x == 2){
		
	    return (M/30);
	    
	}
	else if(x == 3){
		
		return (F/30);
		
	}
}

//Fun��o que aplica as regras do input da velocidade nas rodas
double velocidade_roda(double vr, int x){
	
	// Defin��o das regras para entrada da velocidade da roda
    double S = ((-0.5*vr)+30);
    double M = (30-(fabs((vr-50))));
    double F = ((0.5*vr)-20);
	
	//Se algum dos valores for menor do que 0 corrige para 0
    if (S < 0){
        S = 0;
    }

    if (M < 0){
        M = 0;
    }

    if (F < 0){
        F = 0;
    }
	
	// Configura para o retorno necessario com base na entrada do paremtro x
    if( x == 1){
		
		return (S/30);
		
	}
	else if(x == 2){
		
	    return (M/30);
	    
	}
	else if(x == 3){
		
		return (F/30);
		
	}


}

//Fun��o para analisar a regra1: Se a press�o no pedal for m�dia, ent�o aplicar o freio.
double regra1(double pp,double vr,double vc){
	
	//Chamo a fun��o para press�o freio com o paremetro 2 (M�dio) com base na regra 1
    double pressao = pressao_freio(pp,2);

    return pressao;

}

//Fun��o para analisar a regra2: Se a press�o no pedal for alta, e a velocidade da roda e carro forem altas, ent�o aplicar o freio.
double regra2(double pp,double vr,double vc){
	
	//Chamo as fun��es com os paremetros 3,3,3 com base na regra 2
    double vet_regra2[3] = {pressao_freio(pp,3),velocidade_carro(vc,3),velocidade_roda(vr,3)};
	
	//loop que � usado para pegar o menor valor, com base nas regras do slide
    double menor = 1000;
	int i; 
    for(i=0; i < 3; i++){
      if (vet_regra2[i] <= menor){
          menor = vet_regra2[i];
      }
    }

    return menor;
}

//Fun��o para analisar a regra3: Se a press�o no pedal for alta, e a velocidade da roda e carro forem baixar, ent�o liberar o freio.
double regra3(double pp,double vr,double vc){
	
	//Chamo as fun��es com os paremetros 3,3,1 com base na regra 3
    double vet_regra3[3] = {pressao_freio(pp,3),velocidade_carro(vc,3),velocidade_roda(vr,1)};
	
	//loop que � usado para pegar o menor valor, com base nas regras d
    double menor = 1000;
	int i;
    for(i=0; i < 3; i++){
      if (vet_regra3[i] <= menor){
          menor = vet_regra3[i];
      }	
    }

    return menor;

}

//Fun��o para analisar a regra4: Se a press�o no pedal for baixa, ent�o liberar o freio.
double regra4(double pp,double vr,double vc){
	
	//Chamo a fun��o para press�o freio com o paremetro 1 (baixo) com base na regra 4
    double pressao = pressao_freio(pp,1);

    return pressao;

}

//Fun��o para o caso de aplicar o freio
double aplica_freio(double pp,double vr,double vc){
	
	//Soma o resultado das regras 1 e 2 com base nas regras do slide
    double aplica = regra1(pp,vr,vc) + regra2(pp,vr,vc);
    return aplica*30;
    
}

//Fun��o para o caso de liberar o freio
double libera_freio(double pp,double vr,double vc){
	
	//Soma o resultado das regras 3 e 4 com base nas regras do slide
    double libera = regra3(pp,vr,vc) + regra4(pp,vr,vc);
    return libera*30;
}

//fun�ao final, retorna o valor da reta final para apertar o freio
double pa(int x,double pp,double vr,double vc){
	
	//Valor da fun�ao para o dominio do aplica freio
    double pa_valor1;
    double pa_valor2;
    double valor1 = aplica_freio(pp,vr,vc);
    if(x >= 0 && x<=(10*(valor1/3))){
        pa_valor1 = 0.3*x;
    }
    else{
        pa_valor1 = valor1;
    }

 	 //Valor da fun�ao para o dominio do aplica freio	
    double valor2 = libera_freio(pp,vr,vc);
    if(x >= 0 && x <= (((-10)*valor2 + 300)/3)){
        pa_valor2 = valor2;
    }
    else{
        pa_valor2 = (-0.3)*x + 30;
    }

	//O maior valor entre as duas fun�oes prevalece  na fun�ao final, assim,  � retornado o maior valor.
    if( pa_valor1 >= pa_valor2){
        return pa_valor1;
    }
    else{
        return pa_valor2;
    }
}

int main(){
	
	//Variaveis de entrada
    double pp , vc , vr;
	
	printf("Digite o valor da pressao no pedal: ");
    scanf("%lf", &pp); //Entrada do valor de press�o no pedal
    printf("Digite o valor da velocidade da roda: ");
    scanf("%lf", &vr); //Entrada do valor de velocidade nas rodas
    printf("Digite o valor da velocidade do carro: ");
    scanf("%lf", &vc); //Entrada do valor de velocidade do carro
	
	//Variaveis para o calculo do centro de gravidade
    double c1 = 0;
    double c2 = 0;
    //Variaveis para calculos das pa
	double i,j;
	//Variavel que controla a precis�o 
	double precisao = 1; //Precisao de 1 a 1
	
	//loops que fazem a pa de 0 a 100
    for(i = 0; i <=100; i+=precisao){
        c1 = c1 + ((pa(i,pp,vr,vc)*i));
        c2 = c2 + (pa(i,pp,vr,vc));
    }
    for(j = 0; j <=100; j+=precisao){
       

    }
	
    double c = c1/c2;
	
	//Printa o valor da pressao final do freio
	printf("%lf %lf\n", c1, c2);
    printf("Pressao no freio : %lf\n",c);
    printf("Regra 1: %lf\n",regra1(pp,vc,vr));
    printf("Regra 2: %lf\n",regra2(pp,vc,vr));
    printf("Regra 3: %lf\n",regra3(pp,vc,vr));
    printf("Regra 4: %lf\n",regra4(pp,vc,vr));
	

    return 0;

}

