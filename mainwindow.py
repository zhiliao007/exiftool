#!/usr/bin/env python
# -*- coding:utf-8 -*-
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QMessageBox, QDesktopWidget, QTableWidgetItem,QHeaderView,QTableView, QAction, QFileDialog
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
        self.currfilename = ''
        self.ui.actionOpen.triggered.connect(self.openProcess)
        self.ui.actionSave_as.triggered.connect(self.saveProcess)

    def _showResultOnTable(self, result):
        self.ui.tableWidget.setRowCount(len(result))
        self.ui.tableWidget.setColumnCount(COLUMN_COUNT)
        self.ui.tableWidget.setHorizontalHeaderLabels(['ExifKey', 'ExifValue'])
        row_count = 0
        for key in result:
            self.ui.tableWidget.setItem(row_count, 0, QTableWidgetItem(str(key)))
            self.ui.tableWidget.setItem(row_count, 1, QTableWidgetItem(str(result[key])))
            row_count = row_count + 1
        self.ui.tableWidget.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        self.ui.tableWidget.horizontalHeader().setSectionResizeMode(0, QHeaderView.ResizeToContents)
        self.ui.tableWidget.setEditTriggers(QTableView.NoEditTriggers)

    def _getExifData(self, filename):
        ret = ExifDecode.get_exif_data(filename)
        print(ret)
        self._showResultOnTable(ret)

    def openProcess(self):
        openfile_name = QFileDialog.getOpenFileName(self, 'Choose File', '', 'JPEG files(*.jpg *.JPG)')
        self.currfilename = openfile_name[0]
        if len(openfile_name) > 2 :
            QMessageBox.warning(self, 'Warning', 'Only Support First Image !', QMessageBox.Ok)
        if self.currfilename:
            self._getExifData(self.currfilename)

    def saveProcess(self):
        if self.currfilename:
            #change to .csv for saving
            savefile_name = QFileDialog.getSaveFileName(self, 'Save File', self.currfilename.replace('.jpg','.csv'), 'CSV files(*.csv *.CSV)')
            print(savefile_name)
            i = 0
            j = 0
            conTents = ''
            if savefile_name[0]:
                f = open(savefile_name[0], 'w')
                with f:
                    for i in range(COLUMN_COUNT) :
                        conTents += self.ui.tableWidget.horizontalHeaderItem(i).text()
                        if i != 1 :
                            conTents += ','
                    conTents += '\n'
                    print(self.ui.tableWidget.rowCount())
                    for j in range(self.ui.tableWidget.rowCount()) :
                        conTents += '"' + self.ui.tableWidget.item(j, 0).text() + '"'
                        conTents += ','
                        conTents += '"' + self.ui.tableWidget.item(j, 1).text() + '"'
                        conTents += '\n'
                    f.write(conTents)
            f.close()
        else:
            QMessageBox.critical(self, 'Error', 'NOT OPEN JPEG!', QMessageBox.Ok)


