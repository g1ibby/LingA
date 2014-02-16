#ifndef INOFFER_H
#define INOFFER_H

#include <QObject>
#include <QString>
#include <QStringList>

class InOffer : public QObject
{
    Q_OBJECT
public:
    explicit InOffer(QObject *parent = 0);
    ~InOffer();
    QStringList* TextToLU(QString text);

private:
    QStringList *__ListWord;

signals:

public slots:

};

#endif // INOFFER_H
