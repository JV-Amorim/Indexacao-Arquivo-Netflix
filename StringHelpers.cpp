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

Neste projeto, optou-se por utilizar o strsep() ao invés do strtok(). A razão para isso é que o strsep() consegue  lidar com campos
vazios, diferente do strtok(). Inclusive, o strsep() foi implementado para ser um substituto do  strtok(), devido à esse problema dos
campos vazios. Leia mais sobre isso na seguinte página:
https://refspecs.linuxbase.org/LSB_5.0.0/LSB-Core-generic/LSB-Core-generic/baselib-strsep-3.html .

Entretanto, o compilador utilizado durante o desenvolvimento deste projeto não possui suporte ao strsep() e, devido a isso, o strsep()
foi implementado neste arquivo StringHelpers.cpp. O código dessa implementação foi extraído da seguinte página:
https://stackoverflow.com/questions/58244300/getting-the-error-undefined-reference-to-strsep-with-clang-and-mingw .

*/
