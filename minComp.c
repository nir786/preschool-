#include <stdio.h> 
#include <string.h> 
#include <stdlib.h> 

typedef enum{

TOKEN_INT, 
TOKEN_PLUS,
TOKEN_MINUS,
TOKEN_MUL,
TOKEN_DIV, 
TOKEN_LPAREN,
TOEKN_RPAREN,
TOKEN_EOF,
TOKEN_DELETED

} TokenType; 
typedef struct{

 TokenType type; 
 int value ; 


} Token; 

typedef enum {

 AST_INT,
 AST_BINOP


}ASTnodeType;

typedef struct  ASTNode{
ASTnodeType type ; 
union 
{
 int value; 
 struct {

    struct ASTNode* left;
    TokenType op ; 
    struct ASTNode* right; 
    
 }binop; 
 

};



}ASTnode; 



int reverse_num (int num , int size)
{
    int mult = 1; 
    int newsum =  0 ; 
    
    for(int i = 0 ; i < size - 1 ; i ++ )
    {
      mult= mult*10 ; 

    }
    int arr [size]; 
    for(int i = 0 ;  i < size ; i ++ )
    {
               
       arr[i] = num/ mult ; 
       num = num %mult; 
       mult = mult/10 ;

    }
    
     mult = 1; 
   for(int i = 0; i< size ; i++ )
   {
      
     newsum += arr[i] * mult; 
     mult= mult*10 ;


   }
 
 return newsum ; 


}

Token* tokenize (const char* input, int *size)
{
  Token* tokens = malloc(sizeof(Token)* strlen(input));  
  int b = sizeof(Token) ; 
  *size = sizeof(Token)* strlen(input);
  int digetsum  =0 ;
  int digetmult = 1 ; 
  int c = 0 ;  
  int loops = 0 ; 
   for(int i = 0 ; i < strlen(input); i++ )
   {
    Token in ;
     

       int count = 0 ; 
     while(input[i] - '0' < 10 && input[i] - '0'>= 0 )
     {
       
       digetsum += (input[i] - '0' )* digetmult ; 
       
       digetmult = digetmult *10 ; 
       
       i++;
       count++ ; 
       
     }
     if(digetsum != 0 )
     {
        if(count>1)
         digetsum= reverse_num(digetsum , count) ; 
         
       in.type = TOKEN_INT ; 
       in.value = digetsum ; 
       tokens[b*c] = in;
       digetsum = 0 ; 
       digetmult = 1 ; 
       i += -1 ;
        
     }else {
      switch (input[i])
      {
      case '/':
      in.type = TOKEN_DIV ; 
      in.value = '/';
      tokens[b*c] = in;
      break;
      case '+':
      in.type = TOKEN_PLUS ; 
      in.value = '+';
      tokens[b*c] = in;
      
      break;
      case '-':
      in.type = TOKEN_MINUS ; 
      in.value = '-';
      tokens[b*c] = in;
      
      break;
      case '*':
      in.type = TOKEN_MUL ; 
      in.value = '*';
      tokens[b*c] = in;
       
      break;
         
     }
     
    }

   c++; 

   }




return tokens ;  
  }

