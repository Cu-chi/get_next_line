# Get Next Line
Reading a line from a fd is way too tedious.

⚠️ Disclaimer: This project is released for educational purposes. As plagiarism is strictly forbidden within the 42 curriculum, please do not copy-paste this code without fully understanding it.  
#### 📖 About
Get Next Line (GNL) is a programming project at 42.  
The goal is to write a function that returns a line read from a file descriptor.  
The catch? The function must work regardless of the buffer size defined at compilation time and must handle memory dynamically without leaks.  
It teaches the concept of static variables in C to persist data between function calls.  
#### 🛠️ Usage
Function Prototype
```C
char *get_next_line(int fd);
```
| Parameter | Description |
| --- | --- |
| `fd` | The file descriptor to read from.|

| Return Value | Description |
| --- | --- |
| `char *` | The line read from the file descriptor (including the `\n`).  `NULL`  if there is nothing else to read or if an error occurred.|

#### ⚙️ Compilation
You must compile the source files with your project.  
You can define the buffer size (`BUFFER_SIZE`) using the -D flag (default is `512` if not defined).  
To handle more file descriptors simultaneously, redefine `MAX_FD` during compilation (e.g., `-D MAX_FD=4096`). Default is 1024.
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=4096 get_next_line.c get_next_line_utils.c main.c
```
#### 📋 Example
Here is a simple main.c to test the function:
```C
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break;
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
#### 🧪 Testing
This project has been tested with various buffer sizes (1, 42, 9999, 10000000) and passes strict memory leak checks (Valgrind).  
  
**Valgrind**: No memory leaks. (still reachable when we don't read all the file)  
**Timeout**: Passes strict timeout tests.  
**Static Variable**: Properly managed between calls.  

*Note: A linked list approach could offer better scalability for huge buffers.*
