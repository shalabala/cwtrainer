#include "main_window.h"
#include "../configuration/configuration.h"
#include "../configuration/configuration_types.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
namespace conf = configuration;
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
        connect(this, &MainWindow::singleKeyReleased, presenter.get(), &presenter::Presenter::slotSingleKeyReleased);
        connect(this, &MainWindow::dotKeyReleased, presenter.get(), &presenter::Presenter::slotDotKeyReleased);
        connect(this, &MainWindow::dashKeyReleased, presenter.get(), &presenter::Presenter::slotDashKeyReleased);
    }

    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        int key = event->key();
        if (key == configuration->get<int, conf::singleKeyScanCode>())
        {
            emit singleKeyPressed();
        }
        else if (key == configuration->get<int, conf::dotKeyScanCode>())
        {
            emit dotKeyPressed();
        }
        else if (key == configuration->get<int, conf::dashKeyScanCode>())
        {
            emit dashKeyPressed();
        }
    }

    void MainWindow::keyReleaseEvent(QKeyEvent *event)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        int key = event->key();
        if (key == configuration->get<int,conf::singleKeyScanCode>())
        {
            emit singleKeyReleased();
        }
        else if (key == configuration->get<int,conf::dotKeyScanCode>())
        {
            emit dotKeyReleased();
        }
        else if (key == configuration->get<int,conf::dashKeyScanCode>())
        {
            emit dashKeyReleased();
        }
    }
}