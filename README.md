# Sudoku-Solution-Validator

#Introduction

The Sudoku solution validator project aims to develop a software tool that can validate the correctness of a given Sudoku solution.
Sudoku is a popular logic-based number puzzle game that requires players to fill a 9x9 grid with digits in such a way that each row, column, and 3x3 sub grid contains all of the digits from 1 to 9 without any repetition. 
The proposed solution validator will verify if the given solution adheres to these rules, ensuring its validity.
This project will employ programming techniques and algorithms to efficiently validate the solution, which can help improve the overall Sudoku-solving experience for enthusiasts and professionals alike.
The solution validator can also serve as a valuable tool for Sudoku puzzle creators to ensure the validity of their puzzles.

#Project Specification

Software Specs:
Main function deals with Threads creations and calling methods/Threads.
ValidateRowThread deals with checking and validating some conditions for rows.
ValidateColThread deals with checking and validating some conditions for columns.
ValidateGridThread deals with validating subgrids of 3*3.
The check_line function deals with checking and validating entries of the sudoku grid like those entries are in the (1-9) range and not equal to (0).
Tools, and Technologies:
Programming Language: C++ language
Tools: Visual Studio Code
Platform: Ubuntu 22.04

#Problem Analysis

The main problem to solve in a sudoku solution validator project is to determine whether a given solution follows the rules of the game and is valid.
This requires analyzing the input solution to check for duplicate numbers within rows, columns, and boxes, as well as ensuring that all spaces are filled with valid numbers.

#Solution Design

The solution for a sudoku solution validator project involves creating an algorithm that checks the validity of the inputted solution.
This algorithm will consist of multithreading to store and compare numbers, as well as loops to iterate through the rows, columns, and boxes of the sudoku grid to ensure that each number is unique and valid.
We have also created an algorithm using a single thread.

#Results

The end result of team efforts is a sudoku solution validator program using the “PTHREADS” library. This essentially checks and validates all test cases which can be applied on a sudoku solution by rows and columns and on sub grids
