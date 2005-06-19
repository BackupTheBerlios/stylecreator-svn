#ifndef UISREADER_H
#define UISREADER_H

class QTextEdit;
class QString;

class uisReader
{
    public:
        uisReader();

        void open(const QString& uisFile);
        QTextEdit* feedback;
};

#endif
