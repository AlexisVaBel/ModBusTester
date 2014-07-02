#include "yamlparser.h"
#include <QMessageBox>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

YaNode::YaNode(QString str,QVariant var){
    strName=str;
    varValue=var;
}

YamlParser::YamlParser(QObject *parent, QString strPath) :
    QObject(parent){
    m_strPath    =strPath;
    m_nodePrnt =0;
    m_nodePrev =0;
    m_iTabCnt   =0;
}

void YamlParser::readConf(){
    QFile file(m_strPath);
    if (!file.open(QIODevice::ReadOnly)){
        QMessageBox::information(0,"error",file.errorString());
        return;
    }
    QTextStream inTxt(&file);
    QStringList strLst;
    QStringList strNode;
    QString        strName;
    QString        strVal;
    YaNode      *node=0;
    int iTabCur=0;
// tabs used for deviding elements and allocate children
    while (!inTxt.atEnd()) {
        iTabCur=0;
        strLst=inTxt.readLine().split("\t");
        for(int iCnt=0;iCnt<strLst.count();iCnt++){
            if (strLst.at(iCnt).isEmpty()){
                iTabCur++;
                qDebug()<<"Tab";
            };

            strNode=strLst.at(iCnt).split(":");
            for(int iCnt2=0;iCnt2<strNode.count();iCnt2++){
                qDebug()<<iCnt;
                qDebug()<<strNode.at(iCnt2);
            }
//            strName=strLst.at(iCnt).split(":").at(0);
//            strVal=strLst.at(iCnt).split(":").at(1);

            if(iTabCur==m_iTabCnt){
                m_stackParse.push(m_nodePrev);
            };
            if(iTabCur>m_iTabCnt){
                m_nodePrnt=m_nodePrev;
                iTabCur       =m_iTabCnt;
            }
            node=new YaNode(strName,strVal);
            node->nodeParent=m_nodePrnt;
            m_nodePrev=node;
        };
    }
    file.close();
//    while(!m_stackParse.empty()){
//        node=m_stackParse.pop();
//        qDebug()<<node->strName;
//        qDebug()<<node->varValue;
//    }
}


//QMap<QString, QString> YamlParser::getParamMapByName(QString strName){

//}
