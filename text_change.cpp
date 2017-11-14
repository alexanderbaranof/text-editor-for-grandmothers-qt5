#include "text_change.h"
#include "string.h"
#include <iostream>
#include <string>

using namespace std;

Text_change::Text_change()
{

    differences_line = "";
    index_of_differences_line = 0;
    type_of_change = true;
    type = false;

}

Text_change::Text_change(string &thetext) {
    //current_string = &thetext;
}

Text_change::Text_change(bool input_type_of_change, int input_index, string input_differences_line)
{
    if ( input_index <= (*current_string).size() ) {

        differences_line = input_differences_line;
        index_of_differences_line = input_index;
        type_of_change = input_type_of_change;

    } else {

        differences_line = input_differences_line;
        index_of_differences_line = 0;
        type_of_change = input_type_of_change;
    }

}

/*void Edittext::set_string(string &thetext) {
    cout << "I did it" << endl;
    current_string = &thetext;
}*/

void Text_change::set_string(string* thetext) {
    current_string = thetext;

}

void Text_change::show_current_string(){
    //cout << *current_string << endl;
}

void Text_change::insert_sub_str(int index, string thetext) {
    if (*current_string == "") {
        *current_string = thetext;
    } else if (index == 0) {
        *current_string = thetext + *current_string;
    } else if ( index == (*current_string).size() ) {
        *current_string = *current_string+thetext;
    } else {
        index_of_differences_line = index;
        differences_line = thetext;
        string tmp_string;
        tmp_string += (*current_string).substr(0,index);
        tmp_string += thetext;
        tmp_string += (*current_string).substr(index,(*current_string).size()-index);
        *current_string = tmp_string;
    }
}


void Text_change::delete_sub_str(int index1, int index2) {
    index_of_differences_line = index1;
    differences_line = (*current_string).substr(index1,index2-index1);
    string tmp_string = "";
    tmp_string += (*current_string).substr(0,index1);
    tmp_string += (*current_string).substr(index2,(*current_string).size()-index2);
    *current_string = tmp_string;
}

void Text_change::undo() {
    if (type_of_change) {
        delete_sub_str(index_of_differences_line, (index_of_differences_line + differences_line.size()));
    } else {
        insert_sub_str(index_of_differences_line, differences_line);
    }


}

void Text_change::redo(){
    if (!type_of_change) {
        delete_sub_str(index_of_differences_line, (index_of_differences_line + differences_line.size()));
    } else {
        insert_sub_str(index_of_differences_line, differences_line);
    }
}

void Text_change::set_type_of_change(bool type){
    type_of_change = type;
}

void Text_change::set_index_of_differences_line(int index){
      index_of_differences_line = index;
    }





void Text_change::set_differences_line(string thetext) {
        differences_line = thetext;
    }


string* Text_change::get_current_string(){
    return current_string;
}

string Text_change::get_differences_line(){
    return differences_line;
}

bool Text_change::get_type_of_change(){
    return type_of_change;
}

int Text_change::get_index_of_differences_line(){
    return index_of_differences_line;
}

void Text_change::set_insert_type(){
    this->type_of_change = 1;
}

void Text_change::set_delete_type(){
    this->type_of_change = 0;
}

bool Text_change::is_insert() {
    if (this->type_of_change) {
        return 1;
    } else {
        return 0;
    }
}

bool Text_change::is_delete(){
    if (!this->type_of_change) {
        return 1;
    } else {
        return 0;
    }
}

bool Text_change::get_type(){
    return type;
}

string Text_change::get_removed_string(){
    return "";
}
