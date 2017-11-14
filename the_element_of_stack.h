#ifndef THECOLLECTION_H
#define THECOLLECTION_H

#include "text_change.h"
#include "replaced_text.h"

using namespace std;

class The_element_of_stack
{
public:
    The_element_of_stack();
    void set_string(string &thetext);
    void set_next(The_element_of_stack *backup);
    void set_data(Text_change *backup);
    The_element_of_stack* get_next();
    Text_change* get_data();


private:
    Text_change *data;
    The_element_of_stack *next;
};

#endif // THECOLLECTION_H
