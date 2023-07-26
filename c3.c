#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum Token{
    RETURN=0,
    SEMICOLON=59,
    OPEN_BRACE=123,
    CLOSE_BRACE=125,
    OPEN_PAREN=40,
    CLOSE_PAREN=41,
    NONE=256,
    END=257
} token_t;


/*Function Declarations*/

bool isReturn(char* rChar);
int* lex(FILE* file);

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

    int* retVal = NULL;

    size_t i = 0;
    size_t arrSize = 0;
    while (fileStringBuffer[i] != '\0')
    {
        int* tempArr = calloc(sizeof(int)+arrSize,sizeof(int));
        if(tempArr == NULL)
        {
            exit(2);
        }
        switch (fileStringBuffer[i])
        {
            case SEMICOLON:
                retVal=tempArr;
                retVal[arrSize] = SEMICOLON;
                arrSize++;
                break;
            case OPEN_BRACE:
                retVal=tempArr;
                retVal[arrSize] = OPEN_BRACE;
                arrSize++;
                break;
            case CLOSE_BRACE:
                retVal=tempArr;
                retVal[arrSize] = CLOSE_BRACE;
                arrSize++;
                break;
            case OPEN_PAREN:
                retVal=tempArr;
                retVal[arrSize] = OPEN_PAREN;
                arrSize++;
                break;
            case CLOSE_PAREN:
                retVal=tempArr;
                retVal[arrSize] = CLOSE_PAREN;
                arrSize++;
                break;
            case 'r':
                if(isReturn(&fileStringBuffer[i]))
                {
                    retVal=tempArr;
                    retVal[arrSize] = RETURN;
                    arrSize++;
                }
                break;
            default:
                break;
        }
        i++;
        free(tempArr);
    }

    free(fileStringBuffer);

    retVal = realloc(retVal, arrSize+1);
    retVal[arrSize+1] = END;

    return retVal;
}

bool isReturn(char* rChar)
{
    bool retVal = true;
    int i = 0;

    char returnStr[6] = {'r','e','t','u','r','n'};

    while( i < 6 ){
        retVal = (rChar[i] == returnStr[i]);
        i++;
    }

    return retVal;
}
