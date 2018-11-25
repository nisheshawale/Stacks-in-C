#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<string.h>
void start();
void instruction();
void highscore(int);
void scoreboard();
int game();	
void current(int);
int movev(int,int,int ,int, int,int);
int moveh(int, int, int, int, int,int);
int x[100] , y[100], d[100], l[100],count[100],bonus;
typedef struct //structure declaration for detail of player
{
   char name[20];
   int score;
}score_record;
score_record record1[5],record2[6], record3[5];

void main() //Main function
{
  int  gd=DETECT , gm,score;
  initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
  start();
}


void start()  //Function for home page
{
char c[1],choice;
int x,score;
x=getmaxx();
cleardevice();
fflush(stdin);
setcolor(YELLOW);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
outtextxy(x/2-50,10,"STACKS");
settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
outtextxy(x-500,100,"A.INSTRUCTIONS");
outtextxy(x-500,130,"B.PLAY");
outtextxy(x-500,160,"C.SCOREBOARD");
outtextxy(x-500,190,"D.Quit");
outtextxy(x-500,240,"ENTER YOUR CHOICE:");
choice=toupper(getche());   //gets the choice of user
switch(choice)
{
case 'B':
score=game();
highscore(score);
break;
case 'A':
instruction();
break;
case 'C':
scoreboard();
break;
case 'D':
exit();
break;
default:
exit();
 }
}

void instruction() //function to display instructions
{
int i,j=80,a=0;
char c[5], ins[]="The name of the game is STACKS. You have to place one block over another and build the stack of block. The block moves above next block and you have to place block by press of SPACE KEY. In case block is not placed exactly above next block then the size of  block decreases.";
cleardevice();
setcolor(YELLOW);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
outtextxy(250,30,"HOW TO PLAY");
for(i=0; ins[i]!='\0'; i++)
{
if(a*15>=getmaxx())  //checks whether coordinate exceeded the screen limit
  {
  a=0;
  j=j+30;
  }
  c[0]=ins[i];
  c[1]='\0';
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
  outtextxy(a*15+1,j,c);
  a++;
  if(kbhit())
  delay(0);
  else
  delay(100);
}
getch();
outtextxy(30,350,"Press enter to go to main menu");
getch();
start(); //goes to home page
}

int game()   //function for execution of game
{
   char ch[3];
  int p,q,i;
  x[0]=200, y[0]=200, l[0]=100,d[0]=50;
  bonus=0;
  for(p=0;p<=50;p=p+2)
  {
  q=p+bonus;
  count[p]=movev(x[p],y[p],l[p],d[p],q,bonus);   //function for vertcal movement of block
  if(count[p]>=x[p]+d[p] || count[p]<=x[p]-d[p]) //checks whether the next block is placed over the block or not
  break;   //terminates the game
  l[p+1]=l[p];         //calculation of coordinates for new block
  if(count[p]>=x[p])
  {
  x[p+1]=count[p];
  y[p+1]=y[p]-(0.75*(count[p]-x[p]));
  for(i=0;i<=p;i++)
  y[i]=y[i]+10;
  d[p+1]=d[p]-(count[p]-x[p]);
  }
  else
  {
  x[p+1]=x[p];
  y[p+1]=y[p];
  for(i=0;i<=p;i++)
  y[i]=y[i]+10;
  d[p+1]=d[p]-(x[p]-count[p]);
  }
  q=p+1+bonus;
  count[p+1]=moveh(x[p+1],y[p+1],l[p+1],d[p+1],q,bonus); //function for horizontal movement of block
  if(count[p+1]>=x[p+1]+l[p+1] || count[p+1]<=x[p+1]-l[p+1])//checks whether block is placed over the next block or not
  break;//terminates program
  if(count[p+1]>=x[p+1])    //coordinates of new block calculation
  {
  x[p+2]=count[p+1];
  y[p+2]=y[p+1];
  for(i=0;i<=p+1;i++)
  y[i]=y[i]+10;
  l[p+2]=l[p+1]-(count[p+1]-x[p+1]);
  d[p+2]=d[p+1];
  }
  else
  {
  x[p+2]=x[p+1];
  y[p+2]=y[p+1];
  for(i=0;i<=p+1;i++)
  y[i]=y[i]+10;
  l[p+2]=l[p+1]-(x[p+1]-count[p+1]);
  d[p+2]=d[p+1];
  }
  }
  cleardevice();
  current(q);
  settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
  outtextxy(250,30,"GAME OVER");
  outtextxy(250,60,"SCORE:");
  sprintf(ch,"%d",q);
  outtextxy(300,60,ch);
  getch();
  return q;//return score achieved
}

void current(int m)//function for drawing placed blocks
{
int i,n;
n=m-bonus;
for (i=0; i<=n;i++)
{
setfillstyle(SOLID_FILL,YELLOW);
bar3d(x[i],y[i]+10,x[i]+l[i],y[i]+20,d[i],1);
}
}

