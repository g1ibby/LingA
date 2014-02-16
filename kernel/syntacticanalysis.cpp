#include "syntacticanalysis.h"

SyntacticAnalysis::SyntacticAnalysis(QObject *parent) :
    QObject(parent)
{
}

void SyntacticAnalysis::LoadRules()
{
    rules = new QVector< SyntacticRule >;
    QString tmp;

    // Ask for data rules
    QSqlQuery query;
    if (!query.exec("SELECT * FROM Rule"))
    {
        qDebug() << "Даже селект не получается, я пас.";
    }
    QSqlRecord rec = query.record();
    while (query.next())
    {
        SyntacticRule rule;
        rule.MainWrd = query.value(rec.indexOf("MainWrd")).toInt();
        rule.Dist = query.value(rec.indexOf("Dist")).toInt();
        rule.Type = query.value(rec.indexOf("TypeLink")).toString();
        rule.PartOfSpeech1 = query.value(rec.indexOf("Part1")).toString();
        rule.PartOfSpeech2 = query.value(rec.indexOf("Part2")).toString();

        tmp = query.value(rec.indexOf("Cond1")).toString();
        tmp.length() != 0 ? rule.Cond1.append("") : rule.Cond1.clear();
        for (int i = 0; i < tmp.length(); i++)
        {
            if (tmp.mid(i, 1) != ";")
            {
                rule.Cond1[rule.Cond1.length() - 1] = rule.Cond1.at(rule.Cond1.length() - 1) + tmp.mid(i, 1);
            }
            else if (i < tmp.length() - 1)
            {
                rule.Cond1.append("");
            }
        }

        tmp = query.value(rec.indexOf("Cond2")).toString();
        tmp.length() != 0 ? rule.Cond2.append("") : rule.Cond2.clear();
        for (int i = 0; i < tmp.length(); i++)
        {
            if (tmp.mid(i, 1) != ";")
            {
                rule.Cond2[rule.Cond2.length() - 1] = rule.Cond2.at(rule.Cond2.length() - 1) + tmp.mid(i, 1);
            }
            else if (i < tmp.length() - 1)
            {
                rule.Cond2.append("");
            }
        }

        tmp = query.value(rec.indexOf("CondCommon")).toString();
        tmp.length() != 0 ? rule.CondCommon.append("") : rule.CondCommon.clear();
        for (int i = 0; i < tmp.length(); i++)
        {
            if (tmp.mid(i, 1) != ";")
            {
                rule.CondCommon[rule.CondCommon.length() - 1] = rule.CondCommon.at(rule.CondCommon.length() - 1) + tmp.mid(i, 1);
            }
            else if (i < tmp.length() - 1)
            {
                rule.CondCommon.append("");
            }
        }

        rules->append(rule);
    }
}

