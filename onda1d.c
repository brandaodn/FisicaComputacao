#include<stdio.h>
#include<math.h>
#include<stdlib.h>

//espaco geometrico
#define x0 0
#define xn 10
#define n 1000 // quantos pontos teremos entre 0 e 10

//espaco temporal
#define tinicial 0
#define tfinal 10
#define insttempo 1000 // quantos instantes de tempo estamos simulando





float f(float x);// condicao inicial ou seja o nosso pulso central na corda

float veloc(float x);// nosso c ou seja a velocidade de propagacao da onda no meio

//float exact_solution(float x, float t);

int main(void){
  FILE *arq;
  float c, **u,t, gama, deltat, deltax, pulso;
  int i,j;

  arq = fopen("onda1d02.dat","w");


//alocacao dinamica da matriz
  u =(float **)malloc((n+1)*(sizeof(float *)));
  if(u==NULL){//verifica se alocou as linhas
       printf("Error: Invalid variable");
       return 0;
   }
  for (i=0; i<n;i++){
	  u[i]=(float *)malloc((insttempo)*(sizeof(float)));
	  
	  if(u[i]== NULL){// verifica se alocou as colunas
       printf("Error: Invalid variable");
       return 0;
    }
  }

  //fim da alocacao dinamica da matriz

//-------------------------
//PROBLEMS INFORMATION
//-------------------------
   //discretizacao espacial
     deltax= (float)(xn-x0)/(float)n;
   
   //discretizacao temporal
     t = tinicial;
     deltat= (float)(tfinal - tinicial)/(float)insttempo;

     //posicao do pulso inicial no eixo x
     pulso = (xn - x0) / 2.0;

     //retirando lixo de memoria da matriz
     for (i=0;i<n;i++)
        for (j=0;j<insttempo;j++)
            u[i][j]=0.0;

	printf("Delta x = %5.5f \n", deltax);
	printf("Delta t = %5.5f \n", deltat);
	printf("Courant Number = %5.5f \n", deltax/deltat);
   

   //condicao inicial do problema ou seja posicionando o nosso pulso
   for(i=1;i<n-1;i++){
      u[i][0] = f( i * deltax - pulso);
      gama = (veloc( i * deltax - pulso) * veloc( i * deltax - pulso)) *(deltat * deltat) / (deltax * deltax);
      u[i][1] = (1.0 - gama) * f( i * deltax-pulso) 
               + gama/2.0 * ( f( (i+1) * deltax-pulso) + f(( (i-1) * deltax-pulso)));
    }



//agora vamos calcular todos os instantes de tempo da simulacao
  for (j=1;j<insttempo-1;j++){
  	// agora vamos calcular todos os valores para a onda nos pontos do espaco (x)
      for (i=1;i<n-1;i++){
             //gama = c^2* deltat^2/deltax^2
             gama = (veloc( i * deltax-pulso) * veloc( i * deltax-pulso)) *(deltat * deltat) / (deltax * deltax);
	       u[i][j+1] = gama * (u[i+1][j] + u[i-1][j]) - u[i][j-1] + 2.0 * (1.0 - gama) * u[i][j];
		}//agora percorremos todos os pontos no eixo x
 //partindo pra proxima itercao no tempo
}



 // imprimindo o resultado da simulacao em um arquivo
// observe que a primeira coluna do arquivo contem a discretizacao espacial x (x=0, x=0.01, x=0.02,.....x=10)
  for(i=0;i<n;i++){
    fprintf(arq, " %2.3f  ",(float)i*deltax);
    for(j=0;j<insttempo;j++){
        fprintf(arq,"%2.5f  ", u[i][j]);
      }
     fprintf(arq,"\n");
  }

  fclose(arq);
 return 0;
}



float f(float x){
  float r;
   if ((x<1.0)&&(x>-1.0)){
        r =1.0;
   }
   else{
          r = 0.0;
   }
 return r;


}

float veloc(float x){ //na equacao eh o nosso C
    float valor;
	if(x>1.0) valor = 2.0;
       	else valor = 1.0;
       //testem com o seguinte valor
	   //if(x>1.0) valor = 0.8;
  	   //else valor = 1.0;
	

return valor;
}