int moveh(int a, int b, int c, int d, int z,int e) //function for horizontal
				       //movement
{
char control, ch[3];
int i, x, y,f;
f=5+e;
while(!kbhit())  //continues until key is pressed
{
  for (i=-75; i<=75;i=i+f) //loop for right movement
   {
   x=a+(1.25*i);
   y=b;

   cleardevice();
   sprintf(ch,"%d",z);
	setcolor(RED);     //displays current score
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(DEFAULT_FONT, HORIZ_DIR,4);
	outtextxy(600,30,ch);

   current(z);     //function which displays previous blocks
   setfillstyle(SOLID_FILL,RED);
   bar3d(x,y,x+c,y+10,d,1);  //moving block
   delay(50);

   if(kbhit())
    {
    control=getch();
    switch(control)
     {
	case' ' :
	if(a==x)
	bonus=bonus+2;
       goto end;  //if space is pressed goes to end of function terminating loop
     }
    }
  }

  for(i=75; i>=-75;i=i-f)
   {
    x=a+(1.25*i);
    y=b;
    cleardevice();
   sprintf(ch,"%d",z);
	setcolor(RED);   //displays current score
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(DEFAULT_FONT, HORIZ_DIR,4);
	outtextxy(600,30,ch);
    current(z);  //displays previous blocks
    setfillstyle(SOLID_FILL,RED);
    bar3d(x,y,x+c,y+10,d,1);    //moving block
    delay(50);

   if(kbhit())
    {
    control=getch();
    switch(control)
     {
	case' ' :
       if(a==x)
	bonus=bonus+2;
	goto end;   //if space is pressed terminates loop and goto end of 
				  // function
     }
    }
  }
}
end://end of function
sound(1500);
delay(50);
nosound();
return x; //returns the x coordinate of block when space is pressed
}

int movev(int a, int b, int c, int d, int z,int e) //funcion for vertical movement
				    // of block
{
char control, ch[3];
int i, x, y,f;
f=5+e;
while(!kbhit()) //continues until key is pressed
{
  for (i=-50; i<=50;i=i+f) //loop for upward movement
   {
   x=a+i;
   y=b-(0.75*i);
   cleardevice();
   sprintf(ch,"%d",z);
	setcolor(RED);       //displays current score
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(DEFAULT_FONT, HORIZ_DIR,4);
	outtextxy(600,30,ch);

   current(z);      //displays previous blocks
   setfillstyle(SOLID_FILL,RED);
   bar3d(x,y,x+c,y+10,d,1);       //moving block
   delay(50);

   if(kbhit())
    {
    control=getch();
    switch(control)
     {
	case' ' :
	if(a==x)
	bonus=bonus+2;
	goto end;   //if space is pressed goes to end of function and 
				// terminates loop
     }
    }
  }

  for(i=50; i>=-50;i=i-f)  //loop for downward movement
   {
    x=a+i;
    y=b-(0.75*i);
    cleardevice();
    sprintf(ch,"%d",z);
	setcolor(RED);  //displays score
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	settextstyle(DEFAULT_FONT, HORIZ_DIR,4);
	outtextxy(600,30,ch);

    current(z);      //displays previous blocks
    setfillstyle(SOLID_FILL,RED);
    bar3d(x,y,x+c,y+10,d,1);   //moving block
    delay(50);

   if(kbhit())
    {
    control=getch();
    switch(control)
     {
	case' ' :
	if(a==x)
	bonus=bonus+2;
 goto end;  //if space is pressed terminates loop and goes to end of function
     }
    }
  }
}
end: //end of function
sound(1500);
delay(50);
nosound();
return x; //returns x coordinate of block when space key is pressed
}


void highscore(int score)  //Function to store highscores
{
 FILE *fptr;
 int i,j,k,temp;
 char temp1[20];
 cleardevice();
 fptr=fopen("score","rb");   //file named score opened in read mode
 for(i=0;i<5;i++)
 {
 fread(&record1[i],sizeof(record1),1,fptr); //data stored in file is stored in 
			       //	structure record[]
 }
 fclose(fptr);  //closes file
 for(i=0;i<5;i++)
 {
 if(score>record1[i].score) //checks whether score is top 5 highscore or not
 {
 printf("\n Enter the record of player :\n");
 printf("Name:");
 scanf("%s",&record1[5].name);
 record1[5].score=score;  //gets information of player and stores in record[5]
   for(k=0;k<5;k++)         //bubble sorts the record stored
    {
      for(j=0;j<5-k;j++)
      {
       if(record1[j+1].score>record1[j].score)
       {
       temp=record1[j].score;
       strcpy(temp1,record1[j].name);
       record1[j].score=record1[j+1].score;
       strcpy(record1[j].name,record1[j+1].name);
       record1[j+1].score=temp;
       strcpy(record1[j+1].name,temp1);
       }
      }
     }
  break;
 }
 }
 fptr=fopen("score","wb"); //file opened in write mode
 for(i=0;i<5;i++)
 {
  fwrite(&record1[i],sizeof(record1),1,fptr); //data of structure record[] is 
									   // written on the file
 }
fclose(fptr);//closes file
start();
}

void scoreboard()
{
char temp1[20],c[100];
int i,j,temp,k;
FILE *fptr;
cleardevice();
fptr=fopen("score","rb"); //opens file score in read mode
setcolor(YELLOW);
settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
outtextxy(250,30," SCORE BOARD");
outtextxy(200,70,"RANK  NAME   SCORE");
for(i=0;i<5;i++)
{
fread(&record3[i], sizeof(record3),1,fptr);//data written in file is stored in
			       //	structure record3[]
sprintf(c,"%d     %-10s %-2d",i+1, record3[i].name, record3[i].score); //displays the structure record3[]
outtextxy(200,100+(i*30),c);
}
fclose(fptr);
outtextxy(200,350,"Press any key to go to main menu");
getch();
start();
}


