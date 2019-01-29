# AbstractVM
----------

AbstractVM is a machine that uses a stack to compute arithmetic expressions between values with different types (int8, int16, int32, float, double)
These arithmetic expressions are provided to the machine as basic assembly commands.

## Lexical info
### Commands

-'push VALUE': pushes a new value on the top of the stack

-'pop': pop the first element of the stack, if stack is empty displays an error

-'dump': if any, display all the values of the stack (without changing the stack)

-'print': if value is a int8 prints it as a char, raise an error otherwise

-'assert VALUE': checks if the value on top of the stack is the same as the one given as parameter, raise an error otherwise

-'add': add the first two operands of the stack

-'sub': sub the first two operands of the stack

-'mul': multiply the first two operands of the stack

-'div': divide the first two operands of the stack

-'mod': modulus between the first two operands of the stack

-'sum': sum of stack

-'avrg': average value of the stack

-'min': min value

-'max': max value

-'asort': ascending sort of the stack

-'dsort': descending sort of the stack

-'exit': tells the program that is ended


The objective of this project. Writing a Filler playe


## Usage

$> make

$> ./avm test/1test.txt

OR

$> sh run_error_tests.sh

$> sh run_std_tests.sh

$> sh run_valid_tests.sh


## Example:

; -------------

; test_avm

; -------------

push int32(42)

push int32(33)

add

push float(44.55)

mul

push double(42.42)

push int32(42)

dump

pop

assert double(42.42)

exit

___________________

42

42.42

3341.25

