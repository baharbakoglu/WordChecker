#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE   200
typedef struct{char ch;} element;

element stack[MAX_STACK_SIZE];
void stack_pop(); /*to get the element from stack*/
void stack_push(char c);/*to put the element from stack*/
int control(char arr[100][7], char c);/* for control of the state*/
int controlread (char arr[100][7],char read, char c);/*for control of the state with words character*/
int find_value(char arr[100][7], char c);/*for find character in states*/
char find_stack_last_value();/*for check element which wants pop*/
int check_character(char *str, char *word);/*check words character and stacks character*/
void find_stack_str(FILE *outputfile);/*for combine elements of the stack*/
int check_last_character(char *str, char c);/*for check last status*/
int find_character(char *str, char c);/*for check inputs are correct*/

int main(int argc,char *argv[])
{
    FILE *inputfile, *inputfile1, *outputfile;
    char buffer[50],inputstate[50],dpdainput[50],lastcharacter[10],characters[2],character[15],startchar;
    char *tempstring, arr[100][7];
    int counter, i=0,j,a,cout,k,charnum,value, zinputcout;
    char state[2], read[1], pop[1], nextstate[2], push[1], AInput[50],ZInput[50],stackchar[50];
    int total=0,top=0;
    if ((outputfile = fopen( argv[3], "w" ) ) == NULL ){/*open write file*/
        printf( "File could not be opened\n" );}
    for(a=0; a<MAX_STACK_SIZE;a++){
        stack[a].ch='\0';
    }
    for(a=0;a<50;a++){
        AInput[a]='\0';
        ZInput[a]='\0';
    }
    for(a=0;a<15;a++){
        lastcharacter[a]='\0';
    }
   if ((inputfile = fopen( argv[1], "r" ) ) == NULL )/*open dpda file*/
        printf( "File could not be opened\n" );
    else
    {
        while(fgets(buffer,sizeof(buffer),inputfile)!=NULL){/*read dpda's line*/
            j=0;
            if(buffer[0]=='Q'){
                for(i=0;i<50;i++)
                {
                   if(buffer[i]=='='){break;}
                }
                for(k=2;k<i;k++){/*for states*/
                    if((buffer[k]==',')||(buffer[k]==' ')){
                            inputstate[top]=buffer[k-1];
                            top++;
                    }
                }
                for(i=0;i<50;i++){
                    if(buffer[i]=='('){/*find start state*/
                       startchar=buffer[i+2];
                       }
                    if(buffer[i]=='['){
                        j++;
                        lastcharacter[j]=buffer[i+2];/*find finish states*/
                    }
                }
            }
            else if(buffer[0]=='A'){
                for(j=0;j<50;j++){
                    buffer[j]=buffer[j+2];
                }
                tempstring = strtok(buffer,",");
                i=0;
                while(tempstring!=NULL){/*find alphabet*/
                    strcpy(characters,tempstring);
                    AInput[i]=characters[0];
                    i++;
                    tempstring=strtok(NULL,",");
                }
            }
            else if(buffer[0]=='Z'){
                for(j=0;j<50;j++){
                    buffer[j]=buffer[j+2];
                }
                tempstring = strtok(buffer,",");
                i=0;
                while(tempstring!=NULL){/*find letters must be in stack*/
                    strcpy(characters,tempstring);
                    ZInput[i]=characters[0];
                    i++;
                    tempstring=strtok(NULL,",");
                }
            }
           else if(buffer[0]=='T'){
                for(j=0;j<11;j++){
                    buffer[j]=buffer[j+2];
                }
                tempstring = strtok(buffer,",");
                counter=1;
                while(tempstring != NULL)/*find functions*/
                {
                    switch(counter)
                    {
                        case 1:{
                                strcpy(state,tempstring);
                                arr[total][0]=state[0];
                                arr[total][1]=state[1];
                                if(find_character(inputstate,state[1])==-1){/*control states are correct*/
                                    fprintf(outputfile,"Error [1]:DPDA description is invalid!"); exit(0);}
                                break;}
                        case 2:{
                                strcpy(read,tempstring);
                                arr[total][2]=read[0];
                                if(read[0]!='e'){
                                    if(find_character(AInput,read[0])==-1){/*control functions are correct*/
                                        fprintf(outputfile,"Error [1]:DPDA description is invalid!"); exit(0);}
                                }
                                break;}
                        case 3:{
                                strcpy(pop,tempstring);
                                arr[total][3]=pop[0];
                                if(pop[0]!='e'){
                                    if(find_character(ZInput,pop[0])==-1){/*control functions are correct*/
                                        fprintf(outputfile,"Error [1]:DPDA description is invalid!"); exit(0);}
                                }
                                break;}
                        case 4:{
                                strcpy(nextstate,tempstring);
                                arr[total][4]=nextstate[0];
                                arr[total][5]=nextstate[1];
                                if(find_character(inputstate,nextstate[1])==-1){/*control states are correct*/
                                    fprintf(outputfile,"Error [1]:DPDA description is invalid!"); exit(0);}
                                break;}
                        case 5:{
                                strcpy(push,tempstring);
                                arr[total][6]=push[0];
                                if(push[0]!='e'){
                                    if(find_character(ZInput,push[0])==-1){/*control functions are correct*/
                                        fprintf(outputfile,"Error [1]:DPDA description is invalid!"); exit(0);}
                                }
                                break;}
                        }
                        counter++;
                        tempstring = strtok(NULL,",");
                    }
                    total++;
            }
            arr[0][0]=arr[0][4];
        }
    }
    if ((inputfile1 = fopen(argv[2], "r" ) ) == NULL )/*open input file*/
        printf( "File could not be opened\n" );
    else
    {
        while(fgets(dpdainput,sizeof(dpdainput),inputfile1)!=NULL){/*read words*/
            for(i=0;i<50;i++){stackchar[i]='\0';}
            zinputcout=0;
            cout=0;
            if(dpdainput[1]!=','){/*if word is null,print is accept*/
                fprintf(outputfile,"ACCEPT\n\n\n");
                continue;
            }
            for(a=0;a<15;a++){
                character[a]='\0';
            }
            tempstring=strtok(dpdainput,",");
            i=0;
            while(tempstring!=NULL){/*find words character*/
                strcpy(characters,tempstring);
                character[i]=characters[0];
                i++;
                tempstring=strtok(NULL,",");
            }
            charnum=i;
            value = i;
            i=0;
            a=0;
            while(i<100){/*find first function*/
                if((arr[i][1]==startchar)&&(arr[i][2]==character[a])){
                    charnum--;
                    value--;
                    if(controlread(arr,character[a],arr[i][1])==-1)
                            {
                                cout++;

                            }
                    a++;
                    k=i;
                    fprintf(outputfile,"%c%c,%c,%c => %c%c,%c [STACK]:",arr[i][0],arr[i][1],arr[i][2],arr[i][3],arr[i][4],arr[i][5],arr[i][6]);/*print function*/
                    find_stack_str(outputfile); /*print stack*/
                    stackchar[zinputcout]=arr[i][3];
                    stackchar[zinputcout+1]=arr[i][6];
                    zinputcout=zinputcout+2;
                    break;
                }
                else if((arr[i][1]==startchar)&&(arr[i][2]=='e')){
                    if(control(arr,arr[i][1])==-1)
                    {
                        cout++;
                    }
                    k=i;
                    fprintf(outputfile,"%c%c,%c,%c => %c%c,%c [STACK]:",arr[i][0],arr[i][1],arr[i][2],arr[i][3],arr[i][4],arr[i][5],arr[i][6]);/*print function*/
                    find_stack_str(outputfile); /*print stack*/
                    stackchar[zinputcout]=arr[i][3];
                    stackchar[zinputcout+1]=arr[i][6];
                    zinputcout=zinputcout+2;
                    break;
                    }
                    else{i++;}
                }
            k=i;
            while(charnum>0){/*find other function, word is correct or not*/
                i=1;

                while(i<100){
                    if(arr[i][0]!='q'){
                        break;
                    }
                    if(find_value(arr,arr[k][5])==-1)
                    {
                        charnum--;
                        break;
                    }
                    if((arr[i][1]==arr[k][5])&&(arr[i][2]==character[a])){
                        if((arr[i][3]=='e')||(arr[i][3]==find_stack_last_value())){
                            charnum--;
                            value--;
                            if(controlread(arr,character[a],arr[i][1])==-1)
                            {
                                cout++;

                            }
                            a++;
                            k=i;
                            fprintf(outputfile,"\n");
                            fprintf(outputfile,"%c%c,%c,%c => %c%c,%c [STACK]:",arr[i][0],arr[i][1],arr[i][2],arr[i][3],arr[i][4],arr[i][5],arr[i][6]);/*print function*/
                            find_stack_str(outputfile);/*print stack*/
                            stackchar[zinputcout]=arr[i][3];
                            stackchar[zinputcout+1]=arr[i][6];
                            zinputcout=zinputcout+2;
                            break;
                        }
                        else{i++;}
                    }
                    else if((arr[i][1]==arr[k][5])&&(arr[i][2]=='e')){

                         if((arr[i][3]=='e')||(arr[i][3]==find_stack_last_value())){
                                if(control(arr,arr[i][1])==-1)
                                {
                                    cout++;
                                }
                                k=i;
                                fprintf(outputfile,"\n");
                                fprintf(outputfile,"%c%c,%c,%c => %c%c,%c [STACK]:",arr[i][0],arr[i][1],arr[i][2],arr[i][3],arr[i][4],arr[i][5],arr[i][6]);/*print function*/
                                find_stack_str(outputfile);/*print stack*/
                                stackchar[zinputcout]=arr[i][3];
                                stackchar[zinputcout+1]=arr[i][6];
                                zinputcout=zinputcout+2;
                                break;
                         }
                    }
                    else{i++;}
                    }
                }
                i=1;
                while(i<100)/*find last function*/
                {
                    if((arr[i][1]==arr[k][5])&&(arr[i][2]=='e')){
                            if(control(arr,arr[i][1])==-1)
                            {
                                cout++;
                            }
                            k=i;
                            fprintf(outputfile,"\n");
                            fprintf(outputfile,"%c%c,%c,%c => %c%c,%c [STACK]:",arr[i][0],arr[i][1],arr[i][2],arr[i][3],arr[i][4],arr[i][5],arr[i][6]);/*print function*/
                            find_stack_str(outputfile); /*print stack*/
                            stackchar[zinputcout]=arr[i][3];
                            stackchar[zinputcout+1]=arr[i][6];
                            zinputcout=zinputcout+2;
                            break;
                    }
                    else{i++;}
                }
                for(i=0;i<MAX_STACK_SIZE;i++){
                    stack[i].ch ='\0';
                }
                fprintf(outputfile,"\n");
                if((cout==0)&&(check_character(AInput,character)==1)&&(check_character(ZInput,stackchar)==1)&&(check_last_character(lastcharacter,arr[k][5])==1)&&(value==0)){
                    fprintf(outputfile,"ACCEPT\n\n\n");}
                else {fprintf(outputfile,"REJECT\n\n\n");}
                }/*check word is accept or not*/
    }
    fclose(inputfile);/*close dpda file*/
    fclose(inputfile1);/*close input file*/
    fclose(outputfile);/*close utut file*/
    return 0;
}