ASTnode* create_tree (Token* tokens , int size )
{

struct ASTNode* leaf = malloc(sizeof(struct ASTNode)) ; 
struct ASTNode* single = malloc(sizeof(struct ASTNode)); 

  int i = 0 ; 
  int b = 0 ; 
  while(b < size )
  {
   if( b < size&& tokens[i].type == TOKEN_INT && tokens[i].value != 127
     && tokens[i+sizeof(Token)].type != TOKEN_DIV
     && tokens[i+sizeof(Token)].type != TOKEN_MUL
     &&tokens[i -sizeof(Token)].type != TOKEN_MUL 
     &&tokens[i -sizeof(Token)].type != TOKEN_DIV )
     {
        single->value = tokens[i].value;
        leaf->binop.right = single ;
        leaf->binop.op = tokens[i+sizeof(Token)].type ;
        tokens[i].value = 127;
        //tokens[i+sizeof(Token)].value = 127; 
        tokens[i].type = TOKEN_DELETED;
        tokens[i+ sizeof(Token)].type = TOKEN_DELETED;
        leaf->binop.left = create_tree(tokens , size ); 
        return leaf ; 

     } else 
     {
      if(i !=0 &&tokens[i].type == TOKEN_INT &&tokens[i].value != 127
        && tokens[i-sizeof(Token)].type != TOKEN_DIV
        && tokens[i-sizeof(Token)].type != TOKEN_MUL
        && tokens[i+sizeof(Token)].type != TOKEN_DIV
        && tokens[i+sizeof(Token)].type != TOKEN_MUL  )
       {
        
        single->value = tokens[i].value;
        
        leaf->binop.right = single;
        leaf->binop.op = tokens[i-sizeof(Token)].type ;
        tokens[i].value = 127;
        tokens[i - sizeof(Token)].value = 127; 
        leaf->binop.left = create_tree(tokens , size) ; 
        return leaf ; 
       }
        
     } 
      i+= sizeof(Token) ;
      b++ ;  
  }
  
     return leaf ; 


}

ASTnode* mult_tree (Token * tokens , int size)
{

  struct ASTNode* leaf = malloc(sizeof( struct ASTNode));
          int i = 0 ; 
          int b= 0 ;
          struct ASTNode* single = malloc(sizeof(struct ASTNode)); 
          while(b < size )
          {
        if(b + 2 < size &&tokens[i].type == TOKEN_INT 
          &&tokens[i+(2*sizeof(Token))].type == TOKEN_INT  )
          {
            
            struct ASTNode* single = malloc(sizeof(struct ASTNode)); 
            struct ASTNode* singlet = malloc(sizeof(struct ASTNode)); 
              if(tokens[i-sizeof(Token)].type == TOKEN_MINUS )
              tokens[i].value = -tokens[i].value; 
              struct ASTNode* duble  = malloc(sizeof( struct ASTNode));
                   single->value =  tokens[i].value;
                    
              duble->binop.left = single ; 
                   singlet->value =  tokens[i+2*sizeof(Token)].value ;
              duble->binop.right = singlet ; 
              duble->binop.op = tokens[i+sizeof(Token)].type ;  
              leaf->binop.right = duble; 
              if(tokens[i+3*sizeof(Token)].value == 42 
              || tokens[i+3*sizeof(Token)].value == 47)
              {
                if(tokens[i+3*sizeof(Token)].value == 47)
                leaf->binop.op = tokens[i+3*sizeof(Token)].type = TOKEN_DIV ;
                else 
                leaf->binop.op = tokens[i+3*sizeof(Token)].type = TOKEN_MUL;
              }else 
              {

              leaf->binop.op = TOKEN_PLUS ; 
              }
              tokens[i].type = TOKEN_DELETED ; 
              tokens[i+sizeof(Token)].type = TOKEN_DELETED ;
              tokens[i+2*sizeof(Token)].type = TOKEN_DELETED ;
              leaf->binop.left = mult_tree(tokens , size) ;
              return leaf; 

          }else 
          {
            if( b - 1 > 0 &&tokens[i].type  == TOKEN_INT 
            &&(tokens[i-sizeof(Token)].type == TOKEN_MUL 
            || tokens[i-sizeof(Token)].type == TOKEN_DIV) )
            {
              
              struct ASTNode* single = malloc(sizeof(struct ASTNode)); 
            struct ASTNode* singlet = malloc(sizeof(struct ASTNode)); 
              struct ASTNode* duble  = malloc(sizeof( struct ASTNode));
              single->value = tokens[i].value ; 
              duble->binop.left = single ;
              singlet->value = 1; 
              duble->binop.right = singlet ; 
              duble->binop.op = TOKEN_MUL ; 
               leaf->binop.right  = duble ; 
               leaf->binop.op = tokens[i-sizeof(Token)].type ; 
               tokens[i].type = TOKEN_DELETED ; 
               tokens[i-sizeof(Token)].type = TOKEN_DELETED ; 
                 
              leaf->binop.left = mult_tree(tokens , size) ;
              return leaf;
            }


          }
          b++ ; 
          i += sizeof(Token) ; 
        }
        
     return leaf; 





}


