# CopyFiles
## This is a C command line tool designed to work on Windows and Linux as well. The purpose of this tool is to copy all the files matching a given pattern from a user given input to a user given destination directory.

In order to use this application, you have 2 options:

1. Compile the code using a C compiler (e.g: https://sourceforge.net/projects/mingw-w64/) 
  - in order to compile it, write "gcc TestApp.c"
  - there will be a generated "a.exe" file that you need to execute
  - in order to use the "a.exe" file you have to write a command line like this: a <input folder path name> <output folder path name> <pattern> (4 parameters)
      e.g.: a C:/Users/Me/Desktop/Folder C:/Users/Me/Desktop/OtherFolder ex
  - Following the given example, the application will search in C:/Users/Me/Desktop/Folder and in its sub-directories all the files that contain "ex" and will copy them in     C:/Users/Me/Desktop/OtherFolder

2. Download the CopyFile.exe file. Using this way, you don't need to have a C compiler on your computer. Just open a command prompt and follow the same pattern described at point 1
      e.g.: CopyFile C:/Users/Me/Desktop/Folder C:/Users/Me/Desktop/OtherFolder ex
      
  ![Exaample](C:\Users\Radu\Desktop\LogPhoto.jpg?raw=true "Title")
  
