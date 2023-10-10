#include "mood.h"

int Moods::Num = 0; //to have number of all objects, useful in creating statistic

int main( void ){

    SLList list;
    //moods_import( &list ); //upload data if exists
    
    Moods today;
    today.create_today();
    
    list.insertNode( &today );

    //menu(); //app's menu - showing the calendar of your moods ( list.printSLList() ) and statistic
    list.printSLList();

    moods_export( &list );

    list.deleteSLList();

    return 0;
}