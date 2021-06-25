#include<stdio.h>

typedef struct {
    char id_len;
    char map_type;
    char img_type;
    int  map_first;
    int  map_len;
    char map_entry_size;
    int  x;
    int  y;
    int  width;
    int  height;
    char bpp;
    char desc;
} HEADER;

void create_header(HEADER h, FILE *tga)
{
    fputc(h.map_type, tga);
    fputc(h.id_len, tga);
    fputc(h.img_type, tga);
    fputc(h.map_first % 256, tga);
    fputc(h.map_first / 256, tga);
    fputc(h.map_len % 256, tga);
    fputc(h.map_len / 256, tga);
    fputc(h.map_entry_size, tga);
    fputc(h.x % 256, tga);
    fputc(h.x / 256, tga);
    fputc(h.y % 256, tga);
    fputc(h.y / 256, tga);
    fputc(h.width % 256, tga);
    fputc(h.width / 256, tga);
    fputc(h.height % 256, tga);
    fputc(h.height / 256, tga);
    fputc(h.bpp, tga);
    fputc(h.desc, tga);
}

void color(int r, int g, int b, FILE *tga);

void draw(int x, FILE *tga)
{
    int y;
    int i = x;
    for(i = 0; i < x; i++)
      for(y = 0; y < 640; y++)
      {
        if(y % 2 == 0)
        {
          color(1, 1, 1, tga);
        }
        else if(i % 2 == 0)
        {
          color(1, 1, 1, tga);
        }
        else
        {
          color(255, 255, 255, tga);
        }
      }
    for(; x < 480; x++)
      for(y = 0; y < 640; y++)
      {
        if(y< 80)
        {
          color(255, 255, 255, tga);
        }
        else if(y>= 80 && y<160)
        {
          color(0, 255, 255, tga);
        }
        else if( y>= 160 && y< 240)
        {
          color(255, 255, 0, tga);
        }
        else if(y>= 240 && y< 320)
        {
          color(0, 255, 0, tga);
        }
        else if(y>= 320 && y< 400)
        {
          color(255, 0, 255, tga);
        }
        else if(y>= 400 && y< 480)
        {
          color(0, 0, 255, tga);
        }
        else if(y>= 480 && y< 560)
        {
          color(255, 0, 0, tga);
        }
        else
        {
          color(1, 1, 1, tga);
        }

      }
}

void animate(FILE *tga)
{
  int shift = 0;
  int frame_index;

  for(frame_index = 0; frame_index < 24; frame_index++)
  {
    shift += 20;

    HEADER header;

    header.id_len = 0;
    header.map_type = 0;
    header.img_type = 2;
    header.map_first = 0;
    header.map_len = 0;
    header.map_entry_size = 0;
    header.x = 0;
    header.y = 0;
    header.width = 640;
    header.height = 480;
    header.bpp = 24;
    header.desc= 0x20;

    char filename[64];
    sprintf (filename, "anim%d.tga", frame_index);

    tga = fopen(filename, "wb");

    create_header(header, tga);
    draw(shift, tga);

    fclose(tga);
  }
}

int main ()
{
    FILE *tga;
    HEADER header;

    header.id_len = 0;
    header.map_type = 0;
    header.img_type = 2;
    header.map_first = 0;
    header.map_len = 0;
    header.map_entry_size = 0;
    header.x = 0;
    header.y = 0;
    header.width = 640;
    header.height = 480;
    header.bpp = 24;
    header.desc= 0x20;

    tga = fopen("picture.tga", "w+");

    create_header(header, tga);
    draw(header.x, tga);
    animate(tga);

    fclose(tga);

  return 0;
}
