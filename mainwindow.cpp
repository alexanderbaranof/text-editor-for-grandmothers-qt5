#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "QStandardItemModel"
#include "QStandardItem"
#include <math.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTextDocumentWriter>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    main_text = "";
    undo_stack = new My_stack;
    redo_stack = new My_stack;
    prev_main_text_size = 0;
    curr_main_text_size = 0;
    undo_flag = false;
    selected_flag = false;
    check_button();
    count_for_label();
    is_opened_file = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{

    redo_flag = true;
    The_element_of_stack *tmp_elem = new The_element_of_stack;
    tmp_elem->set_data( redo_stack->get_head()->get_data() ) ;
    if (!redo_stack->get_head()->get_data()->get_type()) {
        undo_stack->push(tmp_elem->get_data()->get_differences_line(),tmp_elem->get_data()->get_index_of_differences_line(),tmp_elem->get_data()->get_type_of_change(),tmp_elem->get_data()->get_current_string());
    } else {
        undo_stack->push(tmp_elem->get_data()->get_differences_line(),tmp_elem->get_data()->get_index_of_differences_line(),tmp_elem->get_data()->get_removed_string(),tmp_elem->get_data()->get_current_string());
    }
    redo_stack->pop();
    undo_stack->get_head()->get_data()->redo();
    undo_flag = true;
    ui->textEdit->setText(QString::fromStdString(main_text));
    undo_flag = false;
    redo_flag = false;
    delete tmp_elem;

}



void MainWindow::on_textEdit_textChanged()
{
    if (!selected_flag ) {
        if (!undo_flag) {
            QTextCursor cursor(ui->textEdit->textCursor());
            if ( !undo_stack->is_empty()  ) show_undo();
            if ( !redo_stack->is_empty()  ) show_redo();

            prev_main_text_size = curr_main_text_size;
            int diff_size = abs(ui->textEdit->toPlainText().count() - curr_main_text_size);
            curr_main_text_size = ui->textEdit->toPlainText().count();

            if (curr_main_text_size > prev_main_text_size){
                string tmp_string = ui->textEdit->toPlainText().toStdString().substr(cursor.position() - diff_size,diff_size);
                undo_stack->push(tmp_string, cursor.position() - diff_size, 1, &main_text);
                redo_stack->clear_stack();
                main_text = ui->textEdit->toPlainText().toStdString();

            } else if ( curr_main_text_size < prev_main_text_size ) {

                string tmp_string = main_text.substr(cursor.position(),diff_size);
                undo_stack->push(tmp_string, cursor.position(), 0, &main_text);
                redo_stack->clear_stack();
                main_text = ui->textEdit->toPlainText().toStdString();
            }

            curr_main_text_size = ui->textEdit->toPlainText().count();
            if ( !undo_stack->is_empty() ) show_undo();
            if ( !redo_stack->is_empty() ) show_redo();

        }
    } else {

        if (!redo_flag){
            main_text = ui->textEdit->toPlainText().toStdString();
            curr_main_text_size = ui->textEdit->toPlainText().count();
            QTextCursor cursor = ui->textEdit->textCursor();
            string tmp_str = main_text.substr(first_replace_position,cursor.position()-first_replace_position);
            undo_stack->push(tmp_str, first_replace_position, replaced_string, &main_text);
            redo_stack->clear_stack();
            selected_flag = false;
        }
        redo_flag = false;

    }

    show_undo();
    show_redo();
    curr_main_text_size = ui->textEdit->toPlainText().count();
    check_button();
    count_for_label();
}

void MainWindow::on_textEdit_selectionChanged()
{

    QTextCursor cursor = ui->textEdit->textCursor();
    if(cursor.hasSelection())
    {
        selected_flag = true;
        replaced_string = cursor.selectedText().toStdString();
        first_replace_position = cursor.selectionStart();
    }

}

void MainWindow::on_pushButton_3_clicked()
{

    redo_flag = true;
    The_element_of_stack *tmp_elem = new The_element_of_stack;
    tmp_elem->set_data( undo_stack->get_head()->get_data() ) ;
    if (!undo_stack->get_head()->get_data()->get_type()) {
        redo_stack->push(tmp_elem->get_data()->get_differences_line(),tmp_elem->get_data()->get_index_of_differences_line(),tmp_elem->get_data()->get_type_of_change(),tmp_elem->get_data()->get_current_string());
    } else {
        redo_stack->push(tmp_elem->get_data()->get_differences_line(),tmp_elem->get_data()->get_index_of_differences_line(),tmp_elem->get_data()->get_removed_string(),tmp_elem->get_data()->get_current_string());
    }
    undo_stack->pop();
    redo_stack->get_head()->get_data()->undo();
    undo_flag = true;
    ui->textEdit->setText(QString::fromStdString(main_text));
    undo_flag = false;
    redo_flag = false;
    delete tmp_elem;
}


