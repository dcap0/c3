#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*Struct Declarations*/
typedef struct node {
    char* val;
    struct node* next;
} ll_node;

#define RETURN_KEY "return"

/*Function Declarations*/
ll_node* lex(FILE* file);
bool isReturn(char* rChar);
char* processSingleCharToken(char token);
char* processMultiCharToken(char* token);
ll_node* llInit();
void llAdd(ll_node* head, char* value);
void llFree(ll_node* head);


int main( int argc, char* argv[] )
{
    FILE* filePtr = fopen("./test_files/return_2.c","r+");
    // FILE* filePtr = fopen(argv[1],"r+"); //open file from beginning
    if (filePtr == NULL) {
        fprintf(stderr, "Cannot open file %s\n", argv[1]);
        return 1;
    }
    ll_node* lexed = lex(filePtr);        
    if(lexed == NULL)
    {
        fprintf(stderr, "Error Lexing File %s\n", argv[1]);
        return 2;
    }

    ll_node* current = lexed;
    while(current->next != NULL){
        printf("%s",current->val);
        current = current->next;
    }

    return 0;
}

ll_node* lex(FILE* file)
{
    int check = fseek(file,0,SEEK_END); //file, offset, position moving to.
    if (check != 0) return NULL;

    long size = ftell(file); //get current position in file (size in bytes!)
    rewind(file);

    char* fileStringBuffer = (char*) malloc(size * sizeof(char));
    fread(fileStringBuffer, size, 1, file);
    fclose(file);
    
    // char* retVal; //pointer to first item in array;
    ll_node* retVal = NULL;
    retVal = llInit();
    retVal->next = NULL;
    
    if(retVal == NULL){
        fprintf(stderr, "Lex Error: Could not allocate memory. Terminating\n");
        exit(2);
    }
    size_t i = 0;
    // size_t arrSize = 0;
    while (fileStringBuffer[i] != '\0')
    {
        switch (fileStringBuffer[i])
        {
            case ';':
                llAdd(retVal, processSingleCharToken(';'));
                break;
            case '{':
                llAdd(retVal, processSingleCharToken('{'));
                break;
            case '}':
                llAdd(retVal, processSingleCharToken('}'));
                break;
            case '(':
                llAdd(retVal, processSingleCharToken('('));
                break;
            case ')':
                llAdd(retVal, processSingleCharToken(')'));
                break;
            case 'r':
                if(isReturn(&fileStringBuffer[i]))
                {
                    llAdd(retVal, processMultiCharToken(RETURN_KEY));
                }
                break;
            default:
                break;
        }
        i++;
    }

    free(fileStringBuffer);

    return retVal;
}

char* processSingleCharToken(char token)
{
    char c = token;
    char* ptr = malloc(1);
    if(ptr == NULL) return NULL;
    ptr = &c;
    return ptr;
}

char* processMultiCharToken(char* token){
    char* copy = malloc(strlen(token) + 1);
    strcpy(token,copy);
    return copy;
}

bool isReturn(char* rChar)
{
    bool retVal = true;
    int i = 0;

    while( i < 6 ){
        retVal = (rChar[i] == RETURN_KEY[i]);
        i++;
    }

    return retVal;
}

ll_node* llInit(){
    ll_node* retVal = (ll_node*) malloc(sizeof(ll_node));
    retVal->val = NULL;
    retVal->next = NULL;
    return retVal;
}

void llAdd(ll_node* head, char* value){
    if (head->val == NULL){
        head -> val = value;
    }
    printf("%s",value);
    ll_node* currentNode = head; //set current to head
    while(currentNode->next != NULL){//move to end of ll
        currentNode = currentNode -> next;
    }

    currentNode->next= (ll_node*)malloc(sizeof(ll_node));
    currentNode = currentNode->next;
    currentNode->val=value;
    currentNode->next=NULL;
}

void llFree(ll_node* head){

}

