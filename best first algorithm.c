#include <stdio.h>
#define SOLSPIC 10000
#define BASE 1000000
#define MOVESPIC 10
#define YES 1
#define NO 0
#define N 9
#define OCCUPIED 1
#define FREE 2
#define WALL 0
#define MAXST 35
#define MAXBR 50

typedef char boolean;
enum dir{UP,RIGHT,DOWN,LEFT};
int dx[]={0, 1,0,-1};
int dy[]={-1,0,1, 0};
long int movesA=0; /* total number of moves - MSD */
long int movesB=0; /* total number of moves - LSD */
long int fmoves=0; /* moves until first solution */
float fbranch; /* branching at first solution */
long int sols=0; /* solutions */
long int nnodes=0; /* number of nonterminal nodes */
int ipegs, pegs;
long br[MAXST][MAXBR]; /* no. branches by level */

void push(int,int,enum dir);
void pop(void);
void print_solution(void);
void move(int, char b[][10],int,int);
void all_print(void);
void first_print(void);

main(){
int x,y;
int steps=0;
pegs=0;
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
for(x=0;x<lines;x++) /* count pegs */
for(y=0;y<collumns;y++)
if(b[y][x]==OCCUPIED)
pegs++;
ipegs=pegs;
printf("(%3d pegs)\n",ipegs);
for(x=0;x<MAXST;x++) /* initialize no. of branches */
for(y=0;y<MAXBR;y++)
br[x][y]=0;
system("date");
move(pegs,b,lines,collumns);
system("date");
//all_print();
}
void move(int pegs,char b[][10],int lines,int collumns){
int x,y,xn,yn,xnn,ynn;
enum dir d;
boolean count;
long branches; /* branches at this node */
/*----------------------- test selection ----------------------*/
/* TEST1: solution = one peg */
if(pegs==1){
br[ipegs-pegs][0]+=1;
sols++;
if(fmoves==0){
fmoves=movesB;
fbranch=(float)fmoves/(float)nnodes;
first_print();
exit(1);
}
/*if(sols%SOLSPIC==0)
printf(" (%8d solutions)\n",sols);*/

}

/*--------------- end of test selection ----------------------*/
count=YES;
branches=0; /* branches for this board */
for(x=0;x<lines;x++)
for(y=0;y<collumns;y++){
if(b[y][x]==OCCUPIED)
for(d=UP;d<=LEFT;d++){
xn=x+dx[d];
yn=y+dy[d];
if(b[yn][xn]==OCCUPIED){
xnn=xn+dx[d];
ynn=yn+dy[d];
if(b[ynn][xnn]==FREE){
branches++;
b[y][x]=FREE; /* do move */
b[yn][xn]=FREE;
b[ynn][xnn]=OCCUPIED;
pegs--;
movesB++;
if(movesB==BASE){
movesB=0;
movesA++;
}
if(count)
nnodes++;
count=NO;
/*if(movesA%MOVESPIC==0 && movesB==0)
printf("(moves: %8d (x BASE), %1.4f branching)\n",
movesA,
(float)(BASE*movesA+movesB)/(float)nnodes);*/
move(pegs,b,lines,collumns);
b[y][x]=OCCUPIED; /* undo move */
b[yn][xn]=OCCUPIED;
b[ynn][xnn]=FREE;
pegs++;
}
}
}
}
br[ipegs-pegs][branches]+=1;
return;
}
/*-----------------------------------------------------------------*/
void line(void);
void all_print(void){
printf("\n");
line();
printf("\nCOMPLETE SEARCH");
printf("\nTotal number of moves = %d,%d",
movesA,movesB);
printf("\nTotal number of solutions = %8d",sols);
printf("\nNon terminal nodes = %8d",nnodes);
printf("\nTerminal nodes = %8d",(movesB+1)-nnodes);
printf("\nAverage branching = %8.4f\n",
(float)movesB/(float)nnodes);
line();
printf("\n");
}
void first_print(void){
printf("\n");
line();
printf("\nSEARCH UNTIL FIRST SOLUTION");
printf("\nMoves until first solution = %8d",fmoves);
printf("\nAverage branching at first solution = %8.4f\n",
fbranch);
line();
printf("\n");
}

void line(void){
printf("----------------------------------------------");
}
