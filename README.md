# Get Next Line
get_next_line() is a C function that reads the next line from a file and returns it. This project was developed as part of the **Common Core** curriculum at [**42 São Paulo**](https://www.42sp.org.br/).

## What You Will Learn
- What is a FD in Unix systems
- File manipulation in C
- How to use static variables

## How to Test
Clone the repository and compile the files with your preferred C compiler, such as **clang** or **gcc**.

**Note:** _the project is separated into two parts, the mandatory and the bonus. If you want to compile the project with the bonus, only the files with "\_bonus" at the end of the name should be compiled_.

## Project Structure
The project is divided into two parts, the **mandatory** and the **bonus**, which includes the entire original project and more resources.

### Files
- `get_next_line.c` includes the `char  *get_next_line(int fd)` function and all the main logic of the project itself.
- `get_next_line_utils.c` includes **utility functions**, which are part of [**Libft**](https://github.com/LuizGandra/libft-42) or were adapted from functions in that library.
- `get_next_line.h` is the project header file.

## Bonus
_All bonus files have "\_bonus" at the end of their names. To run the project with the bonus, simply compile these files, as they also include the mandatory logic_.

**The bonus has two requirements:**
- [x] Develop the function using only one static variable.
- [x] The function must be able to handle multiple file descriptors at the same time.
