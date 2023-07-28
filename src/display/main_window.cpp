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
                           std::shared_ptr<configuration::Configuration> configuration) : MainWindow(presenter, configuration, nullptr)
    {
    }

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
        displayArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        inputLine->setReadOnly(true);
        QFont font("mono", 15);
        inputLine->setFont(font);
        displayArea->setFont(font);
        mainLayout->addWidget(displayArea, 0, 0);
        mainLayout->addWidget(inputLine, 1, 0);
        setLayout(mainLayout);
        connect(this, &MainWindow::keyPressed, presenter.get(), &presenter::Presenter::slotKeyPressed);
        connect(this, &MainWindow::keyReleased, presenter.get(), &presenter::Presenter::slotKeyReleased);
        connect(presenter.get(), &presenter::Presenter::displayChange, this, &MainWindow::slotDisplayChange);

        displayArea->textCursor().setKeepPositionOnInsert(true);
        displayAreaCursor = QTextCursor(displayArea->document());
        // last one
        connect(this, &MainWindow::ready, presenter.get(), &presenter::Presenter::init);
        emit ready();
    }

    void MainWindow::keyPressEvent(QKeyEvent *event)
    {
        int key = event->key();

        if (key == Qt::Key_D)
        {
            emit keyPressed(presenter::backspacePressed);
        }
        if (event->isAutoRepeat())
        {
            return;
        }
        if (key == configuration->get<conf::helpKeyScanCode>())
        {
            emit keyPressed(presenter::helpKeyPressed);
        }
        else if (key == configuration->get<int, conf::singleKeyScanCode>())
        {
            emit keyPressed(presenter::singleKeyPressed);
        }
        else if (key == configuration->get<int, conf::dotKeyScanCode>())
        {
            emit keyPressed(presenter::dotKeyPressed);
        }
        else if (key == configuration->get<int, conf::dashKeyScanCode>())
        {
            emit keyPressed(presenter::dashKeyPressed);
        }
    }

    void MainWindow::keyReleaseEvent(QKeyEvent *event)
    {
        if (event->isAutoRepeat())
        {
            return;
        }
        int key = event->key();
        if (key == configuration->get<int, conf::singleKeyScanCode>())
        {
            emit keyReleased(presenter::singleKeyPressed);
        }
        else if (key == configuration->get<int, conf::dotKeyScanCode>())
        {
            emit emit keyReleased(presenter::dotKeyPressed);
        }
        else if (key == configuration->get<int, conf::dashKeyScanCode>())
        {
            emit emit keyReleased(presenter::dashKeyPressed);
        }
    }
    void MainWindow::slotDisplayChange(const presenter::DisplayChange &change)
    {
        if (!change.textAppendToWords.empty())
        {
            int i = displayArea->textCursor().position();
            displayArea->insertPlainText(change.textAppendToWords.c_str());
            int end = i + change.textAppendToWords.length();
            QTextCharFormat fmt;
            fmt.setBackground(Qt::white);

            QTextCursor cursor(displayArea->document());
            cursor.setPosition(i, QTextCursor::MoveAnchor);
            cursor.setPosition(end, QTextCursor::KeepAnchor);
            cursor.setCharFormat(fmt);
            setTextCursorPosition(i);
        }
        if (!change.textToAppendToMorse.empty())
        {
            inputLine->insert(change.textToAppendToMorse.c_str());
        }
        if (change.charsToHighlight > 0)
        {
            if (change.areCorrect)
            {
                highlightCorrect(change.charsToHighlight);
            }
            else
            {
                highlightIncorrect(change.charsToHighlight);
            }
        }
        if (change.charsToDelete > 0)
        {
            backspace(change.charsToDelete);
        }
    }

    void MainWindow::setTextCursorPosition(int pos)
    {
        displayAreaCursor.setPosition(pos);
        int newPos = displayAreaCursor.position();
        displayArea->setTextCursor(displayAreaCursor);
        displayArea->ensureCursorVisible();
    }
    void MainWindow::highlightNextTokenForInput()
    {
    }
    void MainWindow::highlightCorrect(int chars)
    {
        highlightAndMoveCursor(chars, Qt::green);
    }
    void MainWindow::highlightIncorrect(int chars)
    {
        highlightAndMoveCursor(chars, Qt::red);
    }
    void MainWindow::backspace(int chars)
    {
        int end = displayAreaCursor.position();
        int begin = end - chars;
        QTextCharFormat fmt;
        fmt.setBackground(Qt::white);

        QTextCursor cursor(displayArea->document());
        cursor.setPosition(begin, QTextCursor::MoveAnchor);
        cursor.setPosition(end, QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);
        setTextCursorPosition(begin);
    }
    void MainWindow::highlightAndMoveCursor(int chars, QColor color)
    {
        int begin = displayAreaCursor.position();
        int end = begin + chars;
        QTextCharFormat fmt;
        fmt.setBackground(color);

        QTextCursor cursor(displayArea->document());
        cursor.setPosition(begin, QTextCursor::MoveAnchor);
        cursor.setPosition(end, QTextCursor::KeepAnchor);
        cursor.setCharFormat(fmt);
        setTextCursorPosition(end);
    }
}