#ifndef EDITTEXT_H
#define EDITTEXT_H
#include "string.h"
#include <iostream>
#include <string>

using namespace std;

class Text_change
{
public:
    Text_change();
    Text_change(bool input_type_of_change, int input_index, string input_differences_line);
    Text_change(string &thetext);
    //void set_string(string &thetext);
    void set_string(string* thetext);
    void show_current_string();
    void set_type_of_change(bool type);
    void set_index_of_differences_line(int index);
    void set_differences_line(string thetext);
    virtual void undo();
    virtual void redo();
    virtual string get_removed_string();
    void set_insert_type();
    void set_delete_type();
    string* get_current_string();
    bool get_type_of_change();
    string get_differences_line();
    int get_index_of_differences_line();
    bool is_insert();
    bool is_delete();
    bool get_type();

protected:
    string* current_string;
    string  differences_line;
    int index_of_differences_line;
    virtual void insert_sub_str(int index, string thetext);
    virtual void delete_sub_str(int index1, int index2);
    bool type;


private:
    bool type_of_change;





};

#endif // EDITTEXT_H
