#include "QApplication"
#include "yaml/yamlparser.h"
int main (int argc, char* argv[]){
    QApplication app(argc, argv);
    YamlParser *yamlP=new YamlParser(0,"./conf/weintek1.yaml");
    yamlP->readConf();
    yamlP->getParentChildDep();
    return app.exec();
}
