#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <qmessagebox.h>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <qtextedit.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit); // Removes the sidegaps from the text editor
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path=""; // Clear the path
    ui->textEdit->setText(""); // Make the editor blank
}

void MainWindow::on_actionOpen_triggered()
{
 QString file_name = QFileDialog::getOpenFileName(this,"Open a file");
 QFile file (file_name);
 file_path=file_name;

  if(!file.open(QFile::ReadOnly | QFile::Text)){
    QMessageBox::critical(this,"Error Opening File","File Cannot be Opened!");
    return;
  }
  else{
    //Read the file
    QTextStream inputData(&file);
    QString fileText = inputData.readAll();
    ui->textEdit->setText(fileText);
    file.close();
  }
}

void MainWindow::on_actionSave_triggered()
{
     QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
      //Simply return if the user cancels or does something unexpected!
      return;
    }
    else{
      //Read the file
      QTextStream writeData(&file);
      QString fileText = ui->textEdit->toPlainText();
      writeData << fileText;
      file.flush();
      file.close();
    }
}

void MainWindow::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open a file");
    QFile file (file_name);
    file_path = file_name;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
       //Simply return if the user cancels or does something unexpected!
        return;
     }
     else{
       //Read the file
       QTextStream writeData(&file);
       QString fileText = ui->textEdit->toPlainText();
       writeData << fileText;
       file.flush();
       file.close();
     }
}

void MainWindow::on_actionExit_2_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionAbout_QtTxtEdit_triggered()
{
    QMessageBox::about(this,"About QtTextEdit"," Copyright Gajesh Bhat 2017");
}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,"About Qt Creator.");
}

void MainWindow::on_actionItalic_triggered()
{
    QTextCharFormat format;
    format.setFontItalic(true);
    ui->textEdit->textCursor().mergeCharFormat(format);

}

void MainWindow::on_actionBold_triggered()
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Bold);
    ui->textEdit->textCursor().mergeCharFormat(format);
}

void MainWindow::on_actionUnderline_triggered()
{
    QTextCharFormat format;
    format.setFontUnderline(true);
    ui->textEdit->textCursor().mergeCharFormat(format);
}


void MainWindow::on_actionLeft_Align_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

void MainWindow::on_actionRight_Align_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_actionCenter_Align_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

void MainWindow::on_actionNormal_Default_triggered()
{
    QTextCharFormat format;
    format.setFontWeight(QFont::Normal);
    ui->textEdit->textCursor().mergeCharFormat(format);
}
