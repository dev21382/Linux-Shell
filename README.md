# Linux-Shell
It is a shell which has been coded in C with internal and external commands 

The assumptions made by me while developing the shell are as follows:

1) The name of the files do not have any space between them while entering the commands.
2) Each command given in the shell is treated to be in parts if they have a blank space between them.
3) The options which I have implemented are to be given one by one and not together like -ir in rm -ir file; it has to be like rm -i file or rm -r file.
4) usage of double quotations is not allowed to indicate files with spaces between them as I have not considered that option in my code.
5) First, all the files should be compiled post which one would go on to call the main shell so as to execute the commands.
6) Make sure that the shell has permission to execute.
7) The user should not press enter multiple times in the shell without any reason as that would cause the shell to not quit.
8) In the cd command one shouldn't put it as the only argument.


Format of the commands:

1) quit: exits the shell by printing out Quitting...

2) cd : This command changes the directory of the process, cd has 2 options namely .. and ../.. with it with the format being cd .. 
and cd ../.. where cd .. takes the path back to one directory while the cd ../.. takes the path back 2 directories. It does not support multiple options at a single time. 

3) echo : It prints the given argument in the console. The format is echo *  or echo [ARG], where the number of arguments is 2, or echo -n [ARG] where
 a new line character isn't printed on the console. It does not support multiple options at a time. So escape characters will not be printed according to their roles in 
the console and they will be printed as it is. In the case of too many arguments (max 3) it will generate error).

4) pwd : pwd command is used to print the present working directory onto the console. It's format is simple either pwd or pwd -p or pwd -l with -p and -l being the options.
Here, -p option prints the physical path of the currently working directory whereas -l prints the working directory with logically handling symlink(this is the default).
Only 1 option is to be used at a time. It gives appropriate errors upon invalid input also showing the correct format.

5) mkdir and mkdir&t : this command is used to make a new directory. mkdir [-v | -p] FILES is the format to be followed for this command.
there are two options -v and -p where -v command notifies directories that are created and failed and the -p in case the parent directory of the directory to be made is 
not present it runs mkdir for parent directory first recursively. Any kind of error resulting from a system call or c library call is accounted for.The cases for nested 
directories are handled appropriately, options are to be given one by one.

6) rm and rm&t : It removes the files present in the system. the format is rm [-i | -r] FILES..., -i prompts the deletion of all objects and -r recursively deletes everything 
inside the mentioned directory (if a directory is provided) and then further proceeds to delete the directory.Any kind of error resulting from a system call or c library call 
is accounted for. Throws error if directory is used without -r option. Only 1 option has to be entered at a time.

7) cat and cat&t : It prints the content of the file mentioned in the FILES. The format is cat [ > | >> ] FILE. Here one can also use the normal cat [filename] option to just read 
the file contents and print them out to the console. The option > is used to write to the file whereas the >> option is used to append to the given file.Any kind of error resulting 
from a system call or c library call is accounted for.Only 1 option at a time can be provided.

8) ls and ls&t : It lists the contents of the directory mentioned in the PATH. In the case nothing is mentioned then the cwd is set as the PATH.
The options to be used are of the format ls [-a | -1] where -a gives all the files in directory both hidden as well as unhidden. And the -1 command is used to view the files in the given directory 
in a new line each for every file in it.Only 1 of the options can be used at a time.Any kind of error resulting from a system call or c library call is accounted for.Max 3 arguments allowed.

9) date and date&t : It prints the date and the time of the system or the files that have been mentioned (with -r option ofcourse)
the format of the command can be either date [-u] or date [-r] FILES. Here, the -r option is used to generate the time of the last modification of the files. -u prints the 
current date and time of the system according to the GMT.Any kind of error resulting from a system call or c library call is accounted for. Only 1 option is to be a given at
 a time.
