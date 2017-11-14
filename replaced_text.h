#ifndef REPLACED_TEXT_H
#define REPLACED_TEXT_H

#include "text_change.h"

class Replaced_text : public Text_change
{
public:
    Replaced_text();
    void undo();
    void redo();
    void set_removed_string(string thetext);
    string get_removed_string();
    void delete_sub_str(int index1, int index2);
    void insert_sub_str(int index, string thetext);

private:
    string removed_string;
};

#endif // REPLACED_TEXT_H