int find_value(char arr[100][7] , char c)/*if don't find character return -1 else return 1*/
{
    int i,value=0;
    for(i=0;i<100;i++){
        if(arr[i][1]==c){
            value++;
        }
    }
    if(value==0){return -1;}
    else{return 1;}
}
int control(char arr[100][7],char c)/*control function for words with don't use words character*/
{
    int i=0,k=0;
    while(i<100){
        if((arr[i][1]==c)&&(arr[i][2]=='e')){
            break;
        }
        else i++;
    }
    if(arr[i][3]=='e'){
        if(arr[i][6]!='e'){
            stack_push(arr[i][6]);}
    }
    else{
        while(k<MAX_STACK_SIZE){
            if(stack[k].ch!='\0')
            {
                k++;
            }
            else{ break; return -1;}
        }
         if(arr[i][3]==stack[k-1].ch){
            stack_pop();}
        if(arr[i][6]!='e'){
            stack_push(arr[i][6]);}
    }
    return 0;
}
int controlread (char arr[100][7],char read, char c)/*control function for words*/
{

    int i,k=0;
    while(k<MAX_STACK_SIZE){
            if(stack[k].ch!='\0')
            {
                k++;
            }
            else{ break; return -1;}
        }
    for(i=0;i<100;i++){
        if((arr[i][1]==c)&&(arr[i][2]==read)&&(arr[i][3]==stack[k-1].ch)){
            break;
        }
        else if((arr[i][1]==c)&&(arr[i][2]==read)&&(arr[i][3]=='e')){
            break;
        }
    }
    if(arr[i][3]=='e'){
        if(arr[i][6]!='e'){
        stack_push(arr[i][6]);}
    }
    else{
        if(arr[i][3]==stack[k-1].ch){
            stack_pop();}
        if(arr[i][6]!='e'){
            stack_push(arr[i][6]);}
    }
    return 0;
}

