#include "mood.h"

int Moods::Num = 0; //to have number of all objects, useful in creating statistic

int main( void ){

    SLList list;
    moods_import( &list ); //upload data if exists
    
    //first check if the log from today hasn't been created? (the same date as the same element from SLList)
    Moods today;
    today.create_today();
    
    list.insertNode( &today );

    //menu(); //app's menu - showing the calendar of your moods ( list.printSLList() ), possible to delete a log when giving a date but it's impossible to be recovered and statistic
    list.printSLList();

    moods_export( &list );

    list.deleteSLList();

    return 0;
}
