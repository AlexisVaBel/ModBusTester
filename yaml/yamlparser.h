#ifndef YAMLPARSER_H
#define YAMLPARSER_H

#include <QObject>
#include <QStack>
#include <QMap>
#include <QVariant>
#include <QString>
#include <QMapIterator>


class YaNode{
public:
    explicit    YaNode(QString str, QString val, int iDepth);
    int                             m_iDepth;
    bool                          m_bProcessed;
    QList<YaNode>   *m_lstChild;
    YaNode                  *m_nodeParent;
    QString                    m_strName;
    QString                    m_strValue;
};


class YamlParser : public QObject
{
    Q_OBJECT
public:
    explicit YamlParser(QObject *parent = 0,QString strPath="");

    void         readConf();
    void         getParentChildDep();
    QString  getNextChild(YaNode *nextChild);
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
