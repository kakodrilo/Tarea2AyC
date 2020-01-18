#include <bits/stdc++.h>
using namespace std;

/*
shifteo: agrega 0's a un string a la izquierda o a la derecha.
----
recibe el string al que se le agregarán 0's, un int indicando la cantidad de 0's a agregar
y un int indicando en que lado del string se agregarán los 0's (0: izquierda; 1: derecha).
----
retorna el string con los 0's agregados.
*/
string shifteo(string numero, int cantidad, int direccion){
    int i;
    for (i = 0; i < cantidad; i++){
        if (direccion == 0){ // izquierda
            numero = "0"+numero;
        }
        else{ // derecha
            numero = numero + "0";
        }
    }
    return numero;
}

/*
suma2: suma binaria con numeros de largo 1.
----
recibe dos char que representan a los numeros a sumar. Deben ser '0' o '1'.
----
retorna el string resultante de la suma, 0 o 1, o 2 en caso de que se genere un overflow.
*/
string suma2(char x, char y){
    if (x == '1'){
        if (y == '1'){ // el resultado es 0 con un overflow.
            return "2";
        }
        else{ // la suma es '1' + '0' = "1"
            return "1";
        }
    }
    else{ 
        if (y == '1'){ // la suma es '0' + '1' = "1"
            return "1";
        }
        else{ // la suma es '0' + '0' = "0"
            return "0";
        }
        
    }
    
}


/*
suma: suma binaria entre dos numeros de largo variable.
----
recibe dos string en representación de los números a sumar.
----
retorna el string resultante de la suma binaria.
*/
string suma(string x, string y){
    int n,i,s,ov=0;
    string h,r="";

    /* se calcula la diferencia de largo de los numeros a sumar*/
    s = x.length()-y.length();

    /* según el resultado se realiza un shifteo a los números para que sean del mismo largo */
    if (s > 0){
        y = shifteo(y,s,0);
    }
    else if(s < 0){
        x = shifteo(x,-s,0);
    }

    n = x.length();

    /* se itera sobre los numeros. Desde el bit menos significativo al más significativo */
    for( i = n-1; i >= 0; i--){
        /* se realiza la suma de ambos bit, uno de cada numero binario */
        h = suma2(x[i],y[i]);

        /* se trabaja el resultado según las siguientes condiciones*/
        if (ov == 1){  // hay overflow de la suma anterior
            if (h == "2"){ // hay overflow de la suma actual
                r = "1"+r;
                ov = 1;
            }
            else{   // no hay ov en la suma actual
                h = suma2('1',h[0]); // se suma el oerflow de la suma anterior
                if (h == "2"){  // se genera un overflow
                    r = "0"+r;
                    ov = 1;
                }
                else{  // no se genera overflow
                    r = "1" + r;
                    ov = 0;
                }
                
            }
        }
        else{  // no hay overflow de la suma anterior
            if (h == "2"){ // hay overflow en la suma actual
                r = "0" + r;
                ov = 1;
            }
            else{ // no hay overflow en la suma actual
                r = h + r;
                ov = 0;
            }
        }
    }
    /* en caso de que se produzca overflow a final, se agrega al resultado*/
    if(ov == 1){
        r = "1" + r;
    }
    return r;
}

string multiplicar2(char x, char y){
    if (x == '1' && y == '1'){
        return "1";
    }
    else{
        return "0";
    }
}

string multiplicar(string x, string y, int n){
    if (n == 1){
        return multiplicar2(x[0],y[0]);
    }
    else{
        int i,j;
        string r1, r2 = "0",m;
        
        int shif = 0;

        for ( i = n-1; i >= 0; i--){
            r1 = "";
            for ( j = 0; j < n; j++){
                m = multiplicar2(x[i],y[j]);
                r1 = r1 + m;
            }
            r1 = shifteo(r1,shif,1);
            shif++;
            r2 = suma(r2,r1);
        }
         /* se eliminan los 0´s inncesarios delante del resultado */
        bool flag = true;
        while(flag){
            if(r2.length() == 1){
                flag = false;
            }
            else if(r2[0] == '0'){
                r2.erase(0,1);
            }
            else{
                flag = false;
            }
        }
        return r2;
    }
}

int main(){
    int n;
    string x, y;
    while(scanf("%d",&n) != EOF){
        cin >> x;
        cin >> y;
        cout << multiplicar(x, y,n) << '\n';
    } 
    return 0;
} 