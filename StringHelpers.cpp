#include <string.h>
#include "StringHelpers.h"

char* strsep(char** stringp, const char* delim)
{
    char *rv = *stringp;

    if (rv)
    {
        *stringp += strcspn(*stringp, delim);

        if (**stringp)
        {
            *(*stringp)++ = '\0';
        }
        else
        {
            *stringp = 0;
        }
    }

    return rv;
}


/*

NOTA:

Neste projeto, optou-se por utilizar o strsep() ao inv�s do strtok(). A raz�o para isso � que o strsep() consegue  lidar com campos
vazios, diferente do strtok(). Inclusive, o strsep() foi implementado para ser um substituto do  strtok(), devido � esse problema dos
campos vazios. Leia mais sobre isso na seguinte p�gina:
https://refspecs.linuxbase.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/baselib-strsep-3.html .

Entretanto, o compilador utilizado durante o desenvolvimento deste projeto n�o possui suporte ao strsep() e, devido a isso, o strsep()
foi implementado neste arquivo StringHelpers.cpp. O c�digo dessa implementa��o foi extra�do da seguinte p�gina:
https://stackoverflow.com/questions/58244300/getting-the-error-undefined-reference-to-strsep-with-clang-and-mingw .

*/
