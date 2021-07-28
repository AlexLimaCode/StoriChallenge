#include<iostream>
#include<conio.h>
#include<stdio.h>
using namespace std;

void inicializa(int rectangles[][3], int n){
	int c= sizeof(rectangles[0])/sizeof(*rectangles[0]);
	for(int i=0; i<n; i++){
		for(int j=0; j<c; j++){
			//Inicializo la matriz en -1 por que jamas habra valores negativos pero si puede existir una coordenada 0
			rectangles[i][j]=-1;
		}
	}
}

void insertData(int rectangles[][3], int n){
	for(int i=0; i<n; i++){
		//No hay valores negativos
		while(rectangles[i][0]<0){
			cout<<"Please, Insert the initial point of the "<<i+1<<" rectangle"<<endl;
			cin>>rectangles[i][0];
		}
		//El segundo valor nunca puede ser menor que el inicial, por eso el while
		while(rectangles[i][1]<rectangles[i][0]){
			cout<<"Please, Insert the end point of the "<<i+1<<" rectangle"<<endl;
			cin>>rectangles[i][1];
		}
		//No hay altura negativa
		while(rectangles[i][2]<0){
			cout<<"Please, Insert the height point of the "<<i+1<<" rectangle"<<endl;
			cin>>rectangles[i][2];
		}
		
	}
}

void orderBy(int rectangles[][3], int n){
	int arrMenor[1][3];
	for(int i=0; i<n; i++){
		if(i+1<n){
			for(int j=i+1; j<n; j++){
				if(rectangles[i][0]>rectangles[j][0]){
					for(int k=0; k<3; k++){
						arrMenor[0][k] = rectangles[i][k];
						rectangles[i][k] = rectangles[j][k];
						rectangles[j][k] = arrMenor[0][k];
					}
				}
			}
		}
	}
}

void determineLength(int rectangles[][3], int n){
	int rightExtPoint = 0;
	bool flag=false;
	for(int i=0; i<n; i++){
		//PARA QUE EN EL ULTIMO ELEMENTO NO ME MARQUE UN OUT OF BONUS
		if(i+1<n){
			if(rectangles[i+1][0]<=rectangles[i][1]){
				if(rectangles[i][1]<=rectangles[i+1][1]){
					rightExtPoint = rectangles[i+1][1];
				}
			}else{
				cout<<"("<<rightExtPoint<<",0)"<<endl;
			}
		}else if(i+1==n){
			for(int j=0; j<i; j++){
				if(rectangles[i][0]>=rectangles[j][0] && rectangles[i][0]<rectangles[j][1]){
					cout<<"("<<rectangles[i][1]<<",0)"<<endl;
					flag=true;
				}
			}
			if(!flag){
				if(rectangles[i][0]>rectangles[i-1][0]){
					cout<<"("<<rectangles[i][1]<<",0)"<<endl;
				}
			}
		}
		
	}
	
}
void findSameBlock(int rectangles[][3], int n, int p){
	int counter = 0;
	//Buscare por linea de inicio y linea de corte
	for(int i=0; i<n; i++){
		if(i!=p){
			if(rectangles[p][0]>=rectangles[i][0] && rectangles[p][0]<rectangles[i][1]){//Esta entre estos puntos
				if(rectangles[i][2]>rectangles[p][2]){
					cout<<"("<<rectangles[i][1]<<","<<rectangles[p][2]<<")"<<endl;
					counter++;
				}
			}
			
		}
	}
	//QUIERE DECIR QUE NO ESTUVO ENTRE EEDIFICIOS
	if(counter==0){
		cout<<"("<<rectangles[p][0]<<","<<rectangles[p][2]<<")"<<endl;
	}
	
}

void leftPoint(int rectangles[][3], int n){
	
	for(int i=0; i<n; i++){
		findSameBlock(rectangles, n, i);
	}
	
}

int main() {
	int n,li,ri,hi=0;
	//Solicito el numero de edificios que ingresara el usuario para asi poder usar un array
	cout<<"Insert how many rectangles you have"<<endl;
	cin>>n;
	//Defino la matriz
	int rectangles[n][3];
	inicializa(rectangles,n);
	//Llamo a la funcion donde insertaran los datos
	insertData(rectangles, n);
	//Prefiero ordenar los rectangulos por la coordenada inicial para con ello facilitar las funciones siguientes
	orderBy(rectangles, n);
	// Determino las islas compuestas por los edificios que esten juntos
	determineLength(rectangles, n);
	//Llamo a la funcion donde estan los puntos de la izquierda
	leftPoint(rectangles, n);
}
