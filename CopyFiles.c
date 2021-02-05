#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include<stdlib.h>

int counter = 0;

/*Function to create the LOG file at the user specificated output.
  This function will create the file or if it already exists it will append to it*/
void LogFileHandle(char *path,char *text)
{
    FILE *f;
    char logPath[128];

    sprintf(logPath,"%sLogFile.log",path);  
    f = fopen(logPath,"a+");
    if(f == NULL)
    {
        printf("\nFailed to create the LOG file! Check the output path! \n");
        exit(0);
    }
    
    fprintf(f,text);
}

/*This function open the input file in read mode in order to take its data.
  The output path will be opened in write mode in order to copy the data inside the new file*/
void CopyMatchedFiles(char *sourcePath,char *destinationPath,char *logPath)
{
    FILE *inputFile, *outputFile;
    int data;

    inputFile = fopen(sourcePath,"rb");
    outputFile = fopen(destinationPath,"wb");

    if(outputFile==NULL)
    {
        printf("\nInvalid destination path!\n");
        fclose(outputFile);
        exit(0);
    }

    if(inputFile==NULL)
    {
        printf("\nInvalid source path!\n");
        fclose(inputFile);
        exit(0);
    }
    
    while(1)
    {
        data=fgetc(inputFile);
        if (feof(inputFile)) 
            break;
        fputc(data,outputFile);
    }
    fclose(inputFile);
    fclose(outputFile);

    char text[512];
    sprintf(text,"\n%s -- succesfully copied to --> %s\n",sourcePath,destinationPath);
    LogFileHandle(logPath,text);
}

/*This function recursively parse the input path folder structure.
  It will check every file inside every folder in order to find in the file name the user pattern (argv[3])*/
void ParseFolders(char *inputFolderPath,char *outputFolderPath,char *pattern)
{
    char path[1024];
    char pathToCopyFrom[1024];
    char pathToCopyIn[1024];

    struct dirent *dp;
    DIR *dir = opendir(inputFolderPath);
    DIR *check;

    /* If there is a FILE - not a DIR given at the start of the program,
     the program will return and close. If there is a FILE - not a DIR given 
     as a new recursion parameter, the function will return to the old path and search again */
    if (!dir)
    {
        return;
    }
    
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            //Check for pattern match
            if((strstr(dp->d_name,pattern) != NULL)) 
            {
                sprintf(pathToCopyFrom,"%s\\%s",inputFolderPath,dp->d_name); //if you use Linux, replace "\\" with "/"
                sprintf(pathToCopyIn,"%s%s",outputFolderPath,dp->d_name);  
                check = opendir(pathToCopyFrom);
                if(check) //safety - in order not to copy an entire directory
                {
                    return;
                }
                counter++;
                CopyMatchedFiles(pathToCopyFrom,pathToCopyIn,outputFolderPath);
            }
            // Construct new path from our base path
            strcpy(path, inputFolderPath);
            strcat(path, "\\"); //if you use Linux, replace "\\" with "/"
            strcat(path, dp->d_name);
            ParseFolders(path,outputFolderPath,pattern);
        }
    }
    closedir(dir);
}

int main(int argc,char *argv[])
{
    if(argc != 4)
    {
        printf("Please give as arguments: \n 1. Input folder path \n 2. Output folder path \n 3. Wanted pattern\n");
        return 1;
    }

    time_t t = time(NULL); 
    struct tm tm = *localtime(&t);
    char text[512];

    sprintf(text,"Date: %d-%02d-%02d \nTime: %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    LogFileHandle(argv[2],"-- Program started --\n");
    LogFileHandle(argv[2],text);
    sprintf(text,"* started to search for \" %s \" in %s folder structure\n",argv[3],argv[1]);
    LogFileHandle(argv[2],text);

    ParseFolders(argv[1],argv[2],argv[3]);

    if(counter == 0) //counter incremented in ParseFolder function if there is any match between the pattern and the file name
    {
        sprintf(text,"! There are no files with \" %s \" pattern in this folder structure !\n",argv[3]);
        LogFileHandle(argv[2],text);
        sprintf(text,"Ended at: %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
        LogFileHandle(argv[2],text);
    }
    else
    {
        sprintf(text,"\n\n--> %d files successfully copied! <--\n",counter);
        LogFileHandle(argv[2],text);
        tm = *localtime(&t);
        sprintf(text,"Ended at: %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
        LogFileHandle(argv[2],text);
        printf("\n Program ended sucessfully! Check the LOG file -located in the output folder- for more details!\n");
    }

    return 0;
}


