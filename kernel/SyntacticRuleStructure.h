#ifndef SYNTACTICRULESTRUCTURE_H
#define SYNTACTICRULESTRUCTURE_H

#include <QString>
#include <QStringList>

struct SyntacticRule
{
    QString Type;
    int MainWrd;
    int Dist;

    QString PartOfSpeech1;
    QStringList Cond1;

    QString PartOfSpeech2;
    QStringList Cond2;

    QStringList CondCommon;
};

#endif // SYNTACTICRULESTRUCTURE_H
