#ifndef LINGAGUI_H
#define LINGAGUI_H

#include <QMainWindow>

namespace Ui {
class LingAgui;
}

class LingAgui : public QMainWindow
{
    Q_OBJECT

public:
    explicit LingAgui(QWidget *parent = 0);
    ~LingAgui();

private:
    Ui::LingAgui *ui;
};

#endif // LINGAGUI_H
