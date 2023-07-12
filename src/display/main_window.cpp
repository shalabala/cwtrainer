#include "main_window.h"
#include "../configuration/configuration.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>

namespace display
{
    MainWindow::MainWindow(std::shared_ptr<presenter::Presenter> presenter,
                           std::shared_ptr<configuration::Configuration> configuration, QWidget *parent) : QWidget(parent),
                                                                                                           presenter(presenter),
                                                                                                           configuration(configuration)
    {
        setMinimumSize(100, 50);
        setWindowTitle("CWTrainer");
        mainLayout = new QGridLayout(this);
        inputLine = new QLineEdit(this);
        displayArea = new QTextEdit(this);
        displayArea->setReadOnly(true);
        inputLine->setReadOnly(true);
        displayArea->setText("CQD CQD");
        mainLayout->addWidget(displayArea, 0, 0);
        mainLayout->addWidget(inputLine, 1, 0);
        setLayout(mainLayout);
        connect(this, &MainWindow::singleKeyPressed, presenter.get(), &presenter::Presenter::slotSingleKeyPressed);
        connect(this, &MainWindow::dotKeyPressed, presenter.get(), &presenter::Presenter::slotDotKeyPressed);
        connect(this, &MainWindow::dashKeyPressed, presenter.get(), &presenter::Presenter::slotDashKeyPressed);
        connect(this, &MainWindow::keyReleased, presenter.get(), &presenter::Presenter::slotKeyReleased);
    }

    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        int key=event->key();
        if (key == configuration->getSingleKeyScanCode())
        {
            emit singleKeyPressed();
        }
        else if (key == configuration->getDotKeyScanCode())
        {
            emit dotKeyPressed();
        }
        else if (key == configuration->getDashKeyScanCode())
        {
            emit dashKeyPressed();
        }
    }

    void MainWindow::keyReleaseEvent(QKeyEvent *event)
    {
        emit keyReleased();
    }
}