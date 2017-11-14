#ifndef MY_STACK_H
#define MY_STACK_H

#include "the_element_of_stack.h"

class My_stack
{
public:
    My_stack();
    ~My_stack();
    void push(The_element_of_stack* element);
    void push(string diff_line, int index_of, bool type, string *main_text);
    void push(string diff_line, int index_of, string replaced, string *main_text);
    void pop();
    The_element_of_stack* get_head();
    bool is_empty();
    int size();
    void clear_stack();
    void set_head(The_element_of_stack* element);
    void show();
    void download_from_file(string thetext, string *main_text);
    void upload_to_file(string thetext);


private:
    The_element_of_stack* head;

};

#endif // MY_STACK_H