void MainWindow::show_undo(){
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    horizontalHeader.append("Line difference");
    horizontalHeader.append("Index");
    horizontalHeader.append("Type");


    model->setHorizontalHeaderLabels(horizontalHeader);

    The_element_of_stack *tmp_elem = new The_element_of_stack;
    if ( undo_stack->get_head() != NULL  ){
        tmp_elem->set_data( undo_stack->get_head()->get_data() ) ;
        tmp_elem->set_next( undo_stack->get_head()->get_next() ) ;
    } else {
        tmp_elem = NULL;
    }
    int row = 0;


    while (tmp_elem!=NULL) {

        if (!tmp_elem->get_data()->get_type()) {
            item = new QStandardItem(QString( QString::fromStdString(tmp_elem->get_data()->get_differences_line()) ));
            model->setItem(row, 0, item);
        } else {
            item = new QStandardItem(QString( QString::fromStdString(tmp_elem->get_data()->get_removed_string() + "|" + tmp_elem->get_data()->get_differences_line()) ));
            model->setItem(row, 0, item);
        }

        item = new QStandardItem(QString( QString::number(tmp_elem->get_data()->get_index_of_differences_line() )) );
        model->setItem(row, 1, item);

        if (!tmp_elem->get_data()->get_type() ) {

            if (tmp_elem->get_data()->get_type_of_change() ){
                item = new QStandardItem(QString( "insert" ) );
            } else if ( !tmp_elem->get_data()->get_type_of_change() ){
                item = new QStandardItem(QString( "delete" ) );
            }
            model->setItem(row, 2, item);

        } else {
            item = new QStandardItem(QString( "replace" ) );
            model->setItem(row, 2, item);

        }

        row++;
        tmp_elem = tmp_elem->get_next();

    }

    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    delete tmp_elem;
}

void MainWindow::show_redo(){

    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    horizontalHeader.append("Line difference");
    horizontalHeader.append("Index");
    horizontalHeader.append("Type");

    model->setHorizontalHeaderLabels(horizontalHeader);

    The_element_of_stack *tmp_elem = new The_element_of_stack;

    if ( redo_stack->get_head() != NULL ) {
        tmp_elem->set_data( redo_stack->get_head()->get_data() ) ;
        tmp_elem->set_next( redo_stack->get_head()->get_next() ) ;
    } else {
        tmp_elem = NULL;
    }

    int row = 0;

    while (tmp_elem!=NULL) {

        if (!tmp_elem->get_data()->get_type()) {
            item = new QStandardItem(QString( QString::fromStdString(tmp_elem->get_data()->get_differences_line()) ));
            model->setItem(row, 0, item);
        } else {
            item = new QStandardItem(QString( QString::fromStdString(tmp_elem->get_data()->get_removed_string() + "|" + tmp_elem->get_data()->get_differences_line()  ) ));
            model->setItem(row, 0, item);
        }

        item = new QStandardItem(QString( QString::number(tmp_elem->get_data()->get_index_of_differences_line() )) );
        model->setItem(row, 1, item);

        if (!tmp_elem->get_data()->get_type() ) {

            if (tmp_elem->get_data()->get_type_of_change() ){
                item = new QStandardItem(QString( "insert" ) );
            } else if ( !tmp_elem->get_data()->get_type_of_change() ){
                item = new QStandardItem(QString( "delete" ) );
            }
            model->setItem(row, 2, item);

        } else {

            item = new QStandardItem(QString( "replace" ) );
            model->setItem(row, 2, item);

        }

        row++;

        tmp_elem = tmp_elem->get_next();

    }

    ui->tableView_2->setModel(model);
    ui->tableView_2->resizeRowsToContents();
    ui->tableView_2->resizeColumnsToContents();
    delete tmp_elem;
}


void MainWindow::check_button(){

    if ( undo_stack->is_empty() ) {
        ui->pushButton_3->setDisabled(true);
    } else {
        ui->pushButton_3->setDisabled(false);
    }

    if ( redo_stack->is_empty() ) {
        ui->pushButton_4->setDisabled(true);
    } else {
        ui->pushButton_4->setDisabled(false);
    }

}

void MainWindow::count_for_label(){

    ui->label_9->setText(QString::number(redo_stack->size()));
    ui->label_7->setText(QString::number(undo_stack->size()));
    ui->label_8->setText(QString::number(ui->textEdit->toPlainText().count()));
}




void MainWindow::on_pushButton_clicked()
{
    files = QFileDialog::getOpenFileName(0, "Please choose a file", "", "*.txt");
    QFile file(files);
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    } else {

    undo_stack->clear_stack();
    redo_stack->clear_stack();
    undo_stack->download_from_file(files.toStdString()+"_undo",&main_text);
    redo_stack->download_from_file(files.toStdString()+"_redo",&main_text);

    QTextStream in(&file);
    QString line;
    while(!in.atEnd()) {
        line += in.readLine();

    }

    file.close();

    undo_flag = true;
    ui->textEdit->setText(line);
    main_text = ui->textEdit->toPlainText().toStdString();
    undo_flag = false;
    is_opened_file = true;

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if ( is_opened_file ) {

        QTextDocumentWriter writer(files, "plaintext");
        writer.write(ui->textEdit->document());
        undo_stack->upload_to_file(files.toStdString()+"_undo");
        redo_stack->upload_to_file(files.toStdString()+"_redo");
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.exec();



    } else {

        QString str = QFileDialog::getSaveFileName();
        QTextDocumentWriter writer(str, "plaintext");
        writer.write(ui->textEdit->document());
        undo_stack->upload_to_file(str.toStdString()+"_undo");
        redo_stack->upload_to_file(str.toStdString()+"_redo");
    }
}
