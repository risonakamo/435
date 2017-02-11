#include <iostream>
#include <fstream>

#define WIDTH 512
#define HEIGHT 512

using namespace std;

void test1();
void test2();

int main()
{
  test2();
  return 0;
}

void test2()
{
  FILE* f=fopen("s.ppm","wb");
  fprintf(f, "P6\n%d %d\n%d\n", WIDTH, HEIGHT, 255);

  for (int x=0;x<512;x++)
    {
      for (int y=0;y<512;y++)
        {
          fprintf(f,"252 18 205 ");
        }
    }
}

void test1()
{
  unsigned char pixels[HEIGHT][WIDTH][3];

  for (int x=0;x<512;x++)
    {
      for (int y=0;y<512;y++)
        {
          pixels[y][x][0]=252;
          pixels[y][x][1]=18;
          pixels[y][x][2]=205;
        }
    }

  FILE *f = fopen("hide.ppm","wb");
  fprintf(f, "P6\n%d %d\n%d\n", WIDTH, HEIGHT, 255);
  fwrite(pixels, 1, HEIGHT*WIDTH*3, f);
  fclose(f);
}
