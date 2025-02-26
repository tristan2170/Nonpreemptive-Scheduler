# Nonpreemptive Scheduler v1.0.0
## Overview
* The goal of this application is to imitate the means by which an Operation System executes processes. 
* This application is intended to use a "non-preemptive" system, where each process executes and finishes to completion, with no chance for interruption. 
* A file input by the user represents a list of processes in the Operating System's ready queue awaiting execution. Each line of the file imitates a Process Control Block, which details the Process ID, Priority, Execution Time, and the operation to be performed on two operands. 
* Once the file's contents are read, the policy chosen by the user executes and stores the result of each operation into a FIFO structure. From there a logger function renders the results to the user in the order of the chosen scheduling policy. 

## Set Up
### Format for the Input File
* Each line of your input file should have the following format
    ```
     <pid>,<priority>,<exec_time>,<fcn>,<operand1>,<operand2>
    ```
* Be sure to leave no space between the commas. For this version of the application please use exactly ten lines. 
-  The values you choose for each item are completely up to you. All values in the line should be  integers except for "fcn". "fcn" represents one of the four operations you'll be performing on operand1 and operand2:
    - fib
    - power
    - prod
    - sum
* fib is the only function that takes in one operand, so for the second operand please just put a zero, or any value you like. But, only the first operand will be used. 

### Running the Application
* Because this application uses POSIX functions, it must run in a POSIX-compliant environment. If you're using a macOS, POSIX functions will run in the command line.  Otherwise, you can use a Linux distro such as Ubuntu, or Debian. You can also use a compatibility layer like Windows Subsystem for Linux. Or, the most simple method would be to use Cygwin, which provides you a simple command line tool that can execute linux commands. If you choose Cygwin, in the installation process be sure to install one or more of the necessary packages such as; cygwin-devel, gcc-core, mingw64-i686-pthreads. Choosing Cygwin may also require adding the path of its bin folder to your Environment Variable's Path.
* To compile the application execute the command :
    ```
    gcc main.c operations.c -o main.exe
    ```
* Once compiled, run the application by executing the command:
    ```
    ./main.exe <sched_pol> <input.txt>
    ```
    * <input.txt> represents your input file, and  <sched_pol> represents one of the three policies you can choose for this application:
        - sjf
        - fcfs
        - priority
* Be sure to place those values in the exact order they're specified, as the program expects them in a particular order. Be sure to use the exact spelling specified in the documentation. Also be sure that your input file is in the same directory as the source code, otherwise you must reference the entire path of where your input file is stored. 

Note:
 Be conscious of incorrect spellings and improper inputs at the command line, or in your input file. This may cause unexpected behavior from the application.
