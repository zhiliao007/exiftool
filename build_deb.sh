#!/bin/sh

###############################################################################
# Define QT path
QT_DIR=/opt/Qt5.12.2/5.12.2/gcc_64
# Define exiv2 path
EXIV2_DIR=/home/liwq/code/exiv2

# Define version number
EXIFTOOL_MAJARVERSION="0"
EXIFTOOL_SUBVERSION="2"
EXIFTOOL_REVISION="0"
###############################################################################


###############################################################################
export PATH=$QT_DIR/bin:$PATH
export LD_LIBRARY_PATH=$EXIV2_DIR/lib:$QT_DIR/lib:$LD_LIBRARY_PATH
export QT_PLUGIN_PATH=$QT_DIR/plugins:$QT_PLUGIN_PATH
export QML2_IMPORT_PATH=$QT_DIR/qml:$QML2_IMPORT_PATH
# Synthetic version number
EXIFTOOL_VERSION="V"$EXIFTOOL_MAJARVERSION""$EXIFTOOL_SUBVERSION""$EXIFTOOL_REVISION""
# Make
rm -rf .qmake.stash Makefile
qmake ./exifTool.pro -spec linux-g++ CONFIG+=qtquickcompiler
make clean
echo begin to make
make -j8 
# Clean packaging directory
rm -rf ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64 
rm -f ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64.deb
# Make packaging directory
cp -r ./dpkg/ExifTool ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64
mkdir -p ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool
cp ./build_release/out/ExifTool ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool/ExifTool
# Use linuxdeployqt to copy the dependent .so library to the packaging directory
echo use linuxdeployqt to copy the dependent .so library to the packaging directory
./tools/linuxdeployqt ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool/ExifTool -appimage
rm -rf ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool/doc ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool/default.png ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool/AppRun ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool/default.desktop
cp ./img/ico.png ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/opt/ExifTool/ExifTool.png
# Configure packaging information
echo begin to config
sed -i "s/Version: 0.2.0/Version: $EXIFTOOL_MAJARVERSION.$EXIFTOOL_SUBVERSION$YEXIFTOOL_REVISION/g" ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/DEBIAN/control
InstalledSize=94515.2 # TODO:Calculate size
sed -i "s/Installed-Size: 81203.2/Installed-Size: $InstalledSize/g" ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/DEBIAN/control
chmod 755 ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64/* -R
# Bale
echo begin to bale
dpkg -b ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64 ./dpkg/ExifTool_Linux_"$EXIFTOOL_VERSION"_x86_64.deb
echo build success!
###############################################################################
