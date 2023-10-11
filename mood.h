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


/**
 * @brief Enumerated type with 3 possible mood states that the user can pick from.
*/
typedef enum { BAD, NEUTRAL, GOOD } MOOD_COLOR;

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

/**
 * @brief Class to store a Moods element created.
*/
class Node{
public:
    Moods *today;
    Node *next;
    
    /**
     * @brief Constructor to add data to a Node object.
     * 
     * @param Moods * - data to be saved in a created object
    */
    Node( Moods * );
};

/**
 * @brief Class for Single Linked List to store all the Moods created.
*/
class SLList{
public:
    Node *head;

    /**
     * @brief Constructor for SLList, sets head as a NULL pointer.
    */
    SLList();

    /**
     * @brief Creates new node and add it to the SSList.
     * 
     * @param Moods * - data to be saved in a new node
    */
    void insertNode( Moods * );

    /**
     * @brief Deletes node from SLList.
     * 
     * @param Moods - element you wanna delete
    */
    void deleteNode( Moods );

    /**
     * @brief Prints a complete list of Moods added, using printMood function.
    */
    void printSLList( void );

    /**
     * @brief Deletes whole SLList.
    */
    void deleteSLList( void );
};

void cleaning( void ); //function to clean input
void printMood( Moods );
int compareNode( Moods, Moods );
void moods_export( SLList * ); //save all data from list in the moods.txt file
void moods_import( SLList * ); //read the moods.txt file if it exists and add all the data to the singly linked list

#endif



