#ifndef EXIFDECODE_H
#define EXIFDECODE_H

#include <QString>

class exifDecode
{
public:
    exifDecode();
    static QMap<QString, QString> get_exif_data(QString fileName);
};

#endif // EXIFDECODE_H
