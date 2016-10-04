cd.c is at inc/
uncomment the main() code, compile it and run the executable similar to cd command.
eg) ./a.out ~/Downloads

Make note of any bugs.

If pushing, don't add temporary files like .o

Maintain a proper directory hierarchy.

B)

Instructions :
Run make to build and execute

Bugs:
When exiting the shell using ctrl+D, it gives seg fault

TODO:
mulit-commands (Done)
background processes and list background Process (done)
piping
redirection

Doubts:
when execvp fails, have to manually exit(0) from child process. (Cleared)

##################################################################################################################################################
Fundaes for piping:
Basically for piping what we need to do is, the output of the first process should be input to the second process.
First use the pipe() system call -- pipe() creates a pair of file descriptors, pointing to a pipe inode, and places them in the array pointed to by 'fd'. fd[0] is for reading, fd[1] is for writing. This is before forking. And, fd[] should have been declared as an int array of size 2 before.
Then fork the process. Each process will now have its own copy of fd[0] and fd[1].

Now, in the child process you need to close the write end of the file. So use 'close(fd[1])'.

In the parent close the read end of the file using 'close(fd[0])'.

Then use the read system call in the child to read(i.e input) and write system call in the parent to write (i.e. output). Go through documentation for that.
##################################################################################################################################################
