#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>

using namespace std;

typedef enum { BAD = 12, NEUTRAL = 14, GOOD = 10 } MOOD_COLOR;
class Moods{
private:
    static int Num;
public:
    Moods(){
        date[10] = '\0';
    }
    char date[11]; //dd.mm.rrrr
    MOOD_COLOR vibe;
    //vector for 5 words' note

    //function to get date 
    //function to get vibe
};

int Moods::Num = 0;

void printMood( Moods );
class Node{
public:
    Moods today;
    Node *next;

    Node( Moods data ){
        this->today = data;
        this->next = NULL;
    };
};

int compareNode( Moods, Moods );

class SLList{
private:
    Node *head;

public:
    SLList(){
        this->head = NULL;
    };
    void insertNode( Moods );
    void deleteNode( Moods );
    void printSLList( void );
    void deleteSLList( void );
};

//read moods.txt file if it exists and add all the data to the singly linked list
//void uploader( void );

int main( void ){

    SLList list;
    Moods today, yesterday;
    today.vibe = BAD;
    for( int i = 0; i < 10; i++ ){
        today.date[i] = '1';
    }
    yesterday.vibe = GOOD;
    for( int i = 0; i < 10; i++ ){
        yesterday.date[i] = '1';
    }
    list.insertNode( yesterday );
    list.insertNode( today );
    list.printSLList();


    return 0;
}



void SLList::insertNode( Moods today ){
    Node *newN = new Node( today );

    if( head == NULL ){
        head = newN;
        return;
    }

    Node *curr = head;
    while( curr->next != NULL ) curr = curr->next;

    curr->next = newN;
}

void SLList::deleteNode( Moods thatday ){
    Node *curr = head;
    Node *prev = NULL;

    if( head == NULL ){ //list is empty
        return;
    }

    while( compareNode( thatday, curr->today ) != 0 && curr != NULL ){
        prev = curr;
        curr = curr->next;
    }

    if( curr == NULL ){ //no match
        return;
    }

    if( prev == NULL ){
        head = head->next;
        delete curr;
        return;
    }

    prev->next = curr->next;
    delete curr;
}

void SLList::printSLList( void ){
    Node *curr = head;
    while( curr != NULL ){
        printMood( curr->today );
        curr = curr->next;
    }
}

int compareNode( Moods one, Moods two ){
    int c;
    if( ( c = strcmp( one.date + 6, two.date + 6 ) ) != 0 ) return c;
    if( ( c = strncmp( one.date + 3, two.date + 3, 2 ) ) != 0 ) return c;
    if( ( c = strncmp( one.date, two.date, 2 ) ) != 0 ) return c;
    return 0;
}

void printMood( Moods data ){
    cout << "***" << data.date << "***" << endl;
    if( data.vibe == BAD ) printf( "\033[31mbad\n\n" );
    else if( data.vibe == NEUTRAL ) printf( "\033[33mneutral\n\n" ); 
    else printf( "\033[32mgood\n\n" ); 

    cout << "\033[0mwhy?" << endl;
    //vector

}

void SLList::deleteSLList( void ){
    Node *curr = head, *prev = NULL;

    while( curr != NULL ){
        prev = curr;
        curr = curr->next;
        delete prev;
    }
    delete curr;
    head = NULL;
}