#ifndef CWTRAINER_DISPLAY_MAIN_WINDOW_H
#define CWTRAINER_DISPLAY_MAIN_WINDOW_H
#include "../beeper/beeper.h"
#include "../presenter/presenter.h"
#include <QApplication>
#include <QGridLayout>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <memory>

namespace display
{
    class MainWindow : public QWidget
    {
        Q_OBJECT
        public:
        explicit MainWindow(std::shared_ptr<presenter::Presenter> presenter, 
         std::shared_ptr<configuration::Configuration> configuration,
         QWidget *parent =nullptr);

        protected:
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
        signals:
        void singleKeyPressed();
        void dotKeyPressed();
        void dashKeyPressed();
        void keyReleased();
        public slots:
        
        private:
        std::shared_ptr<configuration::Configuration> configuration;
        std::shared_ptr<presenter::Presenter> presenter;
        QGridLayout *mainLayout;
        QLineEdit *inputLine;
        QTextEdit *displayArea;
    };
}
#endif