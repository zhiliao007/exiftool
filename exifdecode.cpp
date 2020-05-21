#include "exifdecode.h"
#include <exiv2/exiv2.hpp>



#include <QMap>
#include <QDebug>

QMap<QString, QString> exifDecode::get_exif_data(QString filename)
{
    QMap<QString, QString> exif_data;
    Exiv2::XmpParser::initialize();


    char*  ch;
    QByteArray ba = filename.toUtf8(); // must
    ch=ba.data();
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(ch);
    image->readMetadata();

    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        Exiv2::XmpParser::terminate();
        return exif_data;
    }

    for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != exifData.end(); ++i) {
        QString key = QString(QString::fromUtf8(i->key().c_str()));
        QString value = QString(QString::fromUtf8(i->value().toString().c_str()));
        exif_data[key] = value;
    }

    Exiv2::XmpParser::terminate();
    return exif_data;
}
