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
    m_nodeParent=  0;
}

YamlParser::YamlParser(QObject *parent, QString strPath) :
    QObject(parent){
    m_strPath    =strPath;
    m_nodeRoot=0;
    m_nodePrnt =0;
    m_nodePrev =0;
    m_iTabCnt   =0;    
}

// readConf is ok for simple yaml structure
//*************** reading and preparing structure   ***********************//
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
        strLst=strName.split("\t");               // tabs divide to groups

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
                m_nodePrev=node;
                placeNodeToMap(node);
                addChildToRoot(m_nodeRoot,node);
                if(m_nodePrnt!=m_nodeRoot)
                    addChildToRoot(m_nodePrnt,node);

                if(iTabCur==ROOT_DEPTH){
                    placeNodeToMap(m_nodeRoot);
                    m_nodeRoot=node;
                    m_nodeRoot->m_nodeParent=0;
                }
            }
        };        
    };
    file.close();
    placeNodeToMap(node);
    placeNodeToMap(m_nodeRoot);
}

void YamlParser::addChildToRoot(YaNode *root, YaNode *child){
    if((root==0)||(child==0)||(root==child))return;
    if(root->m_iDepth>=child->m_iDepth)return;
    root->m_lstChild.append(child);
}

void YamlParser::placeNodeToMap(YaNode *node){
    if (node==0)return;
    m_mapParsed.insert(node->m_strName,node);
}
//*************// reading and preparing structure   ***********************//

//**************** returning structure for clients    ***********************//
void YamlParser::getParentChildDep(){
     foreach (YaNode *value, m_mapParsed){
         if(value==0) continue;
         if (value->m_nodeParent==0){
             qDebug()<<"root node is "<<value->m_strName;
             foreach(YaNode *node, value->m_lstChild){
                 if(node!=0)qDebug()<<":"<<node->m_strName<<node->m_strValue;
             }
         }
     }
}
//**************// returning structure for clients    ***********************//