void stack_push(char c){/*to put element in stack*/
    int i;
    for(i=0;i<MAX_STACK_SIZE;i++){
        if(stack[i].ch=='\0')
        {
            stack[i].ch=c;
            break;
        }
    }
}

void stack_pop(){/*to get last element from stack*/
    int i=0;
    while(i<MAX_STACK_SIZE){
        if(stack[i].ch!='\0')
        {
           i++;
        }
        else{ break;}
    }
    stack[i-1].ch='\0';/*delete last element*/
}

char find_stack_last_value()/*find stacks last value*/
{
    int i=0;
    while(i<MAX_STACK_SIZE)
    {
        if(stack[i].ch=='\0'){
            break;
        }
        else{i++;}
    }
    if(stack[0].ch=='\0'){
        return stack[0].ch;}
    else{
        return stack[i-1].ch;}
}

int check_character(char *str, char *word)/*check words character*/
{
    int j, i;
    j=strlen(word);
    while(j>0){
        for(i=0;i<strlen(str);i++){
            if(word[j-1]=='e'){
                j--;
                break;
            }
            else if(word[j-1]==str[i]){
                j--;
            }
        }
    }
    if(j==0){
        return 1;
    }
    else return -1;
}
int check_last_character(char str[10], char c)/*check word's last character*/
{
    int i,j;
    for(i=1;i<10;i++){
       if(c==str[i]){
           j=1;
        }
    }
    if(j==1){return 1;}
    else {return -1;}
}
int find_character(char *str, char c)/*for check nput charaters are corret*/
{
    int i,j;
    for(i=0;i<strlen(str);i++){
       if(c==str[i]){
           j=1;
        }
    }
    if(j==1){return 1;}
    else {return -1;}
}

void find_stack_str(FILE *outputfile)/*for print stacks element*/
{
   int i , j=1;
    char stack_str[20];
    stack_str[0]=stack[0].ch;
    for(i=1; i< MAX_STACK_SIZE;i++)
    {
        if(stack[i].ch!='\0'){
            stack_str[j]=',';
            stack_str[j+1]=stack[i].ch;
            j=j+2;
        }
    }
   for(i=0;i<MAX_STACK_SIZE;i++){ /*degistirdigim kisim*/
        if(stack[i].ch!='\0'){ fprintf(outputfile,"%c",stack[i].ch);}
        if(stack[i+1].ch=='\0'){break;}
        fprintf(outputfile,",");
    }
}
