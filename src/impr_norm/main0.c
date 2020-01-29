#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void terminador ( char str[] );

void principio_letra ( char str[] );
void espacio_letra ( char str[] );
void letra_letra ( char str[] );

void principio_espacio ( char str[] );
void espacio_espacio ( char str[] );
void letra_espacio ( char str[] );

void terminador ( char str[] ) {
    putchar('\n');
    return;
}

void principio_letra ( char str[] ) {
    putchar(toupper(str[0]));
    if (str[1] == '\0')     return terminador( str+1 );
    else if (str[1] == ' ') return letra_espacio( str+1 );
    else                    return letra_letra( str+1 );
}
void espacio_letra ( char str[] ) {
    putchar(toupper(str[0]));
    if (str[1] == '\0')     return terminador( str+1 );
    else if (str[1] == ' ') return letra_espacio( str+1 );
    else                    return letra_letra( str+1 );
}
void letra_letra ( char str[] ) {
    putchar(tolower(str[0]));
    if (str[1] == '\0')     return terminador( str+1 );
    else if (str[1] == ' ') return letra_espacio( str+1 );
    else                    return letra_letra( str+1 );
}

void principio_espacio ( char str[] ) {
    if (str[1] == '\0')     return terminador( str+1 );
    else if (str[1] == ' ') return espacio_espacio( str+1 );
    else                    return espacio_letra( str+1 );
}
void espacio_espacio ( char str[] ) {
    if (str[1] == '\0')     return terminador( str+1 );
    else if (str[1] == ' ') return espacio_espacio( str+1 );
    else                    return espacio_letra( str+1 );
}
void letra_espacio ( char str[] ) {
    putchar( ' ' );
    if (str[1] == '\0')     return terminador( str+1 );
    else if (str[1] == ' ') return espacio_espacio( str+1 );
    else                    return espacio_letra( str+1 );
}

void imprimir_normalizado ( char str[] ) {
    if (str[0] == '\0')     return terminador( str );
    else if (str[0] == ' ') return principio_espacio( str );
    else                    return principio_letra( str );
}

int main() {
    imprimir_normalizado("   hOLA  ComO    Va");

    return 0;
}
