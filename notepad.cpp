#include "notepad.h"
#include "ui_notepad.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","File not opened.");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void Notepad::on_actionNew_triggered()
{
    current_file = "";
    ui->textEdit->setText("");
}

void Notepad::on_actionSave_triggered()
{
    QFile file(current_file);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","No file opened. Use Save As.");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void Notepad::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Save As");
    QFile file(file_name);
    current_file = file_name;
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"..","File not opened.");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}
