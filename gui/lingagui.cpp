#include "lingagui.h"
#include "ui_lingagui.h"

#include <QDebug>

LingAgui::LingAgui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LingAgui)
{
    ui->setupUi(this);
}

LingAgui::~LingAgui()
{
    delete ui;
}
