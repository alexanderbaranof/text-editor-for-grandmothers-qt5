#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "my_stack.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void move_to_redo(The_element_of_stack *last_element);
    ~MainWindow();

private slots:
    void on_pushButton_4_clicked();


    void on_textEdit_textChanged();

    void on_textEdit_selectionChanged();



    void on_pushButton_3_clicked();


    void show_undo();

    void show_redo();
    void check_button();
    void count_for_label();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    string main_text;
    My_stack* undo_stack;
    My_stack* redo_stack;
    int prev_main_text_size;
    int curr_main_text_size;
    bool undo_flag;
    bool selected_flag;
    bool redo_flag;
    int first_replace_position;
    int last_replace_position;
    string replaced_string;
    bool is_opened_file;
    QString files;
};

#endif // MAINWINDOW_H
