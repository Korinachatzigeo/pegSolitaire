#include <stdio.h>
#define YES 1
#define NO 0
#define OCCUPIED 1
#define FREE 2
#define WALL 0
#define MAXST 150

typedef char boolean;
enum dir{NORTH,EAST,SOUTH,WEST};                    /* prosanatolismo algorithmou */
int dx[]={0, 1,0,-1};                               /* metakinisi peg */
int dy[]={-1,0,1, 0};
void push(char b[][10],int,int,enum dir,int,int);     /* apothikeusi stin stiva */
void pop(void);                                      /* vgazw apo stoiva */
void print_solution(void);                           /* tupwnw tin lisi */
boolean move(int,char b[][10],int,int);               /* an kounithike kapoio peg */
void print_board(char b[][10]);                       /* tupose enan pinaka */
int pegs=0;                                          /* touvlakia pou exw */

main(){
int x,y;
int steps=0;
char onoma[20], b[10][10],ar;
char bigarray[100];
int i=0,j=0,k=0,lines=0, collumns=0;
int cnt=0;

/*********************************
anoigma arxiou apo to pliktrologio
**********************************/
FILE *fp;
printf("dose to onoma tou arxeiou:");
gets(onoma);
if((fp=fopen(onoma,"r"))==NULL)
{
    puts("problima sto anoigma");
}
while(!feof(fp))
{
    fscanf(fp, "%d",&ar);
    if(i<=1){
     if (i==0) lines=ar;
     if (i==1) collumns=ar;}
     else{
     bigarray[i-2]=ar;}
     i++;
}
/*********************************************************
metatropi monodiastatou pinaka bigarray ston disdiastato b
**********************************************************/
for(i=0;i<lines;i++){
    for(j=0;j<collumns;j++){
        b[i][j]=bigarray[k];
        k++;
    }
}
/*******************************
metraei ta  touvlakia tou pinaka
********************************/
for(x=0;x<lines;x++)
for(y=0;y<collumns;y++)
if(b[y][x]==OCCUPIED)
pegs++;
printf("(%3d pegs)\n",pegs);
print_board(b);
//system("date"); /*pausi o xristis pataei enter gia na sinexisei*/
if(move(pegs,b,lines,collumns))
print_solution();
else
//printf("no solution\n");
system("date");
}

/********************************
sinartisi pou kanei tis kiniseis
to megethos tou  disdiastatou
pinaka eprepe na einai dinamiko
alla stin c den boreis na to kaneis
ama den einai global
*********************************/
boolean move(int pegs,char b[][10],int lines,int collumns){
int x,y,xn,yn,xnn,ynn;
enum dir d;

if(pegs==1){
return(YES);
}
/***********************************
ulopoisi algorithmou prwta se bathos
************************************/
for(x=0;x<lines;x++)
for(y=0;y<collumns;y++)
if(b[y][x]==OCCUPIED)
for(d=NORTH;d<=WEST;d++){
xn=x+dx[d];
yn=y+dy[d];
if(b[yn][xn]==OCCUPIED){
xnn=xn+dx[d];
ynn=yn+dy[d];
if(b[ynn][xnn]==FREE){
b[y][x]=FREE; /* do move */
b[yn][xn]=FREE;
b[ynn][xnn]=OCCUPIED;
pegs--;
/*****************************************
molis kanei mia kinisi ta vazei se lista
******************************************/
push(b,x,y,d,lines,collumns);
if(move(pegs, b,lines,collumns))
return(YES);
b[y][x]=OCCUPIED; /* undo move */
b[yn][xn]=OCCUPIED;
b[ynn][xnn]=FREE;
pegs++;
pop();
}
}
}
return(NO);
}
/*---------- stack -------------------------------------*/
int sp=0;
struct {
char board[10][10];
int vert;
int hor;
int dir;
} stack[MAXST];

char dirname[4][10];
void push(char b[][10],int xm,int ym,enum dir d,int lines,int collumns){
int x,y;
for(y=0;y<lines;y++)
for(x=0;x<collumns;x++)
stack[sp].board[y][x]=b[y][x];
stack[sp].hor=xm;
stack[sp].vert=ym;
stack[sp].dir=d;
sp++;
}
void pop(void){
sp--;
}
/*---------- print -------------------------------------*/
void print_solution(void){
int i;
strcpy(dirname[0],"up");
strcpy(dirname[1],"right");
strcpy(dirname[2],"down");
strcpy(dirname[3],"left");
for(i=0;i<sp;i++){
print_board(stack[i].board);
fflush(stdout);
printf("[moved peg at line %2d, col %2d",
stack[i].vert,stack[i].hor);fflush(stdout);
printf(" in direction %s]\n",dirname[stack[i].dir]);
fflush(stdout);
}
}
void print_board(char b[][10]){
int x,y;
printf("---------------------------------------------------\n");
for(y=0;y<10;y++){
for(x=0;x<10;x++){
if(b[y][x]==1)
printf(" #");
else if(b[y][x]==0)
printf(" O");
else
printf(" -");
}
printf("\n");
}
}
