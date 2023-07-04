#ifndef DISPLAY_MAIN_WINDOW_H
#define DISPLAY_MAIN_WINDOW_H
#include <QApplication>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>

namespace display
{
    class MainWindow : public QWidget
    {
        Q_OBJECT
        public:
        explicit MainWindow(QWidget *parent =nullptr);

        signals:
        public slots:
        private:
        QGridLayout *mainLayout;
        QLineEdit *inputLine;
        QTextEdit *displayArea;
    };
}
#endif