#include <bits/stdc++.h>
using namespace std;

/* se defien un tipo de dato que representará a los nodos del arbol*/
typedef struct nodo{
    int valor;
    int padre;
}nodo;


/*
guardar: lee la representación del árbol através de parentesis y guarda los nodos en preorden
con la posición de dónde se sencuentra su padre.
----
recibe un arreglo de nodos en donde se almacenarán los elementos del árbol y un entero 
indicando la cantidad de elementos.
----
no tiene ningún tipo de retorno.
*/
void guardar(int t,nodo * arreglo){
    int i,posicion=1,distancia = 0;
    int abre=1,cierra=0;
    char arbol[2*t];

    /* se lee la representación del árbol */
    scanf("%s",arbol);

    /* se guarda la raiz asignadondsele un padre en la posición -1*/
    arreglo[0].padre=-1;

    /* se recorre el caracter por caracter la representación del árbol */
    for(i = 1; i < 2*t; i++){
        if (arbol[i]=='('){ // si hay un abre-parentesis se debe agregar un nodo al arreglo
            if (abre - cierra == 1){ // si el nodo a agregar es un hijo de la raíz
                arreglo[posicion].padre = 0;
            }
            else if(arbol[i-1]=='('){ // si el nodo es hijo del último nodo agregado
                arreglo[posicion].padre = posicion-1;
                distancia = 0;
            }
            else if (arbol[i-1]==')'){ // si el nodo es hermano de un nodo ya agregado
                if (arbol[i-2] == '('){ // si el hermano es el último nodo agregado
                    arreglo[posicion].padre =  arreglo[posicion-1].padre;
                }
                else{ // el hermano debe ser buscado en el arreglo
                   arreglo[posicion].padre =  arreglo[posicion-distancia].padre;
                }
            }
            abre++;
            posicion++;
        }
        else if (arbol[i]==')'){ //
            cierra++;
            distancia++;
        }
    }
    /*for ( i = 0; i < t; i++){
        cout << "soy el nodo "<<i<<" mi padres está en "<<arreglo[i].padre<<"\n";
    }*/
}

/*
guardar2: guarda los valores de los nodos del arbol presentados en preorden.
----
recibe la canidad de elemntos a guardar y el arreglo ya previamente ordenado donde se guardarán los valores.
----
no tiene retornos.
*/
void guardar2(int t,nodo * arreglo){
    int i;
    for (i = 0; i < t; i++){
        cin >> arreglo[i].valor;
    }
}

int main(){
    int tamano, i, Q, v, P, ans, flag;
    while (scanf("%d",&tamano) != EOF) {
        nodo * arreglo = (nodo *)malloc(sizeof(nodo)*tamano);
        guardar(tamano,arreglo);
        guardar2(tamano,arreglo);
       
        scanf("%d", &Q);
        printf("%d\n", Q);
        
        
        for(i = 0; i < Q; i++){
            flag = 1;
            ans = 0;
            scanf("%d %d", &v, &P);
            while(flag){
                if(v == 0){
                    flag = 0;   
                }
                if(arreglo[v].valor >= P){
                    ans = v;
                }
                v = arreglo[v].padre;
            }
            printf("%d\n", ans);
        }
        free((void*)arreglo);
    }
    return 0;
}

