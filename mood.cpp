#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <ctime>

using namespace std;

typedef enum { BAD = 12, NEUTRAL = 14, GOOD = 10 } MOOD_COLOR;

void cleaning( void ); //function to clear input

class Moods{
private:
    static int Num;
public:
    Moods(){
        //constructor, unnecessary for now, update - now it's necessary xD
        get_currdate();
    }
    string date; //dd.mm.rrrr
    MOOD_COLOR vibe;
    //vector for 5 words' note

    void get_currdate( void ){
        time_t now = time( 0 );
        tm *ltm = localtime( &now );
        string year = to_string( 1900 + ltm->tm_year );
        string month = to_string( 1 + ltm->tm_mon );
        string day = to_string( ltm->tm_mday );
        if( day.length() == 1 ) date.append( "0" );
        date.append( day );
        date.append( "." );
        if( month.length() == 1 ) date.append( "0" );
        date.append( month );
        date.append( "." );
        date.append( year );
    }

    void get_vibe( void ){
        string mood;
        cin >> mood;
        while( mood != "bad" && mood != "so so" && mood != "good" ){
            cout << "Enter bad, so so or good..." << endl;
            cleaning();
            cin >> mood;
            if( mood == "bad" ) vibe = BAD;
            else if( mood == "so so" ) vibe = NEUTRAL;
            else vibe = GOOD; 
        }
    }
    
    //function to create vector
};

int Moods::Num = 0;

class Node{
public:
    Moods today;
    Node *next;

    Node( Moods data ){
        this->today = data;
        this->next = NULL;
    };
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
    void deleteSLList( void );
};

void printMood( Moods );
int compareNode( Moods, Moods );
//void uploader( void ); //read moods.txt file if it exists and add all the data to the singly linked list

int main( void ){

    SLList list;
    
    //upload data if exists
    
    Moods today;
    cout << today.date << endl;
    cout << "Hi! How is your mood today? ";
    today.get_vibe();
    cout << "\nType up to 5 words to describe your day:\n";

    list.insertNode( today );
    
    list.printSLList();
    

    list.deleteSLList();

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

void cleaning( void ){
    while( getchar() != '\n' ) continue;
}

int compareNode( Moods one, Moods two ){
    int c;
    if( ( c = one.date.compare( 6, 9, two.date, 6, 9 ) ) != 0 ) return c;
    if( ( c = one.date.compare( 3, 4, two.date, 3, 4 ) ) != 0 ) return c;
    return one.date.compare( 0, 1, two.date, 0, 1 );
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