# AI-Fundamentals-In-C
This repo follows some course work, which encouraged looking at AI from the very fundamentals.

1. Tic-Tac-Toe - Non AI Approach & AI Approach
2. 8 Puzzle using Hill Climbing - Simple Hill Climbing & Steepest Hill Climbing
3. 8 Puzzle Using BFS (Best First Search) (A simplified version of A* (A-star) algorithm)
4. Prolog System
5. Single Perceptron

## Lab 1 Tic-Tac-Toe
The Non AI approach 
1. Takes the state of the board.
2. Validates if such a state is possible
3. Calculates an index, which is a way of visualising where such a state would fall within all possible states.

The AI approach
1. Takes the state of the board.
2. Validates if such a state is possible
3. Generates all possible moves
4. Determines which move is the most optimal using a hardcoded scoring system

## Lab 2 8 Puzzle Using Hill Climbing

Simple Hill Climbing Approach
1. Takes the state of the board
2. While Current Heuristic less than New Move Heuristic
    - Generate new move
    - Calculate heuristic
3. Execute new move

Essentially, this approach moves to the state which is found first (not necessarily the most optimal move).

Steepest Hill Climbing Approach
1. Takes the state of the board
2. Generate all possible moves and their heuristics
3. Execute most optimal move

## Lab 3 8 Puzzle Best First Search

A* (A-star) Approach
1. Takes the state of the board
2. Generate all possible moves and their heuristics and total cost to traverse till the state.
3. If not in CLOSED, after exploring neighbours, place in CLOSED. if already in CLOSED, update cost if it is lesser than current.
4. Continue by taking least cost state from OPEN.

## Lab 4 Prolog System

An example of a system in Programmable Logic (SWI-Prolog).

## Lab 5 Single Perceptron

Neuron Model

Perceptron Learning Rule

Perceptron Convergence Theorem