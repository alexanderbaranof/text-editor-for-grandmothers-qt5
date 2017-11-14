#include "replaced_text.h"

Replaced_text::Replaced_text()
{
    type = true;
}


void Replaced_text::set_removed_string(string thetext){
    removed_string = thetext;
}

void Replaced_text::undo() {

  /*  delete_sub_str(index_of_differences_line, (index_of_differences_line + removed_string.size()));

    insert_sub_str(index_of_differences_line, differences_line); */


     delete_sub_str(index_of_differences_line, (index_of_differences_line + strlen(differences_line.c_str())  ));

     insert_sub_str(index_of_differences_line, removed_string);


}

void Replaced_text::redo() {

    delete_sub_str(index_of_differences_line, (index_of_differences_line + strlen(removed_string.c_str())))   ;

    insert_sub_str(index_of_differences_line, differences_line);

}

string Replaced_text::get_removed_string(){
    return removed_string;
}

void Replaced_text::delete_sub_str(int index1, int index2) {
    index_of_differences_line = index1;
    string tmp_string = "";
    tmp_string += (*current_string).substr(0,index1);
    tmp_string += (*current_string).substr(index2,(*current_string).size()-index2);
    *current_string = tmp_string;
}

void Replaced_text::insert_sub_str(int index, string thetext){

    if (*current_string == "") {
        *current_string = thetext;
    } else if (index == 0) {
        *current_string = thetext + *current_string;
    } else if ( index == (*current_string).size() ) {
        *current_string = *current_string+thetext;
    } else {
        index_of_differences_line = index;
        //differences_line = thetext;
        string tmp_string;
        tmp_string += (*current_string).substr(0,index);
        tmp_string += thetext;
        tmp_string += (*current_string).substr(index,(*current_string).size()-index);
        *current_string = tmp_string;
    }

}