QVector< QStringList >* SyntacticAnalysis::BuildSyntGraph(QVector<MorphoStructure> *Wrd)
{
    Link = new QVector< QStringList >;
    for (int i = 0; i < 50; i++)
    {
        QStringList tmp;
        for (int j = 0; j < 50; j++)
        {
            tmp.append("");
        }
        Link->append(tmp);
    }

    for (int i = 0; i < Wrd->size(); i++)
    {
        Node.append(Wrd->at(i).Value);
    }

    // Check the prepositions

    bool IsCoordinated;
    int pt;
    int countpt;
    for (int i = 0; i < Wrd->size(); i++)
    {
        if (Wrd->at(i).Value == "ОТ" || Wrd->at(i).Value == "К" || Wrd->at(i).Value == "В" || Wrd->at(i).Value == "НА")
        {
            IsCoordinated = false;
            pt = i + 1;
            countpt = 0;
            while (!IsCoordinated || pt < Wrd->size())
            {
                for (int j = 0; j < Wrd->at(pt).CountMorph; j++)
                {
                    if (Wrd->at(pt).PartOfSpeech.at(j) == "С")
                    {
                        //Wrd->at(i).PartOfSpeech.replace(countpt, Wrd->at(pt).PartOfSpeech.at(j));
//                        Wrd[i].PartOfSpeech[countpt] = Wrd->at(pt).PartOfSpeech.at(j);
//                        Wrd[i].MorphAttr[countpt] = Wrd->at(pt).MorphAttr.at(j);
//                        Wrd[i].CountMorph = Wrd->at(pt).CountMorph;

                        MorphoStructure buf;
                        QString buf3;

                        buf = Wrd->at(i);
                        buf3 = Wrd->at(pt).PartOfSpeech.at(j);
                        buf.PartOfSpeech.replace(countpt, buf3);
                        Wrd->replace(i, buf);

                        buf = Wrd->at(i);
                        buf3 = Wrd->at(pt).MorphAttr.at(j);
                        buf.MorphAttr.replace(countpt, buf3);
                        Wrd->replace(i, buf);

                        buf = Wrd->at(i);
                        buf.CountMorph = Wrd->at(pt).CountMorph;
                        Wrd->replace(i, buf);




//                        buf.replace(pt, Wrd->at(pt).PartOfSpeech.at(j));
//                        Wrd->replace(i, buf);

//                        buf = Wrd->at(i).MorphAttr;
//                        buf.replace(pt, Wrd->at(pt).PartOfSpeech.at(j));
//                        Wrd->replace(i, buf);


//                        int buf2 = Wrd->at(i).CountMorph;
//                        buf2 = Wrd->at(pt).CountMorph;
//                        Wrd->replace(i, );
                        countpt++;
                        IsCoordinated = true;
                    }
                }
                pt++;
            }
            if (IsCoordinated)
            {
                QStringList buf(Link->at(i));
                buf.replace(pt - 1, "ВСП");
                Link->replace(i, buf);
            }
        }
    }

    int NW1[50],cNW1;
    int NW2[50],cNW2;
    int tmpw2,tmplc;
    bool T1,T2,TC,TL;
    for (int r = 0; r < rules->size(); r++)
    {
        cNW1 = 0;
        cNW2 = 0;
        for (int w1 = 0; w1 < Wrd->size() - 1; w1++)
        {
            T1 = false;
            for (int i = 0; i < Wrd->at(w1).CountMorph; i++)   // number of homonyms
            {
                if (rules->at(r).PartOfSpeech1 == Wrd->at(w1).PartOfSpeech.at(i) && rules->at(r).Cond1.length() == 0)
                {
                    T1 = true;
                    NW1[cNW1] = i;
                    cNW1++;
                }
                if (rules->at(r).PartOfSpeech1 == Wrd->at(w1).PartOfSpeech.at(i))
                {
                    for (int j = 0; j < rules->at(r).Cond1.length(); j++)
                    {
                        for (int q = 0; q < Wrd->at(w1).MorphAttr.at(i).length(); q++)
                        {
                            if (Wrd->at(w1).MorphAttr.at(i).mid(q, rules->at(r).Cond1.at(j).length()) == rules->at(r).Cond1.at(j))
                            {
                                T1 = true;
                                NW1[cNW1] = i;
                                cNW1++;
                            }
                        }
                    }
                }
            }

            if (rules->at(r).Dist == 0)
            {
                tmpw2 = Wrd->size();
            }
            else
            {
                tmpw2 = w1 + rules->at(r).Dist;
            }

            if (tmpw2 > Wrd->size())
            {
                tmpw2 = Wrd->size();
            }

            for (int w2 = w1 + 1; w2 < tmpw2; w2++)
            {
                T2 = false;
                for (int i = 0; i < Wrd->at(w2).CountMorph; i++)
                {
                    if (rules->at(r).PartOfSpeech2 == Wrd->at(w2).PartOfSpeech.at(i) && rules->at(r).Cond2.length() == 0)
                    {
                        T2 = true;
                        NW2[cNW2] = i;
                        cNW2++;
                    }
                    if (rules->at(r).PartOfSpeech2 == Wrd->at(w2).PartOfSpeech.at(i))
                    {
                        for (int j = 0; j < rules->at(r).Cond2.length(); j++)
                        {
                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(i).length(); q++)
                            {
                                if (Wrd->at(w2).MorphAttr.at(i).mid(q, rules->at(r).Cond2.at(j).length()) == rules->at(r).Cond2.at(j))
                                {
                                    T2 = true;
                                    NW2[cNW2] = i;
                                    cNW2++;
                                }
                            }
                        }
                    }
                }

                int CountTrueCond = 0;
                bool tmp1, tmp2, tmp3;
                TC = true;

                if (T1 && T2)
                {
                    if (rules->at(r).CondCommon.length() == 0)
                    {
                        TC = true;
                    }
                    for (int i = 0; i < rules->at(r).CondCommon.length(); i++)
                    {
                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "род")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 3; j++)//3 ًîنà
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Genus.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Genus.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "число")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Number.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Number.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "падеж")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 6; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Case.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Case.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "время")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 3; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Time.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Time.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "время")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 3; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Person.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Person.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "одуш")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Animation.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Animation.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "вид")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == View.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == View.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "перех")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Transitivity.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Transitivity.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "залог")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Deposit.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Deposit.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "повел")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == ImperativeVerb.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == ImperativeVerb.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }


                        tmp1 = false;
                        tmp2 = false;
                        tmp3 = false;

                        if (rules->at(r).CondCommon.at(i) == "неизм")
                        {
                            if (!(tmp1 && tmp2))
                            {
                                for (int n1 = 0; n1 < cNW1; n1++)
                                {
                                    for (int n2 = 0; n2 < cNW2; n2++)
                                    {
                                        for (int j = 0; j < 2; j++)
                                        {
                                            tmp1 = false;
                                            tmp2 = false;

                                            for (int q = 0; q < Wrd->at(w1).MorphAttr.at(NW1[n1]).length(); q++)
                                            {
                                                if (Wrd->at(w1).MorphAttr.at(NW1[n1]).mid(q,2) == Immutability.at(j))
                                                {
                                                    tmp1=true;
                                                }
                                            }

                                            for (int q = 0; q < Wrd->at(w2).MorphAttr.at(NW2[n2]).length(); q++)
                                            {
                                                if (Wrd->at(w2).MorphAttr.at(NW2[n2]).mid(q,2) == Immutability.at(j))
                                                {
                                                        tmp2 = true;
                                                }
                                            }
                                            if(tmp1 && tmp2 && !tmp3)
                                            {
                                                CountTrueCond++;
                                                tmp3 = true;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (CountTrueCond == rules->at(r).CondCommon.length())
                        {
                            TC = true;
                        }

                        tmplc = 0;
                        TL = false;

                        for (int l = 0; l < Wrd->size(); i++)
                        {
                            if (rules->at(r).MainWrd == 1)
                            {
                                if (Link->at(l).at(w2) != "")
                                    tmplc++;
                            }
                            else
                            {
                                if (Link->at(l).at(w1) != "")
                                    tmplc++;
                            }
                        }

                        if (Link->at(w1).at(w2) == "" && Link->at(w2).at(w1) == "" && !tmplc)
                            TL = true;

                        if (T1 && T2 && TC && TL)
                        {
                            if (rules->at(r).MainWrd == 1)
                            {
                                QStringList buf(Link->at(w1));
                                buf.replace(w2, rules->at(r).Type);
                                Link->replace(w1, buf);
                            }
                            else
                            {
                                QStringList buf(Link->at(w2));
                                buf.replace(w1, rules->at(r).Type);
                                Link->replace(w2, buf);;
                            }
                        }


                    }
                }

            }
        }
    }

    for (int i = 0; i < Wrd->size() - 1; i++)
    {
        if (Wrd->at(i).Value == "НЕ")
        {

            QStringList buf(Link->at(i));
            buf.replace(i + 1, "ОТР");
            Link->replace(i, buf);
        }
    }
    return Link;
}
