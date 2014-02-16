#include <QString>
#include <QtTest>
#include <QVector>

#include "inoffer.h"
#include "morphologicalanalysis.h"
#include "morphostructure.h"

class MorphologicalAnalysisTest : public QObject
{
    Q_OBJECT

public:
    MorphologicalAnalysisTest();

private Q_SLOTS:
    void Analysis();
    void Analysis_data();
};

MorphologicalAnalysisTest::MorphologicalAnalysisTest()
{
}

void MorphologicalAnalysisTest::Analysis()
{
    InOffer inOf;
    QStringList *ListWord = inOf.TextToLU("Введите текст.");
//    QStringList *ListWord = inOf.TextToLU("Создать новый проект, старый закрыть.");
    MorphologicalAnalysis MA;
    QVector<MorphoStructure>* ms = MA.Analysis(ListWord);


    QVERIFY2(true, "Failure");
}

void MorphologicalAnalysisTest::Analysis_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

QTEST_APPLESS_MAIN(MorphologicalAnalysisTest)

#include "tst_morphologicalanalysistest.moc"
