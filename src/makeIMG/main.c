#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.H"

FILE* f;
char imgLoc [1024] = {'\0'};
char drive  [1024] = {'\0'};
char imgName[256]  = {'\0'};
char imgPath[2048] = {'\0'};


void makeImage();


int main(int argc, char** argv)
{

  printf("*************************************************************************\n"
         "It is recommended that you use an image to restore your files.  Would you\n"
	 "Like to create one now? Select no if you already have an image.\n"
	 "0. No\n"
	 "1. Yes\n");
  int createImage = getInt_range(0, 1);
  if(!createImage)
  {
    f = popen("zenity --title=\"Select Image\" --file-selection 2>> errorLog", "r");
    fgets(imgPath, 1024, f);
    imgPath[strlen(imgPath) - 1] = '\0';
    fclose(f);
  }

  else
  {
    f = popen("zenity --file-selection --title=\"Select drive to image\" --filename=/dev/disk/by-label 2>> errorLog", "r");
    fgets(drive, 1024, f);
    fclose(f);
    drive[strlen(drive) - 1] = '\0';
  
    if(drive[0] == '\0')
    {
      printf("No drive selected. Exiting.\n");
      return 1;
    }
    
    printf("%s\n", drive);
  }
  
  if(createImage)
  {
    makeImage();
  }
  
  //store path in /tmp to be read by recovery program  
  system("mkdir /tmp/FileRecovery 2>> errorLog");
  FILE* outFile;
  outFile = fopen("/tmp/FileRecovery/imagePath", "w");
  fputs(imgPath, outFile);

  return 0;
}


void makeImage()
{
  printf("Please select the directory you would like to save your image to.\n");
  f = popen("zenity --title=\"Select directory to store image\" --file-selection --directory 2>> errorLog", "r");
  fgets(imgLoc, 1024, f);
  fclose(f);

  imgLoc[strlen(imgLoc) - 1] = '\0'; //There is a newline char there, get rid of it
  
  if(imgLoc[0] == '\0')
  {
    printf("No image location selected. Exiting.\n");
    imgPath[0] = '\0';
    return;
  }
    
  //Name of image
  printf("Please enter what you would like to name your image: ");
  scanf("%s", imgName);
  printf("\n");
   
  if(imgName[0] == '\0')
  {
    printf("No filename provided. Exiting\n");
    imgPath[0] = '\0';
    return;
  } 
    
  //build path of new image
  strcat(imgPath, imgLoc);
  strcat(imgPath, "/");
  strcat(imgPath, imgName);
    
  //build system call
  char call[3088];
  snprintf(call, sizeof(call), "sudo dd if=%s of=%s bs=1M", drive, imgPath);
  printf("Call: %s\n", call); 
  
  printf("***********************************************\n"
         "An image of           %s\n"
         "will be created here: %s\n\n"
	 "This process will likely take several minutes\n"
	 "Continue?\n"
	 "0. No\n"
	 "1. Yes\n", drive, imgPath);

  int choice = getInt_range(0, 1);

  
  if(choice)
    system(call);
  else
    imgPath[0] = '\0';
}
