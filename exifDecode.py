import os
import sys

from PIL import Image
from PIL.ExifTags import TAGS

class ExifDecode(object):

    @classmethod
    def get_exif_data(cls, fileName):
        """Get embedded EXIF data from image file."""
        ret = {}
        try:
            img = Image.open(fileName)
            if hasattr(img, '_getexif'):
                exifinfo = img._getexif()
                if exifinfo != None:
                    for tag, value in exifinfo.items():
                        decoded = TAGS.get(tag, tag)
                        ret[decoded] = value
        except IOError:
            print
            'IOERROR ' + fileName
        return ret


