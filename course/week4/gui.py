# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'dialog.ui'
#
# Created: Tue Jan  6 12:57:42 2015
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(366, 235)
        self.findButton = QtGui.QPushButton(Dialog)
        self.findButton.setGeometry(QtCore.QRect(240, 20, 111, 31))
        self.findButton.setObjectName("findButton")
        self.findText = QtGui.QLineEdit(Dialog)
        self.findText.setGeometry(QtCore.QRect(20, 20, 211, 31))
        self.findText.setObjectName("findText")
        self.Result = QtGui.QTextEdit(Dialog)
        self.Result.setGeometry(QtCore.QRect(20, 70, 331, 151))
        self.Result.setObjectName("Result")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(QtGui.QApplication.translate("Dialog", "Dialog", None, QtGui.QApplication.UnicodeUTF8))
        self.findButton.setText(QtGui.QApplication.translate("Dialog", "Find", None, QtGui.QApplication.UnicodeUTF8))

