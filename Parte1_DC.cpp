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

/*
resta: realiza la resta de dos numeros binarios de largo variable con complemento a2.
----
recibe dos string en representación a los números binarios a restar.
----
retorna un string con el resultado de la resta.
*/
string resta(string x, string y){
    int n,i,s;
    bool flag = true;
    string h = "", auxs;
    /* se calcula la diferencia de largo entre los números */
    s = x.length()-y.length();
    /* en caso de que corresponda se realiza un shifteo a uno de los números */
    if (s > 0){
        y = shifteo(y,s,0);
    }
    else if(s < 0){
        s *= -1;
        x = shifteo(x,s,0);
    }
    n = y.length();
    /* se transforma el segundo número a complemento a2 */
    for(i = n-1; i >= 0; i--){
        if(flag){
            if(y[i] == '1'){
                flag = false;
            }
        }
        else{
            if(y[i] == '0'){
                y[i] = '1';
            }
            else{
                y[i] = '0';
            }
        }
    }
    /* se realiza la suma entre los números*/
    h = suma(x,y);

    /* en caso de que haya overflow se elimina el bit más significativo */
    if(h.length() > y.length()){
        h.erase(0,1);
    }
    return h;
}


/*
multiplicar: multiplicación de dos numeros binarios de igual largo.
----
recibe dos string en representción de los numeros a múltiplicar y un entero n indicando el largo de estos.
----
retorna un string con el resultado final de la multliplicación.
*/
string multiplicar(string x,string y,int n){
    /* se define el caso base, en donde el largo es igual a 1*/
    if (n == 1){
        if (x == "1" && y == "1"){
            return "1";
        }
        else{
            return "0";
        }
    }

    int upper, lower = n/2;
    upper = n - lower;
    bool flag = true;
    
    /* se dividen los numeros en 2 partes cada uno*/
    string xl = x.substr(0,upper);
    string yl = y.substr(0,upper);
    string xr = x.substr(upper,lower);
    string yr = y.substr(upper,lower);

    /* se multiplican, recusrivamente, las partes */
    string p1 = multiplicar(xl,yl,upper);
    string p3 = multiplicar(xr,yr,lower);

    /* antes de la tercera multiplicación es necesario realizar la suma*/
    string suma1 = suma(xl,xr);
    string suma2 = suma(yl,yr);
    
    /* se verfica que ambos resultados sean del mismo largo */
    int dif = suma1.length() - suma2.length();
    if (dif > 0){
        suma2 = shifteo(suma2,dif,0);
    }
    else if (dif < 0){
        suma1 = shifteo(suma1,-dif,0);
    }
    /* se multilpica el resultado */
    string p2 = multiplicar(suma1,suma2,suma1.length());

    /* se le restan las partes p1 y p3*/
    p2 = resta(p2,p1);
    p2 = resta(p2,p3);

    /* se realizan los shifteos de las partes 1 y 2 */
    if (n % 2 != 0){ // si n es impar se shiftea la parte 1 a n-1
        p1 = shifteo(p1,n-1,1);
    }
    else{ // si n es par se shiftea a n
        p1 = shifteo(p1,n,1);
    }
    p2 = shifteo(p2,n/2,1);

    /* se suman las partes para obtener el resultado final */
    p1 = suma(p1,p2);
    string respuesta = suma(p1,p3);

    /* se eliminan los 0´s inncesarios delante del resultado */
    while(flag){
        if(respuesta.length() == 1){
            flag = false;
        }
        else if(respuesta[0] == '0'){
            respuesta.erase(0,1);
        }
        else{
            flag = false;
        }
    }
    return respuesta;
    
}

int main(){
    int n;
    string x, y;
    while(scanf("%d",&n) != EOF){
        cin >> x;
        cin >> y;
        cout << multiplicar(x, y, n) << '\n';
    } 
    return 0;
} 