#ifndef MOOD_H
#define MOOD_H

#include <iostream>
#include <string>
#include <cstring> //to samo co string.h
#include <vector>
#include <stdio.h>
#include <ctime>
#include <fstream>



using namespace std;



#define MAX_SEN_LENGTH 100

typedef enum { BAD = 12, NEUTRAL = 14, GOOD = 10 } MOOD_COLOR;

class Moods{
public:
    static int Num;

    string date; //dd.mm.rrrr
    MOOD_COLOR vibe;
    string words[5];//tab for 5 words' note to decribe the reasons of your mental state that day

    Moods();

    void get_currdate( void );
    void get_vibe( void );
    void get_info( void );
    void create_today( void );
};

class Node{
public:
    Moods *today;
    Node *next;

    Node( Moods *data );
};

class SLList{
public:
    Node *head;

    SLList();

    void insertNode( Moods * );
    void deleteNode( Moods );
    void printSLList( void );
    void deleteSLList( void );
};

void cleaning( void ); //function to clean input
void printMood( Moods );
int compareNode( Moods, Moods );
void moods_export( SLList * ); //save all data from list in the moods.txt file
void moods_import( SLList * ); //read the moods.txt file if it exists and add all the data to the singly linked list

#endif



