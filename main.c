#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100

typedef struct node* ptr;
typedef ptr stack;

struct node{char element[max];  ptr next;};// a stack node that consists of a string and a pointer to the next node
//////////////////////////////////////////////

//////////////////////////////////////////////
void redo(stack s, stack p, char temp[max]){//this function redos the last undo

     Pop(s);//get redo out of the stack
     if(IsEmpty(s) || strcmp(temp,"")==0 ){
     printf("the stack is either empty or the user didn't undo first\n");
    }

    else{

      Push(temp,s);//put the string that we undone to the stack s
      printf("result > \n");

     priint(s);//print them in order

      printf("\n");

      strcpy(temp,"");//make the string empty again
    }

}
///////////////////////////////////////////
void undo(stack s,stack p, char temp[max]){//this function undos the last string in the stack

    Pop(s);
    if(IsEmpty(s)){
    printf("Stack Empty!");
    }

    else{

    strcpy(temp,s->next->element);//first copy the string
    Pop(s);//pop the node
    printf("result > \n");

    priint(s);
    printf("\n");
    }
   }
//////////////////////////////////////////
void PrintStackreverse(stack s,stack p){
        Pop(s);
        if(IsEmpty(s)){

            printf("Stack Empty!");
        }
        else{

        while(s->next!=NULL){
        s =s->next;
        Push(s->element,p);
         }

        PrintStack(s);
         printf("\n");

        }

}

//////////////////////////////////////////
stack createstack(){//this function reserves a place for a node for stack

stack s;
s = (stack)malloc(sizeof(struct node));//reserve space in memory
if(s == NULL){
printf("Empty!");
}

s->next = NULL;
MakeEmpty(s);//invoking make empty function

return s;

}
//////////////////////////////////////////
void priint(stack s){//this function is to print the strings of stack in order

stack w =createstack();

       if(IsEmpty(s)){

            printf("Empty Stack!");
        }
        else{

        while(s->next!=NULL){
        s =s->next;
        Push(s->element,w);//we create new stack and push the elements in so they go upside down and then we print them
         }

        PrintStack(w);
         printf("\n");

        }

}




///////////////////////////////////////////
void MakeEmpty(stack s){//this function clears up the stack


if( s== NULL ){
printf("Stack Empty!");
}

else{
while(!IsEmpty(s))
Pop(s);//get every single element out
}


}
//////////////////////////////////////////
void Pop(stack s){//this function is to take the first elemnet(top) in the stack out

ptr first;

if(IsEmpty(s))
printf("Stack Empty!");

else{
first = s->next;
s->next = s->next->next;
free(first);//free the memory space reserved for this node

}

}
//////////////////////////////////////////
char *Top(stack s){// this function returns the top character

if(!IsEmpty(s))
return s->next->element;

else{
printf("No Top Element!");
return 0;
}

}
///////////////////////////////////////////
void Push(char sen[100],stack s){//this function is to push elements into the stack
    ptr temp;
    temp=(stack)malloc(sizeof(struct node));//create temp and reserve space for it
    if (temp==NULL){
        printf("Out of Space!\n");
    }
    else
    {
        strcpy(temp->element,sen);// same as temp->element = sen
        if(s->next==NULL)//if its the first elemment
        {
            s->next=temp;
            temp->next=NULL;
        }
        else//if it is not the last element
        {
            temp->next=s->next;
            s->next=temp;
        }
    }
}
///////////////////////////////////////////////////////////////////////////
int IsEmpty(stack s){//detect if the stack is empty or not

return s->next == NULL;
}
///////////////////////////////////////////////////////////////////////////
void PrintStack(stack s){//print stack

while(s-> next !=NULL){
        s = s->next;
        printf("%s\n",s->element);
   }

}
////////////////////////////////////////////////////////////////////////////
void fprintStack(FILE *in,stack s){//print stack to the file
fprintf(in,"result > \n");
while(s-> next !=NULL){
        s = s->next;
        fprintf(in,"%s\n",s->element);
   }

}
////////////////////////////////////////////////////////////////////////////
void FilePrint(stack s){// to print stack to the file in the right order
    Pop(s);
    FILE *in;
    stack w =createstack();

    if(IsEmpty(s)){
    printf("Empty Stack!");
    }

    else{

    in = fopen("output.txt","w");
    if(in == NULL){
    printf("there is an error with the file\n");
    exit(0);
     }

    else{
    while(s->next!=NULL){//here we put the elements of the stack on another  stack to reverse-store them
        s =s->next;
        Push(s->element,w);
         }

       fprintStack(in,w);//print it to file
         printf("\n");

        }

}

          fclose(in);

        }
////////////////////////////////////////////////////////////////////////////
int main()
{
stack s = createstack();
stack p = createstack();
char line[max];
char temp[max] = "";


printf("\t\t\t\t\t\t\tProject #2\n");
printf("\t\t\t\t\t   please start entering the sentences\n\n");

while(1){

    printf("My command >  ");
    gets(line);//enter the string from user
    Push(line,s);//put them into the stack
    printf("\n");

    //to read the commands we compare two strings together if it is one of the commands it does its operation
    if(strcmp(line,"print") == 0){//print to the screen
        Pop(s);
        printf("result > \n");
        priint(s);
   }

     if(strcmp(line,"redo") ==0){//redo
    stack w = createstack();
     redo(s,w,temp);
   }

     if(strcmp(line,"undo")== 0){//undo
     stack u = createstack();
     undo(s,u,temp);
   }

    if(strcmp(line,"quit") == 0){//quit
        printf("good bye");
        exit(0);
    }

    if(strcmp(line,"save")== 0){//print to file
        FilePrint(s);
    }



}



    return 0;
}
