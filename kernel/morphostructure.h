#ifndef MORPHOSTRUCTURE_H
#define MORPHOSTRUCTURE_H

#include <QString>
#include <QStringList>

struct MorphoStructure
{
    QString Value;
    QStringList MorphAttr;
    QStringList PartOfSpeech;
    int CountMorph;
    bool IsRecognise;
};

#endif // MORPHOSTRUCTURE_H
