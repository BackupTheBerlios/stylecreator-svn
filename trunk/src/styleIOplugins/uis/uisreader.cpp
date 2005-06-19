#include "uisreader.h"

#include <QSettings>
#include <QTextEdit>
#include <QFileInfo>
#include <QDir>
#include <QImage>
#include <QPixmap>
#include <QVariant>
#include <QDebug>
#include <QChar>
#include <QFile>
#include <QTextStream>

#include "qtstylewriter.h"

uisReader::uisReader()
{

}

void uisReader::open(const QString& uisFile)
{

    /*
        UGLY UGLY UGLY HACK !!!
    */
    QFile inFile(uisFile);
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text))
            return;

    
    QFile outFile("/tmp/temp.ini");
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream in(&inFile);
    QTextStream out(&outFile);

    while (!in.atEnd()) 
    {
        QString line = in.readLine();
    
        line.replace("\\","\\\\");
        out << line << endl;   
    }
    
    inFile.close();
    outFile.close();
    /*
        END OF UGLY UGLY UGLY HACK
    */

    QFileInfo uisFileInfo(uisFile);
    QDir uisDir(uisFileInfo.dir());
    uisDir.cdUp();
    
    QtStyleWriter sw;
    sw.setPath(uisDir.path());

    QString skinName;

    if(feedback)
    {
        feedback->clear();
        feedback->append("<strong>Parsing file: </strong>" + uisFile);
        feedback->append("");
    }

    QSettings s("/tmp/temp.ini", QSettings::IniFormat);

    s.beginGroup("TitlebarSkin");

    skinName = s.value("SkinName", "").toString();
    sw.setName(skinName);

    if(feedback)
    {
        feedback->append(QString("<strong>skin name: </strong>%1").arg(s.value("SkinName", QString("-")).toString()));
        feedback->append(QString("<strong>skin author: </strong>%1").arg(s.value("SkinAuthor", QString("-")).toString()));
        feedback->append(QString("<strong>author email: </strong>%1").arg(s.value("AuthorEmail", QString("-")).toString()));
        feedback->append(QString("<strong>author url: </strong>%1").arg(s.value("AuthorsURL", QString("-")).toString()));
        feedback->append(QString("<strong>skin generator: </strong>%1").arg(s.value("Generator", QString("-")).toString()));
        feedback->append(QString("<strong>windowblinds: </strong>%1").arg(s.value("WBVer", QString("-")).toString()));
        feedback->append(QString("<strong>special notes: </strong>%1").arg(s.value("SpecialNotes", QString("-")).toString()));
        feedback->append(QString("<strong>editor notes: </strong>%1").arg(s.value("EditorNotes", QString("-")).toString()));
        feedback->append("");
    }

    s.endGroup();

    s.beginGroup("Buttons");

    if(feedback)
    {
        feedback->append("Converting buttons...");
    }

    QString buttonFile = s.value("bitmap", "").toString();

    buttonFile = QDir::convertSeparators(uisDir.path() + "/" + buttonFile);
    buttonFile.replace("\\","/");

    if(feedback)
    {
        feedback->append("<strong>button bitmap: </strong>" + buttonFile);
    }
    sw.createButton(buttonFile,
                    s.value("TopHeight", 0).toInt(),
                    s.value("LeftWidth", 0).toInt(),
                    s.value("RightWidth", 0).toInt(),
                    s.value("BottomHeight", 0).toInt());

    
    
    sw.writeQtStyle();
    
}

