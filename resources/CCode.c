#include <stdio.h>
#include <string.h>
#include <error.h>
#include <ctype.h>

#include <gd.h>
#include <gdfontg.h>
#include <gdfontl.h>

static int red = 0;
static int green = 0;
static int blue = 0;

void setupcolor(char *str);

int main(int argc, char *argv[]) {
 FILE *pngout = {0};
 gdImagePtr img;
 int fgcol, bgcol;
 char *str = NULL;
 char *fname = NULL;

 if(argc != 5) {
  fprintf(stderr, "Usage: ./imstr \"STRING\" FFFFFF 000000 image.png\n");
  return 1;
 } else {
  str = argv[1];
  img = gdImageCreate((gdFontGiant->w * strlen(str)) + 2, gdFontGiant->h + 2);
  setupcolor(argv[2]);
  bgcol = gdImageColorAllocate(img, red, green, blue);
  setupcolor(argv[3]);
  fgcol = gdImageColorAllocate(img, red, green, blue);
  fname = argv[4];
 }

 gdImageString(img, gdFontGiant,
  gdImageSX(img) / 2 - (strlen(str) * gdFontGiant->w / 2),
  gdImageSY(img) / 2 - gdFontGiant->h / 2, str, fgcol);

 if((pngout = fopen(fname, "w")) == NULL)
  error(1, 0, "Error - fopen(): %s", fname);
 else {
  gdImagePng(img, pngout);
  fclose(pngout);
 }

 gdImageDestroy(img);
 return 0;
}

void setupcolor(char *str) {
 char r[3] = {0}; 
 char g[3] = {0};
 char b[3] = {0};
 char *ptr = NULL;

 if(strlen(str) != 6)
  error(1, 0, "Error - Invalid hex color length: %s", str);

 for(ptr = str; *ptr; ptr++)
  if(!isxdigit(*ptr))
   error(1, 0, "Error - Non hexdigit: %s", str);
  else if(isupper(*ptr))
   *ptr = tolower(*ptr);

 r[0] = str[0], g[0] = str[2], b[0] = str[4]; 
 r[1] = str[1], g[1] = str[3], b[1] = str[5]; 
 r[2] = '\0',   g[2] = '\0',   b[2]  = '\0'; 

 sscanf(r, "%X", &red);
 sscanf(g, "%X", &green);
 sscanf(b, "%X", &blue);

 return;
}