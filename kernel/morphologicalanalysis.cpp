#include "morphologicalanalysis.h"

MorphologicalAnalysis::MorphologicalAnalysis(QObject *parent) :
    QObject(parent)
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("../../data/rules.db");

    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
    }
    else
    {
        qDebug() << "ОК. к базе подключился";
    }

    __MS = new QVector<MorphoStructure>;
}

QVector<MorphoStructure>* MorphologicalAnalysis::Analysis(QStringList *ListWord)
{
    MorphoStructure ms_temp;
    for (int i = 0; i < ListWord->length(); i++)
    {

        ms_temp = MorphRecognise(ListWord->at(i));
        if (ms_temp.IsRecognise)
        {
            __MS->append(ms_temp);
        }
    }

    return __MS;
}

MorphoStructure MorphologicalAnalysis::MorphRecognise(QString word)
{
    MorphoStructure ms_temp;
    ms_temp.Value = word;
    ms_temp.CountMorph = 0;

    QString TmpWrd = word;
    QString End;
    QString Ends;
    QString Attributes;

    bool IsFound = false;
    bool Exclusion = false;
    int c;
    int tmpcount = 0;

    while (TmpWrd.length() != 0)
    {

        IsFound = false;
        int idEnd = LoadIdEnd(TmpWrd);
        if (idEnd == -1)
        {
            TmpWrd = TmpWrd.left(TmpWrd.length() - 1);
            if (TmpWrd.length() == 0 && !Exclusion)
            {
                TmpWrd = "#";
                Exclusion = true;
            }
            continue;
        }
        Ends = LoadEnd(idEnd);
        c = 0;

        while (c < Ends.length() && !IsFound)
        {
            bool inc = true;
            if (Ends.at(c) == '%')
            {
                inc = false;
                c++;
                while(Ends.at(c) != '*')
                {
                    End = End + Ends.at(c);
                    c++;
                }
                c++;

                while (Ends.at(c) != '%' && Ends.at(c) != ' ' && c < Ends.length())
                {
                    Attributes = Attributes + Ends.at(c);
                    c++;
                }

                if ((TmpWrd + End == word) || (End == word))
                {
                    IsFound = true;
                }
                else
                {
                    End = "";
                    Attributes = "";
                }
            }
            if (inc) c++;
        }
        if (IsFound)
        {
            tmpcount = ms_temp.CountMorph;
            ms_temp.CountMorph = ms_temp.CountMorph + Attributes.length() / 2;
            for (int j = tmpcount; j < ms_temp.CountMorph; j++)
            {
                LoadMorph(Attributes.mid((j - tmpcount) * 2, 2), ms_temp);
            }
            End = "";
            Attributes = "";
            TmpWrd = TmpWrd.left(TmpWrd.length() - 1);
        }
        else
        {
            TmpWrd = TmpWrd.left(TmpWrd.length() - 1);
        }
    }
    if (ms_temp.CountMorph) ms_temp.IsRecognise = true;
    else    ms_temp.IsRecognise = false;

    return ms_temp;
}

int MorphologicalAnalysis::LoadIdEnd(QString basis)
{
    int idEnd = -1;
    QSqlQuery query;
    query.prepare("SELECT * FROM Morphs WHERE morph = ?");
    query.bindValue(0, basis);

    if (!query.exec())
    {
        qDebug() << "Даже селект не получается, я пас.";
    }

    QSqlRecord rec = query.record();
    if (query.next())
    {
        idEnd = query.value(rec.indexOf("end_id")).toInt();
    }

    return idEnd;
}

QString MorphologicalAnalysis::LoadEnd(int idEnd)
{
    QString End;
    QSqlQuery query;
    query.prepare("SELECT * FROM End WHERE end_id = ?");
    query.bindValue(0, idEnd);

    if (!query.exec())
    {
        qDebug() << "2Даже селект не получается, я пас.";
    }

    QSqlRecord rec = query.record();
    if (query.next())
    {
        End = query.value(rec.indexOf("end")).toString();
    }

    return End;
}

void MorphologicalAnalysis::LoadMorph(QString ident, MorphoStructure &ms)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM MorphAttributes WHERE Ident = ?");
    query.bindValue(0, ident);

    if (!query.exec())
    {
        qDebug() << "2Даже селект не получается, я пас.";
    }

//    if (query.size() == -1) return;

    QSqlRecord rec = query.record();
    if (query.next())
    {
        ms.PartOfSpeech.append(query.value(rec.indexOf("PartOfSpeech")).toString());
        ms.MorphAttr.append(query.value(rec.indexOf("MorphAttributes")).toString());
    }
}
