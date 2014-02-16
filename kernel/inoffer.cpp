#include "inoffer.h"
#include <QDebug>
#include <QString>

InOffer::InOffer(QObject *parent) :
    QObject(parent)
{
    __ListWord = new QStringList();
}

InOffer::~InOffer()
{
    delete __ListWord;
}

QStringList *InOffer::TextToLU(QString text)
{
    text = text.toUpper();

    QString word;
    for (int i = 0; i < text.length(); i++)
    {
        if (text.at(i) != ' '
                && text.at(i) != '.'
                && text.at(i) != ','
                && text.at(i) != ':'
                && text.at(i) != '?'
                && text.at(i) != '!'
                && i + 1 <= text.length())
        {
            word = word + text.at(i);
        }
        else if (!word.isEmpty())
        {
            __ListWord->append(word);
            word.clear();
        }
    }

    if (!word.isEmpty())
    {
        __ListWord->append(word);
        word.clear();
    }


    return __ListWord;
}
