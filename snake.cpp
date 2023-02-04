#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<fstream>
using namespace std;

const int width = 40;
const int hight = 20;
int foodx, foody;
int headx;
int heady;
int score = 0;
int highscore = 0;
int tailx[200] = {0};
int taily[200] = {0};
int tail = 0;
enum direction{ LEFT, RIGHT, UP, DOWN } dir;
bool gameover;

void start()
{
  srand(time(NULL));
  gameover = false;
  headx = width / 2;
  heady = hight / 2;
  foodx = rand() % width;
  foody = rand() % hight;
}

void paint()
{
  system("cls");
//gora
  for (int i = 0; i < width + 2; i++)
  cout << "#";
  cout << endl;
//boki
  for (int i = 0; i < hight; i++)
  {
    for (int j = 0; j < width; j++)
    {
//lewo
      if (j == 0)
      {
        cout << "#";
      }
//glowa
     if (i == heady && j == headx)
     cout << "O";
//fruit
     else if (i == foody && j == foodx)
     cout << "*";

    else
    {
    bool print = false;

    for (int k = 0; k < tail; k++)
    {
      if (tailx[k] == j && taily[k] == i)
      {
        cout << "0";
        print = true;
     }
    }

     if (!print) 
     {
      cout << " ";
     }
   }
//prawo
    if (j == width - 1)
    {
      cout << "#";
    }
 }
 cout << endl;
}
//podloga
for (int i = 0; i < width + 2; i++)
{
  cout << "#";
}
 cout << endl;
 cout << "SCORE: " << score << endl;
}

void direct()
{
  if (_kbhit())
  {
   switch (_getch())
   {
    case 'a':
    dir = LEFT;
    break;
    case 's':
    dir = DOWN;
    break;
    case 'w':
    dir = UP;
    break;
    case 'd':
    dir = RIGHT;
    break;
   }
  }
}


void move() {
  int previousx = tailx[0];
  int previousy = taily[0];
  tailx[0] = headx;
  taily[0] = heady;
  for (int i = 1; i < tail; i++) {
    int prev2x = tailx[i];
    int prev2y = taily[i];
    tailx[i] = previousx;
    taily[i] = previousy;
    previousx = prev2x;
    previousy = prev2y;
  }
//moving
 switch (dir)
 {
  case LEFT:
  headx--;
  break;
  case RIGHT:
  headx++;
  break;
  case UP:
  heady--;
  break;
  case DOWN:
  heady++;
  break;
  default:
  break;
 }
//collision
 if (headx>width - 1 || headx<0 || heady > hight - 1 || heady<0)
 gameover = true;

 for (int i = 0; i < tail; i++)
 {
   if (tailx[i] == headx && taily[i] == heady)
      gameover = true;
 }
//new fruit
 if (headx == foodx && heady == foody)
 {
  srand(time(NULL));
  foodx = rand() % width;
  foody = rand() % hight;
  tail++;
  score += 10;
 }
}
void loadHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highscore;
        file.close();
    }
}
void saveHighScore() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highscore;
        file.close();
    }
}

int main()
{
  start();

 while (!gameover)
 {
  paint();
  direct();
  move();
  Sleep(100);
 }

 system("cls");
  loadHighScore();
  if (score>highscore){
    highscore=score;
    saveHighScore();
  }
  cout << "SCORE: " << score << " HIGHSCORE: " << highscore <<endl;
}