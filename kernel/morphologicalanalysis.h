#ifndef MORPHOLOGICALANALYSIS_H
#define MORPHOLOGICALANALYSIS_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QDebug>
#include <QtSql>

#include "morphostructure.h"

class MorphologicalAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit MorphologicalAnalysis(QObject *parent = 0);
    QVector<MorphoStructure>* Analysis(QStringList* ListWord);

private:
    MorphoStructure MorphRecognise(QString word);
    int LoadIdEnd(QString basis);
    QString LoadEnd(int idEnd);
    void LoadMorph(QString ident, MorphoStructure& ms);

    QVector<MorphoStructure>* __MS;
signals:

public slots:

};

#endif // MORPHOLOGICALANALYSIS_H
