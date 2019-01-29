AbstractVM
42 project: AbstractVM

Objective
create a program which executes some basic pseudo-assembly commands. All the values are saved in the same stack-like structure, even if the type between them is not the same (int32, float, ..). When an operation between values with different types occurs the result will have the most precise type of the two operands.

Lexical info
For commands who need a VALUE the type can be: int8(N), int16(N), int32(N), float(Z) and double(Z)
The char ';' is consider as the beginning of the comment for that line
You can put as many spaces before-after any param
Commands
'push VALUE': pushes a new value on the top of the stack
'pop': pop the first element of the stack, if stack is empty displays an error
'clear': clears the stack from all values
'dump': if any, display all the values of the stack (without changing the stack)
'print': if value is a int8 prints it as a char, raise an error otherwise
'assert VALUE': checks if the value on top of the stack is the same as the one given as parameter, raise an error otherwise
'add': add the first two operands of the stack
'sub': sub the first two operands of the stack
'mul': multiply the first two operands of the stack
'div': divide the first two operands of the stack
'mod': modulus between the first two operands of the stack
'exit': tells the program that is ended
Usage
$> ./avm [-option1 -option2 .. -optionN] [filepath]

Options
-d -> 'debug' mode while executing the program
-h -> displays this help menu and exit
-s -> 'strict' comparison with 'assert' command
-v -> displays one-line comments
-V -> -v option + displays precision with 'dump' command
Notes
All arithmetics operations with 2 values are done with the form 'v2 op v1', where v1 is the first element on the stack and v2 the second
All arithmetics operations pop the value(s) from the stack and insert the result as a new instance
You can put as many option as you like
If you do not give a filepath the program will read in the standard input, insert ';;' to end reading.
If the program ends without calling the 'exit' command an error will be displayed