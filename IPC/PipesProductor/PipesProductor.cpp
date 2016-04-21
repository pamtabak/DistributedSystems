/* 
pipe() is a system call that facilitates inter-process communication. It opens a pipe, which is an area of main memory that is treated as a "virtual file". The pipe can be used by the creating process, as well as all its child processes, for reading and writing.
One process can write to this "virtual file" or pipe and another related process can read from it.
If a process tries to read before something is written to the pipe, the process is suspended until something is written.
The pipe system call finds the first two available positions in the process's open file table and allocates them for the read and write ends of the pipe. Recall that the open system call allocates only one position in the open file table */