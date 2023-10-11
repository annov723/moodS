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

/**
 * @brief Class with all the information about the user's mental state.
*/
class Moods{
public:
    static int Num;

    string date; //dd.mm.rrrr
    MOOD_COLOR vibe;
    string words[5]; //tab for 5 words' note to decribe the reasons of user's mental state that day

    /**
     * @brief Constructor that initializes words array.
    */
    Moods();

    /**
     * @brief Gets today's date.
    */
    void get_currdate( void );

    /**
     * @brief Allows user to input his mental state (good, neutral, bad).
    */
    void get_vibe( void );

    /**
     * @brief Allows user to input reasons of their mental state.
    */
    void get_info( void );

    /**
     * @brief Connect all the methods above to fill a new Moods object.
    */
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

/**
 * @brief Cleaning a console input.
*/
void cleaning( void ); //function to clean input

/**
 * @brief Prints information from Moods class object.
*/
void printMood( Moods );

/**
 * @brief Compare two Moods objects.
 * Returns 0 if objects are the same, >0 if the first one is younger and <0 if the first one is older than the second object.
*/
int compareNode( Moods, Moods );

/**
 * @brief Export all SLList data to a .txt file.
 * 
 * @param SLList * - pointer to the head element of SSlist
*/
void moods_export( SLList * );

/**
 * @brief Import all data from moods_data.txt fril to the SLList.
 * If the file doesn't exists, it creates a new moods_data.txt file.
 * 
 * @param SLList * - pointer to the head element of SSlist
*/
void moods_import( SLList * );

#endif



