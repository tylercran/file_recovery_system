#include <stdio.h>
#include <stdlib.h>


void findDrives()
{

  FILE *fp;
  // max path for Linux.
  char path[4096];

  /* Open the command for reading. */
  //fp = popen("lsblk | awk '{if ($7 ~ \"media\") print $7}'", "r");
  fp = popen("lsblk | awk '{if ($6 == \"part\" && $7 ~ \"/\") print $7}'", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }
  
  int count = 1;


  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    printf("%d: %s", count, path);
    count++;
  }
  
  /* close */
  pclose(fp);
}

// FNR > 1 is to get rid of header. $7 != "" checks if it's blank. Super convoluted one, BUT...
// lsblk | awk 'FNR > 1 {if ($7 !~ \"/snap/\") print $7}' | awk '{if ($1 != \"\") print $1}'

// This should work better. I believe all drives we care about are going to be in /media/(username)
// Second note to this. Internal drives used for your specific os aren't listed, but... well... your computer wouldn't be running too well without them.
// lsblk | awk '{if ($7 ~ \"/media/\") print $7}'

// Could also use (this one is probably best):
// lsblk | awk '{if ($6 == \"part\" && $7 ~ \"/\") print $7}'




