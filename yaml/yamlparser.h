#ifndef YAMLPARSER_H
#define YAMLPARSER_H

#include <QObject>
#include <QStack>
#include <QMap>
#include <QVariant>
#include <QString>

class YaNode{
public:
    explicit    YaNode(QString str,QVariant var);
    YaNode   *nodeParent;
    YaNode   *nodeChild;
    QString   strName;
    QVariant varValue;
};


class YamlParser : public QObject
{
    Q_OBJECT
public:
    explicit YamlParser(QObject *parent = 0,QString strPath="");

    void        readConf();
//    QMap<QString, QString> getParamMapByName(QString strName);
signals:

public slots:
private:
    int           m_iTabCnt;
    QString  m_strPath;
    YaNode  *m_nodePrnt;
    YaNode  *m_nodePrev;
    QMap <QString,YaNode*> m_mapParsed;
    QStack<YaNode*>               m_stackParse;
};

#endif // YAMLPARSER_H
