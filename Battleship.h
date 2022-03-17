#ifndef BATTLESHIP_H
#define BATTLESHIP_H
/*
Name: Milee Owen
Class: CPSC 121, Spring 2019
Date: April 04, 2019
Programming Assignment: PA8
Description: Create a program that plays the game battleship.
*/
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
// global variables
const int NUM_ROWS = 10;
const int NUM_COLS = 10;
// function prototypes
void welcomeScreen();
void selectWhoStartsFirst(bool&, bool&);
void initializeBoard(char[NUM_ROWS][NUM_COLS], int, int);
void displayBoard(char[NUM_ROWS][NUM_COLS], int, int);
void displayOpponentBoard(char[NUM_ROWS][NUM_COLS], int, int);
void manuallyPlaceShipsOnBoard(char[NUM_ROWS][NUM_COLS], string[5], char[5], int[5]);
void randomlyPlaceShipsOnBoard(char[NUM_ROWS][NUM_COLS], string[5], char[5], int[5]);
int checkShot(char[][NUM_COLS], int, int);
bool isLoser(char[][NUM_COLS], int, int, bool&, bool&);
void updateBoard(char[NUM_ROWS][NUM_COLS], int, int, int);
void outputCurrentMove(ofstream&, int, int, int, bool, bool);
void checkIfSunkShip(char[NUM_ROWS][NUM_COLS], ofstream&, int, int, bool&, bool&, bool&, bool&, bool&);
void outputStats(ofstream&, double, double, double, double, double, double);
#endif
