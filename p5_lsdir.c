/*    Project 5: lsdir */

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

int  listDir(const char *path)
{
 DIR *dir;
 struct stat statbuf;
 struct dirent *dp;
 char cwd[128]; //store current working directory
 getcwd(cwd, sizeof(cwd)); // get current working directory

 if((dir = opendir(path)) == NULL)
 {
  printf("\n%s/%s: \n%s/%s unreadable\n", cwd, path, cwd, path);
  return;
 }

 if(chdir(path) == -1) //error case - couldn't change directory
	return;

 while(dp = readdir(dir))
 { 
	if((stat(dp->d_name, &statbuf)) == -1)
	{
		continue;
	}
  if((dp->d_name[0]) != '.' && S_ISDIR(statbuf.st_mode))
    //if not a current working directory 
    //and checks if its a directory passing info of the file
     printf("%s\n", dp->d_name);
  //prints directory name 
 }
 rewinddir(dir); // start rereading from the beginning of the directory (pg. 69)

 while(dp = readdir(dir))
 {
	if(strcmp(dp->d_name, ".") == 0)
	  // "." current working directory (pg. 64)
		continue;

	if(strcmp(dp->d_name, "..") == 0)
	  // ".." parent directory of the current working directory
		continue;

	if((stat(dp->d_name, &statbuf)) == -1)
        {
                continue;
        }

	if((dp->d_name[0]) != '.' && S_ISDIR(statbuf.st_mode))
	listDir(dp->d_name);
	//recursive
	//goes back to listDir
	//does it for directory d_name 
 }
  
 closedir(dir);
 chdir(cwd);	

 return 0;
}
 
main(int argc, char *argv[])
{
 const char *pathname;
 if(argc < 2)
	listDir(".");
 else
 {
 	pathname  = argv[1];
	listDir(pathname);
 }
 return 0;
}
