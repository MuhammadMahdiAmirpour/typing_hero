#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include "helper_windows.h"
#include <time.h>
int x = 0, i, j, wave10 = 0, n4 = 0, hazf = 0, wave = 1, level, dorepayani = 0, red = 0, mark=0,ft=0;
double period ;
char word[20][255];
int word_type[20];
int Word_locked = 0;
void delay(int milliseconds);
void print();
int shift(int n);
void time_set();
void selector();
void builder(int k);
void score(int k);
void tab(int k, int m, int sign);
void eftekhri();
// file usa.c dar masir zir zahkire shvad.
// ****** C:\\usa.txt **********
COORD coord = {0, 0};
void gotoxy(int x, int y) 
{
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void frame() 
{
  for (int y = 0; y < 19; y = y + 1)
  {
    gotoxy(0, y);
    printf("#                    #");
  }
  printf("\n######################");
  
  gotoxy(23, 1);
  printf("score=%d", mark);
}
void my_callback_on_key_arrival(char c)
{
  if (word[shift(0)][x] == c)
  {
    x++;
    if (3 == x&&ft==1){
      x = 0;
      score(word_type[shift(0)]);
      i--;
      Word_locked++;
      Word_locked = Word_locked % 20;
      hazf++;
      time_set();
      builder(shift(19));
    }
      if (strlen(word[shift(0)]) == x)
      {
        if (word_type[shift(0)] == 3 && strlen(word[shift(0)]) > 10 && ft < 1 && i >= 16)
          ft=1;
        x = 0;
      score(word_type[shift(0)]);
      i--;
      Word_locked++;
      Word_locked = Word_locked%20;
          hazf++;
      time_set();
      builder(shift(19));

      
    }
    if (i < 19 && dorepayani<2)
      print();
  }

  
}

int main()
{
  printf("Specify the level of the game from one to three:\n");
  scanf("%d", &level);
  switch (level)
  {
  case 1:
    period=10;
     break;
  case 2:
    period=8;
     break;
  case 3:
    period=5;
  }

  
  HANDLE thread_id = start_listening(my_callback_on_key_arrival);
  

  system("cls");
  selector();
  for (int k = 0; k < 20; k++)
  {
    builder(k);
  }
 
      
      for (i = 0; i < 19; i++)
  {
    if (n4 > 0)
    {
      delay(period *n4*3000);
      n4=0;
    }
    if (dorepayani==2){
      system("cls");
      printf("You have reached a good level of skill and speed.\nscore=%d", mark);
      delay(5000);
      return 0;
     
    }
      wave10++;
    print();
    if (n4 > 0&&ft==1)
    {
      delay(period * 2000);
      ft=2;
      n4 = 0;
    }
    delay(period * 1000);
    if(n4>0){
      delay(period * n4 * 3000);
      n4 = 0;
    }
  }
  system("cls");
  printf("Gameover\nwave=%d\nscore=%d\nlevel=%d",wave,mark,level);
  delay(5000);
  return 0;
      // bakhti
      WaitForSingleObject(thread_id, INFINITE);
  return 0;
}

void delay(int milliseconds)
{
  long pause;
  clock_t now, then;

  pause = milliseconds * (CLOCKS_PER_SEC / 1000);
  now = then = clock();
  while ((now - then) < pause)
    now = clock();
}
void print()
{
  if(red==0)
  {red=1;
    frame();
    if (ft == 1)
    {
      eftekhri();
    }
    else 
  {for (j = 1; j < i+1; j++)
  {
    if (word_type[shift(j)] >= 5){ 
    gotoxy(1, i - j);
    printf("********************");
    }
    else{
    gotoxy((20 - (int)strlen(word[shift(j)])) / 2 + 1, i - j);
    printf("%s", word[shift(j)]);
    }
  }
  if(i>=0)
  {
    gotoxy((20 - (int)strlen(word[shift(0)])) / 2 + 1, i);
    for (int k = 0; k < x; k++)
      printf("\x1b[31m"
             "%c"
             "\x1b[0m",
             word[shift(0)][k]);
    for (int k = x; k < strlen(word[shift(0)]); k++)
      printf("%c", word[shift(0)][k]);}
  }
      red=0;
     
      }
}
int shift(int n)
{
  if (Word_locked + n - 20 >= 0)
    return (Word_locked + n - 20);
  else
    return (Word_locked + n);
}
void time_set()
{
  if (hazf / 10 + 1 != wave)
  {
    wave = hazf / 10 + 1;
    switch (level)
    {
    case 1:
      period = period * 0.8;
      break;
    case 2:
      period = period * 0.7;
      break;
    case 3:
      period = period * 0.6;
    }
    if (period<=1){
      period=1;
      dorepayani++;
     
    }
  }
}
int mobham[6];
void selector(){
  for (int k = 0; k < 20; k++){
    word_type[k] = rand() % 4+1;
  }

    for (int k = 0; k < 6; k++)
    {
      mobham[k] = rand() % 20;
      word_type[mobham[k]] =rand()%3+5;
    }

}
void builder(int k){
  FILE *fp;
  char buff[255];
  fp = fopen("C:\\usa.txt", "r");
  fseek(fp, rand(), SEEK_SET);
  switch (word_type[k])
  {
  case 1:
    do {
      fscanf(fp, "%s", buff);
      fscanf(fp, "%s", buff);
      strcpy(word[k], buff);
    } while(strlen(buff) > 10 || strlen(buff) <= 4);
     break;
  case 2:
    do{
      fscanf(fp, "%s", buff);
      fscanf(fp, "%s", buff);
      strcpy(word[k], buff);
    }while (strlen(buff) > 20 || strlen(buff) <= 10);
     break;
  case 3:
    fscanf(fp, "%s", buff);
    fscanf(fp, "%s", buff);
    strcpy(word[k], buff);
    do
    {
      
      switch(rand()%6){
        case 0:
          tab(k, rand() % strlen(word[k]), '!');
          break;
        case 1:
          tab(k, rand() % strlen(word[k]), '&');
          break;
        case 2:
          tab(k, rand() % strlen(word[k]), '^');
          break;
        case 3:
          tab(k, rand() % strlen(word[k]), '%');
          break;
        case 4:
          tab(k, rand() % strlen(word[k]), '$');
          break;
        case 5:
          tab(k, rand() % strlen(word[k]), '@');
          break;
      }
        

    } while (rand() % 10 > 6&&strlen(word[k])<19);
    break;
  case 4:
    fscanf(fp, "%s", buff);
    fscanf(fp, "%s", buff);
    strcpy(word[k], buff);
    do{
    
    tab(k, rand() % strlen(word[k]),'#');

  } while (rand() % 10 > 6 && strlen(word[k]) < 19);
     break;
   case 5:
     do
     {
       fscanf(fp, "%s", buff);
       fscanf(fp, "%s", buff);
       strcpy(word[k], buff);
     } while (strlen(buff) > 10 || strlen(buff) <= 4);
     break;
   case 6:
     do
     {
       fscanf(fp, "%s", buff);
       fscanf(fp, "%s", buff);
       strcpy(word[k], buff);
     } while (strlen(buff) > 20 || strlen(buff) <= 10);
     break;
   case 7:
    word_type[k]=3;
    builder(k);
    word_type[k] = 7;
     break;
  }
}
void score(int k){
   switch (k)
  {
  case 1:
    mark++;
    break;
  case 2:
    mark+=2;
    break;
 case 3:
    mark+=3;
    break;
   case 4:
     n4++;
     break;
   case 5:
     mark += 2;
     break;
   case 6:
     mark += 3;
     break;
   case 7:
     mark += 4;
     break;
  }
}
void tab(int k, int m, int sign)
{
  char temp[255];
  strcpy(temp,word[k]);
  word[k][m] = sign;
  for(int l=m+1;l<strlen(temp)+2;l++){
    word[k][l]=temp[l-1];
  }
}
void eftekhri(){
    frame();
    n4=1;
    for (j = 1; j < i + 1; j++)
    {
         gotoxy(9, i - j);
         for (int k = 0; k < 3; k++)
         printf("%c", word[shift(j)][k]);
       
    }
    if (i >= 0)
    {
      gotoxy(9, i);
      for (int k = 0; k < x; k++)
        printf("\x1b[31m" "%c""\x1b[0m",word[shift(0)][k]);
      for (int k = x; k < 3; k++)
        printf("%c", word[shift(0)][k]);
    }
  }
