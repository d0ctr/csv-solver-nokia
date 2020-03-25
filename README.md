# csv-solver-nokia
Home task from NOKIA
## Task
Develop a program that would take .csv file as an input and perform manipulation with its content.
First row of the file contains horizontal headers represented as a word or a letter.
First item of each row contains vertical headers represented as natural numbers (that may not be in ascending order or in any).
Item in file is either an integer non-negative value or a fomula like this ```=ARG1 OP ARG2```. ARG is a horizontal header, number is a vertical header, OP is one of these ```+ - * ?``` operations.
### Input example
```
,A,B,Cell
1,1,0,1
2,2,=A1+Cell30,0
30,0,=B1+A1,5
```
## Requirements
Developed program must take name of the file as a command line argument, solve equations in cells (if any) and output csv-formated table in standart output.
Result for example below would be:
```
,A,B,Cell
1,1,0,1
2,2,6,0,
30,0,1,5
```
## Solution
To solve this task I developed class **CSVParser** that takes csv-like table and parses it into 2 maps, one with solved cell and another with unsolved ones. It also contains method to solve formulas in cells and complete table.
## Running my program
I have wrote a Makefile that has following instructions: clear object files, clear executables, run, compile and all, that combines other instruction. Instruction run would run compiled executable with file *task.csv* as a command line argument.
