
compilar: FB DC P2
	g++ Parte1_FB.o -o Parte1_FB
	g++ Parte1_DC.o -o Parte1_DC
	g++ Parte2.o -o Parte2

FB: Parte1_FB.cpp
	g++ -c Parte1_FB.cpp -Wall

DC: Parte1_DC.cpp
	g++ -c Parte1_DC.cpp -Wall

P2: Parte2.cpp
	g++ -c Parte2.cpp -Wall

ejecutarDC: Parte1_DC
	./Parte1_DC

ejecutarFB: Parte1_FB
	./Parte1_FB

ejecutar2: Parte2
	./Parte2



clear:
	rm -r Parte1_FB \
	Parte1_DC Parte2 Parte1_FB.o Parte1_DC.o Parte2.o


