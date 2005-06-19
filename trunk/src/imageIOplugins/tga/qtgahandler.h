#ifndef QTGAHANDLER_H
#define QTGAHANDLER_H

#include <qimageiohandler.h>

class QTgaHandler : public QImageIOHandler
{
public:
    QTgaHandler();

    bool canRead() const;
    bool read(QImage *image);
    bool write(const QImage &image);

    QByteArray name() const;

    static bool canRead(QIODevice *device);

    QVariant option(ImageOption option) const;
    void setOption(ImageOption option, const QVariant &value);
    bool supportsOption(ImageOption option) const;

private:
    //int quality;
    QByteArray parameters;
};

#endif
