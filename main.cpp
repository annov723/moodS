#include "mood.h"

int Moods::Num = 0; //to have number of all objects, useful in creating statistic

int main( void ){

    SLList list;
    moods_import( &list ); //upload data if exists
    
    bool new_mood = check_today( &list );
    if( new_mood ){ //first check if the log from today hasn't been created? (the same date as an element from SLList)
        Moods *today = new Moods();
        today->create_today();
        list.insertNode( today );
    }

    Moods to_del;

    //app's menu - to show the calendar of your moods ( list.printSLList() ), delete a chosen log, show statistic
    while( true ){
        cout << FLOWERS << "\n                         ***moodS menu***\n" << endl;
        cout << "(1) moodS list\n" << "(2) moodS chart\n" << "(3) delete a moodS\n" << "(4) quit\n" << endl;
        cout << "Choose an option: ";
        switch( get_char() ){
            case '1':
                list.printSLList();
                break;
            case '2':
                moods_chart( &list );
                break;
            case '3':
                list.printSLList();
                cout << "Type date of a log you wanna remove, remember that you cannot recover the removed data: ";
                
                to_del.date = get_date();
                list.deleteNode_bydate( to_del );
                break;
            case '4':
                cout << "\nHave a nice day!" << endl;
                moods_export( &list );

                moods_delete( &list, new_mood ); //have to delete all allocated moods first!
                list.deleteSLList();
                return 0;
            default:
                cout << "\n[invalid option]";

        }

    }
    
    return 1;
}
