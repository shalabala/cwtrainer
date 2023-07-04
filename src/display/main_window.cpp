#include "main_window.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

namespace display
{
    MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
    {
        setMinimumSize(100, 50);
        setWindowTitle("CWTrainer");
        mainLayout = new QGridLayout(this);
        inputLine = new QLineEdit(this);
        displayArea = new QTextEdit(this);
        displayArea->setReadOnly(true);
        inputLine->setReadOnly(true);
        displayArea->setText("CQD CQD");
        mainLayout->addWidget(displayArea,0,0);
        mainLayout->addWidget(inputLine,1,0);
        setLayout(mainLayout);
    }
}