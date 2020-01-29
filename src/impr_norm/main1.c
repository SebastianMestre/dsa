#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void imprimir_normalizado ( char str[] ) {
	enum Accion {
		imprimir_directo = 0,
		imprimir_mayus,
		imprimir_minus,
		imprimir_barra_n,
		imprimir_nada
	};

	enum Estado {
		letra = 0,
		espacio,
		terminador
	};

	int transiciones[3][3] = {
		{imprimir_minus,   imprimir_directo, imprimir_barra_n}, // Letra -> ( Letra, Espacio, Terminador)
		{imprimir_directo, imprimir_nada,    imprimir_barra_n}, // Espacio -> ( Letra, Espacio, Terminador)
		{imprimir_nada,    imprimir_nada,    imprimir_nada   }  // Terminador -> ( Letra, Espacio, Terminador)
	};
	
	enum Estado estado;
	if      ( str[0] == '\0' ) estado = terminador;
	else if ( str[0] == ' '  ) estado = espacio;
	else                       estado = letra;
	
	enum Accion accion = transiciones[espacio][estado];

	while ( true ) {
		switch(accion){
			case imprimir_directo: putchar(str[0]);          break;
			case imprimir_mayus:   putchar(toupper(str[0])); break;
			case imprimir_minus:   putchar(tolower(str[0])); break;
			case imprimir_barra_n: putchar('\n'); return;    break;
			case imprimir_nada:                              break;
		}
		
		int siguiente;
		if      ( str[1] == '\0' ) { siguiente = terminador; }
		else if ( str[1] == ' '  ) { siguiente = espacio;    }
		else                       { siguiente = letra;      }

		accion = transiciones[estado][siguiente];
		estado = siguiente;
		str = str + 1;
	}
}	


int main() {
    imprimir_normalizado("   hOLA  ComO    Va");

    return 0;
}


