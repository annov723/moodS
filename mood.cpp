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

void Moods::get_info( void ){
    int counter = 0;
    vector<string> info;
    while( true ){
        string sentence;

        try{
            getline( cin, sentence );
        }
        catch( ... ){
            cout << "Maybe try to shorten this one? ^^" << endl;
            continue;
        }
        int k = 0;
        for( char& c : sentence ){
            if( c == ';' ){
                cout << "Incorrect sign found \";\", input your sentence once again please <3" << endl;
                k = 1;
                break;
            }
        }
        if( k == 1 ) continue;

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

    if( head == NULL ) return; //list is empty

    int k = 1;
    while( ( k = compareNode( thatday, *( curr->today ) ) ) != 0 && curr != NULL ){
        if( k < 0 ){
            cout << "\n[no match]\n" << endl;
            return; //no match
        }
        prev = curr;
        curr = curr->next;
    }

    if( curr == NULL ){
        cout << "\n[no match]\n" << endl;
        return; //no match
    }

    if( prev == NULL ){
        head = head->next;
        delete curr->today;
        delete curr;
        cout << "\n[deleted successfully]\n" << endl;
        return;
    }

    prev->next = curr->next;
    delete curr;
    cout << "\n[deleted successfully]\n" << endl;
}

void SLList::deleteNode_bydate( Moods to_del ){
    Node *curr = head;
    Node *prev = NULL;

    if( head == NULL ) return; //list is empty

    int k = 1;
    while( curr != NULL ){
        k = ( to_del.date ).compare( curr->today->date );
        if( k == 0 ) break;
        if( k < 0 ){
            cout << "\n[no match]\n" << endl;
            return; //no match
        }
        prev = curr;
        curr = curr->next;
    }

    if( curr == NULL ){
        cout << "\n[no match]\n" << endl;
        return; //no match
    }

    if( prev == NULL ){
        head = head->next;
        delete curr->today;
        delete curr;
        cout << "\n[" << to_del.date << " deleted successfully]\n" << endl;
        return;
    }

    prev->next = curr->next;
    delete curr;
    cout << "\n[" << to_del.date << " deleted successfully]\n" << endl;
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
    for ( int i = 0; i < 5 && data.words[i] != ""; i++ ) {
        cout << "  -> " << data.words[i] << endl;
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
    file.open( "moods_data.txt", ios::trunc );
    if( !file.is_open() ){
        cout << "An error occured." << endl;
        return;
    }

    file << "moodSx_2023_annov723_37482009";
    
    if( list->head == NULL ) return;
    Node *curr = list->head;
    while( curr != NULL ){
        file << "\n" << curr->today->date << ";";

        if( curr->today->vibe == BAD ) file << BAD;
        else if( curr->today->vibe == NEUTRAL ) file << NEUTRAL;
        else file << GOOD;

        file << ";";
        for( int i = 0; curr->today->words[i] != ""; i++ ) file << curr->today->words[i] << ";";

        curr = curr->next;
    }

    file.close();
}

void moods_import( SLList *list ){  //create new elements from before saved data and add them to the SLList
    ifstream file;
    file.open( "moods_data.txt", ios::in );
    if( !file ){ //it's just a fresh start for someone's moodS so no moods.txt file exists
        ofstream file;
        file.open( "moods_data.txt", ios::out );
        file << "moodSx_2023_annov723_37482009";
        return;
    }

    string line;
    //check if moods_data.txt is really a good file
    getline( file, line );
    if( line != "moodSx_2023_annov723_37482009" ){
        cout << "moods_data.txt is invalid! Delete this file from the application directory or upload a valid mood_data.txt file." << endl;
        exit( EXIT_FAILURE );
    }

    while( !file.eof() ){ //get all data for one object and create a SLList object
        Moods *day = new Moods();
        
        getline( file, line );
        day->date = line.substr( 0, 10 );
        if( line[2] != '.' || line[5] != '.' ){
            cout << "moods_data.txt is invalid! Delete this file from the application directory or upload a valid mood_data.txt file." << endl;
            exit( EXIT_FAILURE );
        }

        int x = stoi( line.substr( 11, 1 ) );
        switch( x ){
            case 0:
                day->vibe = BAD;
                break;
            case 1:
                day->vibe = NEUTRAL;
                break;
            case 2:
                day->vibe = GOOD;
                break;
            default:
                cout << "moods_data.txt is invalid! Delete this file from the application directory or upload a valid mood_data.txt file." << endl;
                exit( EXIT_FAILURE );
        }

        if( line.length() < 13 ){ //if user hasn't added any description to their log
            list->insertNode( day );
            continue;
        }

        int where = 13;
        for( int i = 0; i < 5; i++ ){
            if( line.find( ';', where ) == string::npos ) break;

            int f = line.find( ';', where );
            day->words[i] = line.substr( where, f - where );
            where = f + 1;
        }

        list->insertNode( day );  
    }
}

bool check_today( SLList *list ){
    Node *curr = list->head;
    if( curr == NULL ) return true;
    while( curr->next != NULL ) curr = curr->next;
    
    string date1 = curr->today->date;
    Moods date2;
    date2.get_currdate();

    if( date1 != date2.date ) return true; //there is no log from today

    return false;
}

void moods_delete( SLList *list, bool new_mood ){
    if( list->head == NULL ) return;
    Node *curr = list->head;
    Moods *elem = NULL;
    while( curr != NULL ){
        delete curr->today;
        curr = curr->next;
    }
}

void moods_chart( SLList *list ){
    int good = 0, neutral = 0, bad = 0;
    Node *curr = list->head;
    if( list->head == NULL ) return;
    while( curr != NULL ){
        switch( curr->today->vibe ){
            case 0:
                bad++;
                break;
            case 1:
                neutral++;
                break;
            case 2:
                good++;
                break;
            default:
                cout << "An error occured." << endl;
                return;
        }
        curr = curr->next;
    }

    int sum = bad + neutral + good;

    cout << "\nWhat kind of a chart would you like to see?" << endl;
    cout << "(1) time-mood chart\n" << "(2) mood-amount chart" << endl;
    cout << "Choose an option: ";
    switch( get_char() ){
        case '1':
            cout << CHART1 << endl;
            curr = list->head;
            break;
        case '2':
            cout << CHART2 << endl;
            double b1 = bad / sum, n1 = neutral / sum, g1 = good / sum;

            break;
    }    
}

char get_char(){
    string input;
    cin >> input;
    cleaning();
    while( input.length() != 1 ){
        cout << "\n[invalid input]" << endl;
        cout << "Type one digit: ";
        cin >> input;
    }

    return input[0]; 
}

string get_date(){
    string input;
    bool check;
    while( true ){
        cin >> input;
        cleaning();
        check = true;
        if( input.length() != 10 || input[2] != '.' || input[5] != '.' ) check = false;
        if( check == true ){
            for( int i = 0; i < input.length(); i++ ){
                if( i == 2 || i == 5 ) continue;
                if( !isdigit( input[i] ) ){
                    check = false;
                    break;
                }
            }
        }
        if( check == true ) break;

        cout << "\n[invalid input]" << endl;
        cout << "Type a date [dd.mm.yyyy]: ";
    }

    return input; 
}