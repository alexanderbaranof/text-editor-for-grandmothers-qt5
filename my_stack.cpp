#include "my_stack.h"
#include <iostream>
#include <fstream>

using namespace std;

My_stack::My_stack()
{
    head = NULL;
}



The_element_of_stack* My_stack::get_head(){
    return head;
}

void My_stack::push(The_element_of_stack* element){

    element->set_next(head);
    head = element;

}

void My_stack::push(string diff_line, int index_of, bool type, string *main_text){

    Text_change *tmp_change = new Text_change;
    tmp_change->set_differences_line(diff_line);
    tmp_change->set_index_of_differences_line( index_of );
    tmp_change->set_type_of_change(type);
    tmp_change->set_string(&(*main_text));
    The_element_of_stack* tmp_element_of_stack = new The_element_of_stack;
    tmp_element_of_stack->set_data(tmp_change);
    push(tmp_element_of_stack);

}

void My_stack::push(string diff_line, int index_of, string replaced, string *main_text){

    Replaced_text* tmp_change = new Replaced_text;
    tmp_change->set_differences_line( diff_line );
    tmp_change->set_removed_string( replaced );
    tmp_change->set_index_of_differences_line( index_of );
    tmp_change->set_string(&(*main_text));
    The_element_of_stack* tmp_element_of_stack = new The_element_of_stack;
    tmp_element_of_stack->set_data(tmp_change);
    push(tmp_element_of_stack);

}

void My_stack::pop(){

    head = head->get_next();
}

void My_stack::clear_stack(){

    head=NULL;
}

void My_stack::set_head(The_element_of_stack *element){

    head = element;
}

void My_stack::show(){
    The_element_of_stack* tmp = head;
    while(tmp!=NULL){
        cout << tmp->get_data()->get_differences_line() << endl;
        cout << tmp->get_data()->get_index_of_differences_line() << endl;
        cout << tmp->get_data()->get_type_of_change() << endl;
        tmp = (tmp->get_next());
    }

}

bool My_stack::is_empty(){

    if (head!=NULL){
        return false;
    } else {
        return true;
    }
}

int My_stack::size(){

    int size = 0;
    The_element_of_stack* tmp = head;
    while(tmp!=NULL){
        size++;
        tmp = (tmp->get_next());
    }
    return size;
}

My_stack::~My_stack()
{
    The_element_of_stack* tmp;
    while(this->get_head()!=NULL){
        tmp = this->get_head()->get_next();
        delete this->get_head();
        head = tmp;
    }
    delete tmp;
}

void My_stack::download_from_file(string file_name, string *main_text){

        int inde_of, type, type_of_change;
        string dif_line;
        ifstream fin(file_name);
        string s,removed_str;
        int i = 1;
        while(getline(fin, s)){
            if ( i % 4 == 1 ){
                type = atoi(s.c_str());

            }

            if ( i % 4 == 2 ){
                dif_line = s;

            }

            if ( i % 4 == 3 ){
                inde_of = atoi(s.c_str());

            }

            if (i % 4 == 0) {

                if (!type) {
                    type_of_change = atoi(s.c_str());
                    this->push(dif_line,inde_of,type_of_change,&(*main_text));
                } else{
                    removed_str = s;
                    this->push(dif_line,inde_of,removed_str,&(*main_text));
                }

            }

            i++;
        }

        fin.close();
}

void My_stack::upload_to_file(string file_name){

    My_stack* tmp_stack = new My_stack;

    The_element_of_stack* tmp_element = new The_element_of_stack;
    tmp_element = this->get_head();

    while(tmp_element!=NULL){
        if ( !(tmp_element->get_data()->get_type()) ) {
            tmp_stack->push(tmp_element->get_data()->get_differences_line(),tmp_element->get_data()->get_index_of_differences_line(),tmp_element->get_data()->get_type_of_change(),tmp_element->get_data()->get_current_string());
        }
        else {
            tmp_stack->push(tmp_element->get_data()->get_differences_line(),tmp_element->get_data()->get_index_of_differences_line(),tmp_element->get_data()->get_removed_string(),tmp_element->get_data()->get_current_string());
        }
        tmp_element = tmp_element->get_next();
    }


    tmp_element = tmp_stack->get_head();
    ofstream fout(file_name, ios_base::trunc);
    while(tmp_element!=NULL){
        fout << tmp_element->get_data()->get_type() << endl;
        fout << tmp_element->get_data()->get_differences_line() << endl;
        fout << tmp_element->get_data()->get_index_of_differences_line() << endl;
        if ( !tmp_element->get_data()->get_type()  ) {
            fout << tmp_element->get_data()->get_type_of_change() << endl;
        } else {
             fout << tmp_element->get_data()->get_removed_string() << endl;
        }
        tmp_element = tmp_element->get_next();
    }

    fout.close();
}
