#ifndef CWTRAINER_DISPLAY_MAIN_WINDOW_H
#define CWTRAINER_DISPLAY_MAIN_WINDOW_H
#include "../beeper/beeper.h"
#include "../presenter/presenter.h"
#include "../presenter/presenter_types.h"
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
                            QWidget *parent = nullptr);

    protected:
        void keyPressEvent(QKeyEvent *event) override;
        void keyReleaseEvent(QKeyEvent *event) override;
    signals:
        void keyPressed(presenter::InputState state);
        void keyReleased(presenter::InputState state);
        /**
         * The display is ready to be instructed by the presenter
         */
        void ready();
    private slots:
        /**
         * Handles changes on the display
         */
        void slotDisplayChange(const presenter::DisplayChange &change);

    private:
        void setTextCursorPosition(int pos);
        void highlightNextTokenForInput();
        void highlightCorrect(int chars);
        void highlightIncorrect(int chars);
        void backspace(int chars);

        void highlightAndMoveCursor(int chars, QColor color );

        QTextCursor displayAreaCursor;
        std::shared_ptr<configuration::Configuration> configuration;
        std::shared_ptr<presenter::Presenter> presenter;
        QGridLayout *mainLayout;
        QLineEdit *inputLine;
        QTextEdit *displayArea;
    };
}
#endif