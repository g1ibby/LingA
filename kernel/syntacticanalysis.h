#ifndef SYNTACTICANALYSIS_H
#define SYNTACTICANALYSIS_H

#include <QObject>
#include "SyntacticRuleStructure.h"
#include "morphostructure.h"
#include <QVector>
#include <QString>
#include <QStringList>
#include <QtSql>
#include <QDebug>

class SyntacticAnalysis : public QObject
{
    Q_OBJECT
public:
    explicit SyntacticAnalysis(QObject *parent = 0);
    void LoadRules(void);
    QVector< QStringList >* BuildSyntGraph(QVector<MorphoStructure>* Wrd);
private:
    QVector< SyntacticRule >* rules;
    QVector< QStringList >* Link;

    QStringList Node;
    QStringList PartOfSpeech;
    QStringList MorphAttr;

    QStringList Genus{"мр", "жр", "ср"};
    QStringList Animation{"од", "но"};
    QStringList Number{"ед", "мн"};
    QStringList Case{"им", "рд", "дт", "вн", "тв", "пр"};
    QStringList View{"св", "нс"};
    QStringList Transitivity{"пе", "нп"};
    QStringList Deposit{"дст", "стр"};
    QStringList Time{"прш", "нст", "буд"};
    QStringList ImperativeVerb{"пвл"};
    QStringList Person{"1л", "2л", "3л"};
    QStringList Immutability{"0"};

signals:

public slots:

};

#endif // SYNTACTICANALYSIS_H
