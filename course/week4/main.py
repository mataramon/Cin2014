#!/usr/bin/env python

# System dependences
import sys
import os

# Qt and Graphical Classes
from PySide.QtGui import QMainWindow, QApplication, QFileDialog, QStyle, QWindowsStyle, QMotifStyle, QMessageBox 
from PySide import QtCore
# your template
from gui import *

# Front End GUI
class MainWindow(QMainWindow,Ui_Dialog):
    
    def __init__(self,parent = None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
    # using a slot
    
    @QtCore.Slot(list) # note the slot can be str, dict, list any type you want
    def set_result(self, result):
        text = ""
        for i in result:
            text+= "{0} \n".format(i)
            
        self.Result.setText(text)
        
# Back end
class Logic(QtCore.QObject):
    # signals are class items
    calculation_result = QtCore.Signal(list)
        
    def __init__(self, parent = None):
        super(Logic, self).__init__(parent)
        
    @QtCore.Slot()
    def calculate(self):
        print ("Starting calculation in background")
        range_calculation = range(100)
        self.calculation_result.emit(range_calculation)
        
    

if __name__ == '__main__':
    app = QApplication(sys.argv)
    app.setStyle("Cleanlooks")
    frame = MainWindow()
    backend = Logic()
    # connecting objects
    # GUI find button when is clicked executes backend calculate function
    frame.findButton.clicked.connect(backend.calculate)
    # Backend class when is emited (the calculation is done) sets the gui textbox result
    backend.calculation_result.connect(frame.set_result)
    
    frame.show()
    app.exec_()