void print_mult_tree (struct ASTNode* first   )
{

  
  struct ASTNode* move_right = malloc(sizeof(struct ASTNode));
   if(first->binop.left !=0 && first->binop.right != 0 )
   {
  int opr_one = first->binop.op;
    move_right = first->binop.right ; 
  printf("%d\n", opr_one);
  int opr_two = move_right->binop.op; 
  int value_left = move_right->binop.left->value; 
  int value_right = move_right->binop.right->value;  
  printf("node_right (%d , op:%d , %d )\n" ,value_left ,opr_two , value_right );
   }
   else 
   printf("end of the line buddy") ; 

}

void print_sec_tree(struct ASTNode* first)
{

  struct ASTNode* sec = malloc(sizeof(struct ASTNode*));
  if(first->binop.left ->binop.right->value!= 0 && first->binop.left ->binop.left->binop.right->value !=  0   )
  {
  sec = first->binop.left ;
  int first_right_value = first->binop.right->value ;  
  int sec_right_value = sec->binop.right->value; 
  int op = first->binop.op  ; 
  int sec_op = sec->binop.op ;
  
  printf("(%d , op : %d , %d ) \n" , first_right_value , op , sec_right_value ); 
  }
  else
  {
printf("end of the line bud"); 

  }

}

void ass_gen_mult(struct ASTNode* pointer )
{
   

 

 int a = pointer->binop.left->value; 
 int b = pointer->binop.right->value; 
printf("mov rax, %d\n" , a); 
printf("push rax\n");

printf("mov rbx, %d\n" , b); 
printf("push rbx\n");

printf("pop rax\n");
printf("pop rbx\n");


 if(pointer->binop.op == TOKEN_DIV )
 {   
  if(a > 0 || b > 0) 
   {
     printf("cqo\n");
     printf("idiv rbx\n");
   } else 
   {
     printf("xor rdx, rdx\n"); 
     printf("div rbx\n");

   }

 }else 
 {   
     printf("imul rax, rbx\n") ;
 }
 
  
 

}

void ass_gen_mult_tree(struct ASTNode * first)
{

  struct ASTNode* point = malloc(sizeof(struct ASTNode)); 
   
  point = first->binop.left; 
  while(point->binop.left->value != 0 && point->binop.left->value != 0 )
  {
     ass_gen_mult(point) ; 


  }
  
  

  printf("mov rcx,rax\n");
  printf("push rcx"); 

    printf("pop rcx\n");
    printf("add rcx, rax\n") ; 
    printf("push rcx\n ");



}

int realloc_tokens(Token* tokens , int string_length )
{
   
int size = 0  ; 
int i = 0 ;
while(tokens[i].value != 0 && tokens[i+sizeof(Token)].value!= 0&& i<string_length )
{
 

i+= sizeof(Token) ; 

size++ ; 

}
 tokens = realloc(tokens,size+1) ; 


return size+1 ; 
}
int main ( )
{
  int  size;                 //11
  Token*  tokens = tokenize("1+2*3456",&size) ; 
  size = realloc_tokens(tokens ,size ) ; 
  
  struct ASTNode* branch = malloc(sizeof(struct ASTNode));
  branch = create_tree(tokens , size);

  
 struct ASTNode* multtree = malloc(sizeof(struct ASTNode));
 multtree = mult_tree(tokens,size);
 
 
ass_gen_mult(multtree, 0);

 
 
 

 

 



  



 free(tokens); 
 
 return 0 ; 

}