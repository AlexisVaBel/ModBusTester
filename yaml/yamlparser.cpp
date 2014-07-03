#include "yamlparser.h"
#include <QMessageBox>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QDebug>

YaNode::YaNode(QString str, QString val, int iDepth){
    m_strName    =    str;
    m_strValue     =   val;
    m_iDepth        =   iDepth;
    m_bProcessed=   false;
    m_nodeParent=  0;
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
        strName=inTxt.readLine();
        if(strName.contains("#")) continue; // don`t process comments
        strLst=strName.split("\t");
        strName.clear();
        for(int iCnt=0;iCnt<strLst.count();iCnt++){

            if (strLst.at(iCnt).isEmpty()){
                iTabCur++;              
            }else{
                strNode=strLst.at(iCnt).split(":");
                if(strNode.count()<2)continue;
                strName=strNode.at(0);
                strVal=strNode.at(1);

                if(iTabCur>m_iTabCnt){
                    m_nodePrnt=m_nodePrev;
                    m_iTabCnt= iTabCur ;
                };
                if(iTabCur<m_iTabCnt){
                    while(!m_stackParse.empty()){
                        node=m_stackParse.pop();
                        if (node==0) continue;
                        if(node->m_iDepth<iTabCur){
                            m_iTabCnt=iTabCur;
                            m_nodePrnt=node;
                            break;
                        }
                     }
                };

                m_stackParse.push(m_nodePrev);
                node=new YaNode(strName,strVal,iTabCur);
                node->m_nodeParent=m_nodePrnt;
                if(m_nodePrnt!=0){

                }
                m_nodePrev=node;
                m_mapParsed.insert(node->m_strName,node);
            }
        };        
    };
    m_mapParsed.insert(node->m_strName,node);
    file.close();    
}

void YamlParser::getParentChildDep(){

     foreach (YaNode *value, m_mapParsed){
         if(value==0) continue;
         if (value->m_nodeParent==0){
             qDebug()<<"root node is "<<value->m_strName;
         }
     }
//YaNode      *node=0;
//    QMapIterator<QString, YaNode*> i(m_mapParsed);
//    while (i.hasNext()) {
//        i.next();
//        node=i.value();
//        if (node==0) continue;
//        m_nodePrnt=node->m_nodeParent;
//        if (m_nodePrnt==0){
//            qDebug()<<node->m_strName;
//        }else{
//            qDebug()<<node->m_strName<<" Parent is "<<m_nodePrnt->m_strName;
//        }
//        qDebug()<<node->m_strValue;
//        qDebug()<<node->m_bHasChild;
//        qDebug()<<" *********";
//    }
}

// YamlNode implementation
