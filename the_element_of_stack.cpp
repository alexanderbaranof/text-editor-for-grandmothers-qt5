#include "the_element_of_stack.h"
#include <iostream>

using namespace std;

The_element_of_stack::The_element_of_stack()
{
    this->data = NULL;
    this->next = NULL;
}

void The_element_of_stack::set_next(The_element_of_stack *backup){
    if (this!=NULL) this->next = backup;
}

void The_element_of_stack::set_data(Text_change *backup){
    if (this!=NULL) this->data = backup;
}

The_element_of_stack* The_element_of_stack::get_next(){
    return next;
}

Text_change* The_element_of_stack::get_data(){
    return data;
}

