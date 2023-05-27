#ifndef ERRORS_H
#define ERRORS_H

#include <errno.h>
#include <stdlib.h>
#include <string.h>

//list of handled errors
typedef enum Errors
{
    SUCCESS,
    E_NO_NEWLINE,
    E_WORD_EXPECTED_REDIRECT,
    E_CLOSE_EXPECTED,
    E_WORD_OR_OPEN_EXPECTED,
	ENUM_ERRORS_END
}Errors;

//returns a string indicating an error
const char *error_message(int error);

#endif
