#include <QString>
#include <QtTest>

#include "inoffer.h"

class InOfferTest : public QObject
{
    Q_OBJECT

public:
    InOfferTest();

private Q_SLOTS:
    void TextToLU();
    void TextToLU_data();
};

InOfferTest::InOfferTest()
{
}

void InOfferTest::TextToLU()
{
    InOffer inOf;

    QFETCH(QString, offer);
    QFETCH(QStringList, list_word);
    QCOMPARE(*(inOf.TextToLU(offer)), list_word);
}

void InOfferTest::TextToLU_data()
{
    QTest::addColumn<QString>("offer");
    QTest::addColumn<QStringList>("list_word");

    QTest::newRow("Привет как дела") << QString("Привет как дела") << QStringList{QString("ПРИВЕТ"), QString("КАК"), QString("ДЕЛА")};
    QTest::newRow("Чем, занят") << QString("Чем, занят") << QStringList{QString("ЧЕМ"), QString("ЗАНЯТ")};
    QTest::newRow(".") << QString(".") << QStringList{};
    QTest::newRow("Empty") << QString("") << QStringList{};
    QTest::newRow("!!!...  ") << QString("!!!...  ") << QStringList{};
    QTest::newRow("привет .") << QString("привет .") << QStringList{QString("ПРИВЕТ")};
    QTest::newRow(" 777 ") << QString(" 777 ") << QStringList{QString("777")};
}

QTEST_APPLESS_MAIN(InOfferTest)

#include "tst_inoffertest.moc"
