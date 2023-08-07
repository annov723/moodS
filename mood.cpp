#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

class Node{
public:
    Moods today;
    Node *next;

    Node( Moods data ){
        this->today = data;
        this->next = NULL;
    };

    int compareNode( Moods, Moods );
};

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
};

typedef enum { RED, YELLOW, GREEN } MOOD_COLOR;

class Moods{
private:
    static int Num;
public:
    Moods(){
        //read moods.txt file if it exists and add all the data to the singly linked list
    }
    char date[11]; //dd.mm.rrrr
    MOOD_COLOR color;
};

int Moods::Num = 0;

int main( void ){

    SLList list;

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

    while( Node::compareNode( thatday, curr->today ) != 0 && curr != NULL ){
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
    while( curr != NULL ) printMoods
}

int Node::compareNode( Moods one, Moods two ){
    int c;
    if( ( c = strcmp( one.date + 6, two.date + 6 ) ) != 0 ) return c;
    if( ( c = strncmp( one.date + 3, two.date + 3, 2 ) ) != 0 ) return c;
    if( ( c = strncmp( one.date, two.date, 2 ) ) != 0 ) return c;
    return 0;
}