#include "mood.h"


//Moods class functions
Moods::Moods(){
    for( int i = 0; i < 5; i++ ){
        words[i] = "";
    }
}

void Moods::get_currdate( void ){
    time_t now = time( 0 );
    tm *ltm = localtime( &now );
    string year = to_string( 1900 + ltm->tm_year );
    string month = to_string( 1 + ltm->tm_mon );
    string day = to_string( ltm->tm_mday );
    if( day.length() == 1 ) date.append( "0" );
    date.append( day + ".");
    if( month.length() == 1 ) date.append( "0" );
    date.append( month + "." + year );
}

void Moods::get_vibe( void ){
    string mood;
    cin >> mood;
    while( mood != "bad" && mood != "neutral" && mood != "good" ){
        cout << "Enter bad, neutral or good... ";
        cleaning();
        cin >> mood;
    }
    if( mood == "bad" ) vibe = BAD;
    else if( mood == "neutral" ) vibe = NEUTRAL;
    else vibe = GOOD; 
    cleaning();
}

void Moods::get_info( void ){ //function to create a vector (just for fun), then add words to the array words
    int counter = 0;
    vector<string> info;
    while( true ){
        string sentence;

        try{
            getline( cin, sentence ); //check if there are no semicolons in the user input!
        }
        catch( ... ){
            cout << "Maybe try to shorten this one? ^^" << endl;
            continue;
        }

        if( sentence == "." ) break;
        info.push_back( sentence );
        counter++;
        if( counter == 5 ) break;
    }

    int j = 0;
    for( const string& i : info ){
        words[j] = i;
        j++;
    }
}

void Moods::create_today( void ){
    get_currdate();
    cout << date << endl;
    cout << "Hi! How is your mood today? ";
    get_vibe();
    cout << "\nType up to 5 sentences to describe your mood (enter \".\" in new line to end):\n";
    get_info();
    Num++;
}


//Single Linked List functions
Node::Node( Moods *data ){
    this->today = data;
    this->next = NULL;
};

SLList::SLList(){
    this->head = NULL;
};

void SLList::insertNode( Moods *today ){
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

    while( compareNode( thatday, *( curr->today ) ) != 0 && curr != NULL ){
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
    cout << "\n***LIST OF YOUR MOODS :)***\n" << endl;
    Node *curr = head;
    while( curr != NULL ){
        printMood( *( curr->today ) );
        curr = curr->next;
    }
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


//other functions
void cleaning( void ){
    while( getchar() != '\n' ) continue;
}

void printMood( Moods data ){
    cout << "---" + data.date + "---" << endl;
    if( data.vibe == BAD ) printf( "   \033[31mbad\n" );
    else if( data.vibe == NEUTRAL ) printf( "   \033[33mneutral\n" ); 
    else printf( "   \033[32mgood\n" ); 

    cout << "\033[0m---why?\n";
    for ( int i = 0; data.words[i] != ""; i++ ) {
    cout << "  -> " + data.words[i] << endl;
    }

    cout << "\n";
}

int compareNode( Moods one, Moods two ){
    int c;
    if( ( c = one.date.compare( 6, 9, two.date, 6, 9 ) ) != 0 ) return c;
    if( ( c = one.date.compare( 3, 4, two.date, 3, 4 ) ) != 0 ) return c;
    return one.date.compare( 0, 1, two.date, 0, 1 );
}

void moods_export( SLList *list ){ //write all elements to file, divided with semicolons
    ofstream file;
    file.open( "moods_data.txt", ios::app ); //to save new data at the end of the file
    if( !file.is_open() ){
        cout << "An error occured." << endl;
        return;
    }

    Node *curr = list->head;
    while( curr->next != NULL ) curr = curr->next; //searching for the newest log
    file << "\n" << curr->today->date << ";";
    if( curr->today->vibe == BAD ) file << "BAD";
    else if( curr->today->vibe == NEUTRAL ) file << "NEUTRAL";
    else file << "GOOD";
    file << ";";
    for( int i = 0; curr->today->words[i] != ""; i++ ) file << curr->today->words[i] << ";";
    file.close();
}

void moods_import( SLList *list ){  //create new elements from before saved data and add them to the SLList
    ifstream file;
    file.open( "moods_data.txt", ios::in );
    if( !file ){ //it's just a fresh start for someone's moodS so no moods.txt file exists
        ofstream file;
        file.open( "moods_data.txt", ios::out );
        file << "moodSx_2023_annov723";
        return;
    }

    Node *curr = list->head;
    while( !file.eof() ){ //get all data for one object and create a SLList object
        
    }

    return;
}