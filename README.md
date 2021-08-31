# chmod command

The chmod command is used to change the permissions of a file or directory. To use it, you specify the desired permission settings and the file or files that you wish to modify.

# What are Permissions?

There are three types of permissions-
• r: Read permissions. The file can be opened, and its content viewed.
• w: Write permissions. The file can be edited, modified, and deleted.
• x: Execute permissions. If the file is a script or a program, it can be run (executed).

# How it Works?

Syntax-
chmod [reference][operator][mode] file...

The references are used to specify for which user we want r=to set the permissions:
Reference Class Description
u owner file's owner

g group users who are members of
the file's group

o others users who are neither the
file's owner nor members of
the file's group

a all All three of the above, same as ugo
The operators are used to set how the permission is to be set-
Operator Description

-         Adds the specified modes to the
          specified classes

*         Removes the specified modes from
          the specified classes

= The modes specified are to be made
the exact modes for the specified
classes

The mode is used to specify the permissions that are to be given.
r Permission to read the file.
w Permission to write (or delete) the file.
x Permission to execute the file, or, in
the case of a directory, search it.

It is easy to think of the permission settings as a series of bits (which is how the computer thinks about them). Here's how it works:
rwx rwx rwx = 111 111 111 or 777
rw- rw- rw- = 110 110 110 or 666
rwx --- --- = 111 000 000 or 700
and so on...

# cat command

Cat(concatenate) command is very frequently used in Linux. It reads data from the file and gives their content as output. It helps us to create, view, concatenate files.
SYNTAX-
cat [OPTIONS][file_names]

OPTIONS: All different options.
FILE_NAMES: Zero or more file names.

# Creating a New File-

$ cat > file1.txt
Display File Contents-
The most basic and common usage of cat command is to display contents of a file.
					$ cat file1

# Redirect Contents of a File:

Instead of displaying the output to the stdout, you can redirect it to a file.
$ cat file1.txt > file2.txt
Use  (>>) to append to a file.
				  $ cat file1.txt >> file2.txt

# Concatenating files-

It is also used to concatenates 2 files
\$ cat file1.txt file2.txt

# echo command

echo command in linux is used to display line of text/string that are passed as an argument . This is a built in command that is mostly used in shell scripts and batch files to output status text to the screen or a file.
Syntax :
echo [option][string]

Options of echo command

NOTE :- -e here enables the interpretation of backslash escapes

1. \b : it removes all the spaces in between the text
   echo -e "Hello \bWorld"

2. \c : suppress trailing new line with backspace interpretor ‘-e‘ to continue without emitting new line.
3. \n : this option creates new line from where it is used.
4. \t : this option is used to create horizontal tab spaces.
5. \r : carriage return with backspace interpretor ‘-e‘ to have specified carriage return in output.
6. \v : this option is used to create vertical tab spaces.
7. \a : alert return with backspace interpretor ‘-e‘ to have sound alert.
8. echo \* : this command will print all files/folders, similar to ls command .
9. -n : this option is used to omit echoing trailing newline .
