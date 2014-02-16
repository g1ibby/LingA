#include <QString>
#include <QtTest>
#include <QVector>

#include "inoffer.h"
#include "morphologicalanalysis.h"
#include "morphostructure.h"
#include "syntacticanalysis.h"
#include "SyntacticRuleStructure.h"

class SyntacticAnalysisTest : public QObject
{
    Q_OBJECT

public:
    SyntacticAnalysisTest();

private Q_SLOTS:
    void LoadRules();
};

SyntacticAnalysisTest::SyntacticAnalysisTest()
{
}

void SyntacticAnalysisTest::LoadRules()
{
    InOffer inOf;
    QStringList *ListWord = inOf.TextToLU("Введите текст");
    MorphologicalAnalysis MA;
    QVector<MorphoStructure>* ms = MA.Analysis(ListWord);

    SyntacticAnalysis SynA;
    SynA.LoadRules();

    QVector< QStringList >* link = SynA.BuildSyntGraph(ms);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SyntacticAnalysisTest)

#include "tst_syntacticanalysistest.moc"
