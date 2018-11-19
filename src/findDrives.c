#include <stdio.h>
#include <stdlib.h>


int main()
{

  FILE *fp;
  char path[10];

  /* Open the command for reading. */
  fp = popen("ls /sys/block", "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }
  
  int hi = 1;

  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    printf("%d: %s", hi, path);
    hi++;
  }

  /* close */
  pclose(fp);

  return 0;
}
