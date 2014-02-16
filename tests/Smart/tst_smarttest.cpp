#include <QString>
#include <QtTest>
#include "smart.h"

class SmartTest : public QObject
{
    Q_OBJECT

public:
    SmartTest();

private Q_SLOTS:
    void testCase1();
    void testCase1_data();
};

SmartTest::SmartTest()
{
}

void SmartTest::testCase1_data()
{
    QTest::addColumn<int>("a");
    QTest::addColumn<int>("b");
    QTest::addColumn<int>("result");

    QTest::newRow("res1") << 1 << 9 << 9;
}

void SmartTest::testCase1()
{
    Smart a2;
//    QCOMPARE(a.max(1, 0), 1);
//    QCOMPARE(a.max(7, 6), 7);

//    QVERIFY(1 + 1 == 2);
//    QCOMPARE(a.max(1,   0), 1);
//    QCOMPARE(a.max(-1,  1), 1);
//    QCOMPARE(a.max(4,   8), 8);
//    QCOMPARE(a.max(0,   0), 0);
//    QCOMPARE(a.max(1,   1), 1);
//    QCOMPARE(a.max(-10,-5), -5);

    QFETCH(int, a);
    QFETCH(int, b);
    QFETCH(int, result);
    QCOMPARE(a2.max(a, b), result);
}

QTEST_APPLESS_MAIN(SmartTest)

#include "tst_smarttest.moc"
