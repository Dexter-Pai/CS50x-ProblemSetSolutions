#include <stdio.h>
#include <iostream>
#include <string.h>

//global definitions
#define FILENAME_LENGTH 80

//global variables
namespace global
{
  char filename[FILENAME_LENGTH] = "";
}

//prototypes
void filenamePrompt(void);
long obtainFileSize(FILE *file);
void readAndPrint (char *c, long a, FILE *b);
void output(char* c, long size);
void noOutput(void);
void runProgram(void);

//main function
int main(void)
{
    system("clear");
    //prompting user for filename
    filenamePrompt();
    FILE *file = fopen(global::filename,"r");
    if (file == NULL)
    {
      std::cout << "No file with such name, program will terminate.\n";
      return 1;
    }

    //obtain file size
    long lSize = obtainFileSize(file);

    //memory leaks happen tho :(
    char* c = (char *)malloc(sizeof(char)*lSize);
    readAndPrint (c, lSize, file);

    //prompt for output
    char ans;
    std::cout << "Would you like to output to external as python file? (Y/N)\n";
    do
    {
      std::cin >> ans;
    }
    while (ans != 'Y' && ans != 'N');

    //write to output or not
    (ans == 'Y') ? output(c, lSize) : noOutput();
    if(ans == 'N')
    {
      free(c);
      fclose(file);
      return 0;
    }

    //system("cls"); apparently not in this version of vscode
    system("clear");

    //run the program
    runProgram();

    //free memory
    free(c);
    fclose(file);
    return 0;
}

//prompt for file name
void filenamePrompt(void)
{
  printf("enter filename: ");
  scanf("%s",global::filename);
}

//file size
long obtainFileSize(FILE *file)
{
  fseek (file , 0 , SEEK_END);
  long lSize = ftell (file);
  rewind (file);
  return lSize;

    //working but disregard for now
    // std::string filename;
    // std::cout << "Enter filename: ";
    // std::getline(std::cin, filename);
    // FILE *file = fopen(filename, "r");
    // int *c = NULL;
}

//read and print the file
void readAndPrint (char *c, long a, FILE *b)
{
  fread(c , sizeof(char), a, b);
  std::cout << c << "\n";
}

//output file
void output(char* c, long size)
{
  FILE *output = fopen("output.py" , "w");
  fwrite(c, sizeof(char), size, output);
  fclose(output);
}

//no output file
void noOutput(void)
{
  std::cout << "No file made\n";
}

//run program?
void runProgram(void)
{
  char ans;
  std::cout << "Would you like to run the program? (Y/N)\n";
  do
  {
    std::cin >> ans;
  }
  while(ans != 'Y' && ans != 'N');

  if (ans == 'Y')
  {
    system("python output.py");
  }
}

    // std::cout << "hello, world!\n";
    // int x, y;
    // std::cout << "Input x: ";
    // std::cin >> x;
    // std::cout << "Input y: ";
    // std::cin >> y;
    // std::cout <<" x + y = "<<x+y<<"\n";