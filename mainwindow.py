#!/usr/bin/env python
# -*- coding:utf-8 -*-
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QDesktopWidget, QTableWidgetItem,QHeaderView,QTableView, QAction, QFileDialog
from view import Ui_MainWindow
from exifDecode import ExifDecode

VERSION = 'V0.1.1'
COLUMN_COUNT = 2

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MainWindow, self).__init__()
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.setWindowTitle('ExifTool  ' + VERSION + 'by liwq')
        screen = QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width() - size.width()) / 2, (screen.height() - size.height()) / 2)

        self.ui.actionOpen.triggered.connect(self.openProcess)
        self.ui.actionSave_as.triggered.connect(self.saveProcess)

    def _showResultOnTable(self, result):
        self.ui.tableWidget.setRowCount(len(result))
        self.ui.tableWidget.setColumnCount(COLUMN_COUNT)
        self.ui.tableWidget.setHorizontalHeaderLabels(['exif key', 'exif value'])
        print(type(result))
        row_count = 0
        for key in result:
            self.ui.tableWidget.setItem(row_count, 0, QTableWidgetItem(str(key)))
            self.ui.tableWidget.setItem(row_count, 1, QTableWidgetItem(str(result[key])))
            row_count += 1
        self.ui.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.ui.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.ui.tableWidget.setEditTriggers(QTableView.NoEditTriggers)

    def _getExifData(self, filename):
        ret = ExifDecode.get_exif_data(filename)
        print(ret)
        self._showResultOnTable(ret)

    def openProcess(self):
        openfile_name = QFileDialog.getOpenFileName(self, '选择文件', '', 'JPEG files(*.jpg *.JPG)')
        print(openfile_name[0])
        if openfile_name[0]:
            self._getExifData(openfile_name[0])

    def saveProcess(self):
        savefile_name = QFileDialog.getSaveFileName(self, '保存文件', 'test.cvs', 'CVS files(*.cvs *.CVS)')
        print(savefile_name)



