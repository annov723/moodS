#include "mood.h"

int Moods::Num = 0; //to have number of all objects, useful in creating statistic

int main( void ){

    SLList list;
    moods_import( &list ); //upload data if exists
    
    bool new_mood = check_today( &list );
    if( new_mood ){ //first check if the log from today hasn't been created? (the same date as an element from SLList)
        Moods today;
        today.create_today();
        list.insertNode( &today );
    }

    //app's menu - showing the calendar of your moods ( list.printSLList() ), possible to delete a log when giving a date but it's impossible to be recovered and statistic
    while( true ){
        cout << FLOWERS << "\n                            ***MENU***\n" << endl;
        cout << "(1)moodS list\n" << "(2)moodS chart\n" << "(3)quit\n" << endl;
        cout << "Choose an option: ";
        switch( get_char() ){
            case '1':
                list.printSLList();
                break;
            case '2':
                //moods_chart( &list );
                break;
            case '3':
                cout << "Have a nice day!" << endl;
                if( new_mood ) moods_export( &list );

                moods_delete( &list, new_mood ); //have to delete all allocated moods first!
                list.deleteSLList();
                return 0;
            default:
                cout << "[invalid option]" << endl;

        }

    }
        
    return 1;
}
