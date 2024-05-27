#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <regex.h>

typedef enum Keyword{
    RETURN=1,
    INT=2,
    IDENT=3,
    SEMICOLON=59,
    OPEN_BRACE=123,
    CLOSE_BRACE=125,
    OPEN_PAREN=40,
    CLOSE_PAREN=41,
    NONE=0,
    END=255
} keyword_t;

typedef struct Tokens{
    int* keywords;
    char* identifiers;
    int* order;
} token_t;

/*Function Declarations*/

bool isKeyword(char* rChar, char* token);
int* lex(FILE* file);

/*Constants*/
const regex_t int_regex;
const regex_t ident;

int main( int argc, char* argv[] )
{

    FILE* filePtr = fopen("./test_files/return_2.c","r+");
    // FILE* filePtr = fopen(argv[1],"r+"); //open file from beginning
    if (filePtr == NULL) {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        return 1;
    }

    int* lexed = lex(filePtr);        
    if(lexed == NULL)
    {
        fprintf(stderr, "Error Lexing File %s\n", argv[1]);
        return 2;
    }

    size_t i = 0;
    while(lexed[i] != END){
        printf("%d\n",lexed[i]);
        i++;
    }

    free(lexed);

    return 0;
}

int* lex(FILE* file)
{
    int check = fseek(file,0,SEEK_END); //file, offset, position moving to.
    if (check != 0) return NULL;

    long size = ftell(file); //get current position in file (size in bytes!)
    rewind(file);

    char* fileStringBuffer = (char*) malloc(size * sizeof(char));
    fread(fileStringBuffer, size, 1, file);
    fclose(file);

    size_t arrSize = 0;
    int* keywords = NULL;
    char* indicators = NULL;

    size_t i = 0;
    while (fileStringBuffer[i] != '\0')
    {
        int* tempArr = (int*) realloc(keywords,sizeof(int)*(arrSize+1));
        switch (fileStringBuffer[i])
        {
            case SEMICOLON:
                keywords = tempArr;
                keywords[arrSize] = SEMICOLON;
                arrSize++;
                break;
            case OPEN_BRACE:
                keywords = tempArr;
                keywords[arrSize] = OPEN_BRACE;
                arrSize++;
                break;
            case CLOSE_BRACE:
                keywords = tempArr;
                keywords[arrSize] = CLOSE_BRACE;
                arrSize++;
                break;
            case OPEN_PAREN:
                keywords = tempArr;
                keywords[arrSize] = OPEN_PAREN;
                arrSize++;
                break;
            case CLOSE_PAREN:
                keywords = tempArr;
                keywords[arrSize] = CLOSE_PAREN;
                arrSize++;
                break;
            case 'r':
                if(isKeyword(&fileStringBuffer[i],"return"))
                {
                    keywords = tempArr;
                    keywords[arrSize] = RETURN;
                    arrSize++;
                }
                break;
            case 'i':
                if(isKeyword(&fileStringBuffer[i],"int")){
                    keywords = tempArr;
                    keywords[arrSize] = INT;
                    arrSize++;
                }
            default:
                break;
        }
        i++;
    }

    free(fileStringBuffer);

    keywords = realloc(keywords, sizeof(int)*(arrSize+1));
    keywords[arrSize] = END;

    return keywords;
}

bool isKeyword(char* rChar, char* token)
{
    bool retVal = true;
    int i = 0;

    while( token[i] != '\0' ){
        retVal = (rChar[i] == token[i]);
        i++;
    }

    return retVal;
}
