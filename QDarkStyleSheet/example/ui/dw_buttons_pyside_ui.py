# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'dw_buttons.ui'
#
# Created: Fri May 31 23:17:02 2019
#      by: pyside-uic 0.2.15 running on PySide 1.2.2
#
# WARNING! All changes made in this file will be lost!

from PySide import QtCore, QtGui

class Ui_DockWidget(object):
    def setupUi(self, DockWidget):
        DockWidget.setObjectName("DockWidget")
        DockWidget.resize(562, 497)
        self.dockWidgetContents = QtGui.QWidget()
        self.dockWidgetContents.setObjectName("dockWidgetContents")
        self.gridLayout = QtGui.QGridLayout(self.dockWidgetContents)
        self.gridLayout.setObjectName("gridLayout")
        self.pushButtonChecked = QtGui.QPushButton(self.dockWidgetContents)
        self.pushButtonChecked.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.pushButtonChecked.setCheckable(True)
        self.pushButtonChecked.setChecked(True)
        self.pushButtonChecked.setObjectName("pushButtonChecked")
        self.gridLayout.addWidget(self.pushButtonChecked, 2, 1, 1, 6)
        self.label_2 = QtGui.QLabel(self.dockWidgetContents)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 6, 0, 1, 1)
        self.toolButtonChecked = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonChecked.setCheckable(True)
        self.toolButtonChecked.setChecked(True)
        self.toolButtonChecked.setPopupMode(QtGui.QToolButton.DelayedPopup)
        self.toolButtonChecked.setObjectName("toolButtonChecked")
        self.gridLayout.addWidget(self.toolButtonChecked, 6, 1, 1, 4)
        self.toolButtonCheckedDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonCheckedDis.setEnabled(False)
        self.toolButtonCheckedDis.setCheckable(True)
        self.toolButtonCheckedDis.setChecked(True)
        self.toolButtonCheckedDis.setPopupMode(QtGui.QToolButton.DelayedPopup)
        self.toolButtonCheckedDis.setObjectName("toolButtonCheckedDis")
        self.gridLayout.addWidget(self.toolButtonCheckedDis, 6, 7, 1, 4)
        self.label_3 = QtGui.QLabel(self.dockWidgetContents)
        self.label_3.setObjectName("label_3")
        self.gridLayout.addWidget(self.label_3, 7, 0, 1, 1)
        self.toolButtonArrowDown = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowDown.setArrowType(QtCore.Qt.DownArrow)
        self.toolButtonArrowDown.setObjectName("toolButtonArrowDown")
        self.gridLayout.addWidget(self.toolButtonArrowDown, 7, 1, 1, 1)
        self.toolButtonArrowUp = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowUp.setArrowType(QtCore.Qt.UpArrow)
        self.toolButtonArrowUp.setObjectName("toolButtonArrowUp")
        self.gridLayout.addWidget(self.toolButtonArrowUp, 7, 2, 1, 1)
        self.toolButtonArrowRight = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowRight.setArrowType(QtCore.Qt.RightArrow)
        self.toolButtonArrowRight.setObjectName("toolButtonArrowRight")
        self.gridLayout.addWidget(self.toolButtonArrowRight, 7, 3, 1, 1)
        self.toolButtonArrowLeft = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowLeft.setArrowType(QtCore.Qt.LeftArrow)
        self.toolButtonArrowLeft.setObjectName("toolButtonArrowLeft")
        self.gridLayout.addWidget(self.toolButtonArrowLeft, 7, 4, 1, 2)
        self.toolButtonArrowDownDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowDownDis.setEnabled(False)
        self.toolButtonArrowDownDis.setArrowType(QtCore.Qt.DownArrow)
        self.toolButtonArrowDownDis.setObjectName("toolButtonArrowDownDis")
        self.gridLayout.addWidget(self.toolButtonArrowDownDis, 7, 7, 1, 1)
        self.toolButtonArrowUpDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowUpDis.setEnabled(False)
        self.toolButtonArrowUpDis.setArrowType(QtCore.Qt.UpArrow)
        self.toolButtonArrowUpDis.setObjectName("toolButtonArrowUpDis")
        self.gridLayout.addWidget(self.toolButtonArrowUpDis, 7, 8, 1, 1)
        self.toolButtonArrowRightDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowRightDis.setEnabled(False)
        self.toolButtonArrowRightDis.setArrowType(QtCore.Qt.RightArrow)
        self.toolButtonArrowRightDis.setObjectName("toolButtonArrowRightDis")
        self.gridLayout.addWidget(self.toolButtonArrowRightDis, 7, 9, 1, 1)
        self.toolButtonArrowLeftDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonArrowLeftDis.setEnabled(False)
        self.toolButtonArrowLeftDis.setArrowType(QtCore.Qt.LeftArrow)
        self.toolButtonArrowLeftDis.setObjectName("toolButtonArrowLeftDis")
        self.gridLayout.addWidget(self.toolButtonArrowLeftDis, 7, 10, 1, 2)
        self.radioButtonChecked = QtGui.QRadioButton(self.dockWidgetContents)
        self.radioButtonChecked.setChecked(True)
        self.radioButtonChecked.setAutoExclusive(False)
        self.radioButtonChecked.setObjectName("radioButtonChecked")
        self.gridLayout.addWidget(self.radioButtonChecked, 8, 1, 1, 3)
        self.radioButtonCheckedDis = QtGui.QRadioButton(self.dockWidgetContents)
        self.radioButtonCheckedDis.setEnabled(False)
        self.radioButtonCheckedDis.setChecked(True)
        self.radioButtonCheckedDis.setAutoExclusive(False)
        self.radioButtonCheckedDis.setObjectName("radioButtonCheckedDis")
        self.gridLayout.addWidget(self.radioButtonCheckedDis, 8, 7, 1, 3)
        self.label_29 = QtGui.QLabel(self.dockWidgetContents)
        self.label_29.setMinimumSize(QtCore.QSize(0, 0))
        self.label_29.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_29.setFont(font)
        self.label_29.setObjectName("label_29")
        self.gridLayout.addWidget(self.label_29, 9, 0, 1, 1)
        self.radioButtonUnchecked = QtGui.QRadioButton(self.dockWidgetContents)
        self.radioButtonUnchecked.setMinimumSize(QtCore.QSize(0, 0))
        self.radioButtonUnchecked.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.radioButtonUnchecked.setAutoExclusive(False)
        self.radioButtonUnchecked.setObjectName("radioButtonUnchecked")
        self.gridLayout.addWidget(self.radioButtonUnchecked, 9, 1, 1, 4)
        self.radioButtonUncheckedDis = QtGui.QRadioButton(self.dockWidgetContents)
        self.radioButtonUncheckedDis.setEnabled(False)
        self.radioButtonUncheckedDis.setMinimumSize(QtCore.QSize(0, 0))
        self.radioButtonUncheckedDis.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.radioButtonUncheckedDis.setChecked(False)
        self.radioButtonUncheckedDis.setAutoExclusive(False)
        self.radioButtonUncheckedDis.setObjectName("radioButtonUncheckedDis")
        self.gridLayout.addWidget(self.radioButtonUncheckedDis, 9, 7, 1, 4)
        self.label_53 = QtGui.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_53.setFont(font)
        self.label_53.setObjectName("label_53")
        self.gridLayout.addWidget(self.label_53, 10, 0, 1, 1)
        self.checkBoxChecked = QtGui.QCheckBox(self.dockWidgetContents)
        self.checkBoxChecked.setChecked(True)
        self.checkBoxChecked.setObjectName("checkBoxChecked")
        self.gridLayout.addWidget(self.checkBoxChecked, 10, 1, 1, 3)
        self.checkBoxCheckedDis = QtGui.QCheckBox(self.dockWidgetContents)
        self.checkBoxCheckedDis.setEnabled(False)
        self.checkBoxCheckedDis.setChecked(True)
        self.checkBoxCheckedDis.setObjectName("checkBoxCheckedDis")
        self.gridLayout.addWidget(self.checkBoxCheckedDis, 10, 7, 1, 3)
        self.label_30 = QtGui.QLabel(self.dockWidgetContents)
        self.label_30.setMinimumSize(QtCore.QSize(0, 0))
        self.label_30.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_30.setFont(font)
        self.label_30.setObjectName("label_30")
        self.gridLayout.addWidget(self.label_30, 11, 0, 1, 1)
        self.checkBoxEnabled = QtGui.QCheckBox(self.dockWidgetContents)
        self.checkBoxEnabled.setMinimumSize(QtCore.QSize(0, 0))
        self.checkBoxEnabled.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.checkBoxEnabled.setTristate(False)
        self.checkBoxEnabled.setObjectName("checkBoxEnabled")
        self.gridLayout.addWidget(self.checkBoxEnabled, 11, 1, 1, 4)
        self.checkBoxUncheckedDis = QtGui.QCheckBox(self.dockWidgetContents)
        self.checkBoxUncheckedDis.setEnabled(False)
        self.checkBoxUncheckedDis.setMinimumSize(QtCore.QSize(0, 0))
        self.checkBoxUncheckedDis.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.checkBoxUncheckedDis.setChecked(False)
        self.checkBoxUncheckedDis.setObjectName("checkBoxUncheckedDis")
        self.gridLayout.addWidget(self.checkBoxUncheckedDis, 11, 7, 1, 4)
        self.label = QtGui.QLabel(self.dockWidgetContents)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 12, 0, 1, 1)
        self.checkBoxTristate = QtGui.QCheckBox(self.dockWidgetContents)
        self.checkBoxTristate.setChecked(False)
        self.checkBoxTristate.setTristate(True)
        self.checkBoxTristate.setObjectName("checkBoxTristate")
        self.gridLayout.addWidget(self.checkBoxTristate, 12, 1, 1, 3)
        self.checkBoxTristateDis = QtGui.QCheckBox(self.dockWidgetContents)
        self.checkBoxTristateDis.setEnabled(False)
        self.checkBoxTristateDis.setChecked(False)
        self.checkBoxTristateDis.setTristate(True)
        self.checkBoxTristateDis.setObjectName("checkBoxTristateDis")
        self.gridLayout.addWidget(self.checkBoxTristateDis, 12, 7, 1, 3)
        self.label_31 = QtGui.QLabel(self.dockWidgetContents)
        self.label_31.setMinimumSize(QtCore.QSize(0, 0))
        self.label_31.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_31.setFont(font)
        self.label_31.setObjectName("label_31")
        self.gridLayout.addWidget(self.label_31, 13, 0, 1, 1)
        self.commandLinkButton = QtGui.QCommandLinkButton(self.dockWidgetContents)
        self.commandLinkButton.setMinimumSize(QtCore.QSize(0, 0))
        self.commandLinkButton.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.commandLinkButton.setObjectName("commandLinkButton")
        self.gridLayout.addWidget(self.commandLinkButton, 13, 1, 1, 6)
        self.commandLinkButtonDIs = QtGui.QCommandLinkButton(self.dockWidgetContents)
        self.commandLinkButtonDIs.setEnabled(False)
        self.commandLinkButtonDIs.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.commandLinkButtonDIs.setObjectName("commandLinkButtonDIs")
        self.gridLayout.addWidget(self.commandLinkButtonDIs, 13, 7, 1, 6)
        self.label_32 = QtGui.QLabel(self.dockWidgetContents)
        self.label_32.setMinimumSize(QtCore.QSize(0, 0))
        self.label_32.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_32.setFont(font)
        self.label_32.setObjectName("label_32")
        self.gridLayout.addWidget(self.label_32, 14, 0, 1, 1)
        self.buttonBox = QtGui.QDialogButtonBox(self.dockWidgetContents)
        self.buttonBox.setMinimumSize(QtCore.QSize(0, 0))
        self.buttonBox.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.buttonBox.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.gridLayout.addWidget(self.buttonBox, 14, 1, 1, 6)
        self.buttonBoxDis = QtGui.QDialogButtonBox(self.dockWidgetContents)
        self.buttonBoxDis.setEnabled(False)
        self.buttonBoxDis.setStandardButtons(QtGui.QDialogButtonBox.Cancel|QtGui.QDialogButtonBox.Ok)
        self.buttonBoxDis.setObjectName("buttonBoxDis")
        self.gridLayout.addWidget(self.buttonBoxDis, 14, 7, 1, 6)
        spacerItem = QtGui.QSpacerItem(20, 4, QtGui.QSizePolicy.Minimum, QtGui.QSizePolicy.Expanding)
        self.gridLayout.addItem(spacerItem, 15, 0, 1, 1)
        self.label_36 = QtGui.QLabel(self.dockWidgetContents)
        self.label_36.setAlignment(QtCore.Qt.AlignCenter)
        self.label_36.setObjectName("label_36")
        self.gridLayout.addWidget(self.label_36, 16, 0, 1, 1)
        self.label_76 = QtGui.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_76.setFont(font)
        self.label_76.setObjectName("label_76")
        self.gridLayout.addWidget(self.label_76, 3, 0, 1, 1)
        self.label_33 = QtGui.QLabel(self.dockWidgetContents)
        self.label_33.setMinimumSize(QtCore.QSize(0, 0))
        self.label_33.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_33.setFont(font)
        self.label_33.setObjectName("label_33")
        self.gridLayout.addWidget(self.label_33, 4, 0, 1, 1)
        self.toolButton = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButton.setMinimumSize(QtCore.QSize(0, 0))
        self.toolButton.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.toolButton.setObjectName("toolButton")
        self.gridLayout.addWidget(self.toolButton, 4, 1, 1, 2)
        self.toolButtonDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonDis.setEnabled(False)
        self.toolButtonDis.setMinimumSize(QtCore.QSize(0, 0))
        self.toolButtonDis.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.toolButtonDis.setObjectName("toolButtonDis")
        self.gridLayout.addWidget(self.toolButtonDis, 4, 7, 1, 2)
        self.label_75 = QtGui.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_75.setFont(font)
        self.label_75.setObjectName("label_75")
        self.gridLayout.addWidget(self.label_75, 8, 0, 1, 1)
        self.pushButton = QtGui.QPushButton(self.dockWidgetContents)
        self.pushButton.setMinimumSize(QtCore.QSize(0, 0))
        self.pushButton.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.pushButton.setObjectName("pushButton")
        self.gridLayout.addWidget(self.pushButton, 1, 1, 1, 6)
        self.pushButtonDis = QtGui.QPushButton(self.dockWidgetContents)
        self.pushButtonDis.setEnabled(False)
        self.pushButtonDis.setMinimumSize(QtCore.QSize(0, 0))
        self.pushButtonDis.setMaximumSize(QtCore.QSize(16777215, 16777215))
        self.pushButtonDis.setDefault(False)
        self.pushButtonDis.setObjectName("pushButtonDis")
        self.gridLayout.addWidget(self.pushButtonDis, 1, 7, 1, 6)
        self.label_73 = QtGui.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_73.setFont(font)
        self.label_73.setObjectName("label_73")
        self.gridLayout.addWidget(self.label_73, 0, 7, 1, 3)
        self.pushButtonCheckedDis = QtGui.QPushButton(self.dockWidgetContents)
        self.pushButtonCheckedDis.setEnabled(False)
        self.pushButtonCheckedDis.setCheckable(True)
        self.pushButtonCheckedDis.setChecked(True)
        self.pushButtonCheckedDis.setObjectName("pushButtonCheckedDis")
        self.gridLayout.addWidget(self.pushButtonCheckedDis, 2, 7, 1, 6)
        self.label_26 = QtGui.QLabel(self.dockWidgetContents)
        self.label_26.setMinimumSize(QtCore.QSize(0, 0))
        self.label_26.setMaximumSize(QtCore.QSize(16777215, 16777215))
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_26.setFont(font)
        self.label_26.setObjectName("label_26")
        self.gridLayout.addWidget(self.label_26, 1, 0, 1, 1)
        self.pushButtonUncheckedDis = QtGui.QPushButton(self.dockWidgetContents)
        self.pushButtonUncheckedDis.setEnabled(False)
        self.pushButtonUncheckedDis.setCheckable(True)
        self.pushButtonUncheckedDis.setObjectName("pushButtonUncheckedDis")
        self.gridLayout.addWidget(self.pushButtonUncheckedDis, 3, 7, 1, 6)
        self.toolButtonDots = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonDots.setObjectName("toolButtonDots")
        self.gridLayout.addWidget(self.toolButtonDots, 7, 6, 1, 1)
        self.label_74 = QtGui.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_74.setFont(font)
        self.label_74.setObjectName("label_74")
        self.gridLayout.addWidget(self.label_74, 2, 0, 1, 1)
        self.pushButtonUnchecked = QtGui.QPushButton(self.dockWidgetContents)
        self.pushButtonUnchecked.setCheckable(True)
        self.pushButtonUnchecked.setObjectName("pushButtonUnchecked")
        self.gridLayout.addWidget(self.pushButtonUnchecked, 3, 1, 1, 6)
        self.label_72 = QtGui.QLabel(self.dockWidgetContents)
        font = QtGui.QFont()
        font.setWeight(75)
        font.setBold(True)
        self.label_72.setFont(font)
        self.label_72.setObjectName("label_72")
        self.gridLayout.addWidget(self.label_72, 0, 1, 1, 2)
        self.toolButtonCheckedIcon = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonCheckedIcon.setCheckable(True)
        self.toolButtonCheckedIcon.setChecked(True)
        self.toolButtonCheckedIcon.setObjectName("toolButtonCheckedIcon")
        self.gridLayout.addWidget(self.toolButtonCheckedIcon, 6, 6, 1, 1)
        self.toolButtonIcon = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonIcon.setObjectName("toolButtonIcon")
        self.gridLayout.addWidget(self.toolButtonIcon, 4, 6, 1, 1)
        self.toolButtonDotsDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonDotsDis.setEnabled(False)
        self.toolButtonDotsDis.setObjectName("toolButtonDotsDis")
        self.gridLayout.addWidget(self.toolButtonDotsDis, 7, 12, 1, 1)
        self.toolButtonCheckedIconDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonCheckedIconDis.setEnabled(False)
        self.toolButtonCheckedIconDis.setCheckable(True)
        self.toolButtonCheckedIconDis.setChecked(True)
        self.toolButtonCheckedIconDis.setObjectName("toolButtonCheckedIconDis")
        self.gridLayout.addWidget(self.toolButtonCheckedIconDis, 6, 12, 1, 1)
        self.toolButtonIconDis = QtGui.QToolButton(self.dockWidgetContents)
        self.toolButtonIconDis.setEnabled(False)
        self.toolButtonIconDis.setObjectName("toolButtonIconDis")
        self.gridLayout.addWidget(self.toolButtonIconDis, 4, 12, 1, 1)
        DockWidget.setWidget(self.dockWidgetContents)

        self.retranslateUi(DockWidget)
        QtCore.QObject.connect(self.radioButtonChecked, QtCore.SIGNAL("clicked(bool)"), self.radioButtonCheckedDis.setChecked)
        QtCore.QObject.connect(self.radioButtonUnchecked, QtCore.SIGNAL("clicked(bool)"), self.radioButtonUncheckedDis.setChecked)
        QtCore.QObject.connect(self.checkBoxChecked, QtCore.SIGNAL("clicked(bool)"), self.checkBoxCheckedDis.setChecked)
        QtCore.QObject.connect(self.checkBoxEnabled, QtCore.SIGNAL("clicked(bool)"), self.checkBoxUncheckedDis.setChecked)
        QtCore.QObject.connect(self.checkBoxTristate, QtCore.SIGNAL("clicked(bool)"), self.checkBoxTristateDis.setChecked)
        QtCore.QObject.connect(self.commandLinkButton, QtCore.SIGNAL("clicked(bool)"), self.commandLinkButtonDIs.setChecked)
        QtCore.QObject.connect(self.toolButton, QtCore.SIGNAL("clicked(bool)"), self.toolButtonDis.setChecked)
        QtCore.QObject.connect(self.pushButtonChecked, QtCore.SIGNAL("clicked(bool)"), self.pushButtonCheckedDis.setChecked)
        QtCore.QObject.connect(self.pushButtonUnchecked, QtCore.SIGNAL("clicked(bool)"), self.pushButtonUncheckedDis.setChecked)
        QtCore.QObject.connect(self.pushButton, QtCore.SIGNAL("clicked(bool)"), self.pushButtonDis.click)
        QtCore.QMetaObject.connectSlotsByName(DockWidget)

    def retranslateUi(self, DockWidget):
        DockWidget.setWindowTitle(QtGui.QApplication.translate("DockWidget", "Buttons", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonChecked.setText(QtGui.QApplication.translate("DockWidget", "Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.label_2.setText(QtGui.QApplication.translate("DockWidget", "<html><head/><body><p><span style=\" font-weight:600;\">ToolButton</span></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonChecked.setText(QtGui.QApplication.translate("DockWidget", "Tool Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonCheckedDis.setText(QtGui.QApplication.translate("DockWidget", "Tool Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.label_3.setText(QtGui.QApplication.translate("DockWidget", "<html><head/><body><p><span style=\" font-weight:600;\">ToolButton</span></p></body></html>", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowDown.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowUp.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowRight.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowLeft.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowDownDis.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowUpDis.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowRightDis.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonArrowLeftDis.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonChecked.setText(QtGui.QApplication.translate("DockWidget", "Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonCheckedDis.setText(QtGui.QApplication.translate("DockWidget", "Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.label_29.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_29.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_29.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_29.setText(QtGui.QApplication.translate("DockWidget", "RadioButton", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUnchecked.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUnchecked.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUnchecked.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUnchecked.setText(QtGui.QApplication.translate("DockWidget", "Unchecked", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUncheckedDis.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUncheckedDis.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUncheckedDis.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.radioButtonUncheckedDis.setText(QtGui.QApplication.translate("DockWidget", "Unchecked", None, QtGui.QApplication.UnicodeUTF8))
        self.label_53.setText(QtGui.QApplication.translate("DockWidget", "CheckBox", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxChecked.setText(QtGui.QApplication.translate("DockWidget", "Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxCheckedDis.setText(QtGui.QApplication.translate("DockWidget", "Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.label_30.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_30.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_30.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_30.setText(QtGui.QApplication.translate("DockWidget", "CheckBox", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxEnabled.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxEnabled.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxEnabled.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxEnabled.setText(QtGui.QApplication.translate("DockWidget", "Unchecked", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxUncheckedDis.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxUncheckedDis.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxUncheckedDis.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxUncheckedDis.setText(QtGui.QApplication.translate("DockWidget", "Unchecked", None, QtGui.QApplication.UnicodeUTF8))
        self.label.setText(QtGui.QApplication.translate("DockWidget", "CheckBox", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxTristate.setText(QtGui.QApplication.translate("DockWidget", "Tristate", None, QtGui.QApplication.UnicodeUTF8))
        self.checkBoxTristateDis.setText(QtGui.QApplication.translate("DockWidget", "Tristate", None, QtGui.QApplication.UnicodeUTF8))
        self.label_31.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_31.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_31.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_31.setText(QtGui.QApplication.translate("DockWidget", "CommandLinkButton", None, QtGui.QApplication.UnicodeUTF8))
        self.commandLinkButton.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.commandLinkButton.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.commandLinkButton.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.commandLinkButton.setText(QtGui.QApplication.translate("DockWidget", "Command", None, QtGui.QApplication.UnicodeUTF8))
        self.commandLinkButtonDIs.setText(QtGui.QApplication.translate("DockWidget", "Command", None, QtGui.QApplication.UnicodeUTF8))
        self.label_32.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_32.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_32.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_32.setText(QtGui.QApplication.translate("DockWidget", "ButtonBox", None, QtGui.QApplication.UnicodeUTF8))
        self.buttonBox.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.buttonBox.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.buttonBox.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_36.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_36.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_36.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_36.setText(QtGui.QApplication.translate("DockWidget", "Inside DockWidget", None, QtGui.QApplication.UnicodeUTF8))
        self.label_76.setText(QtGui.QApplication.translate("DockWidget", "PushButton", None, QtGui.QApplication.UnicodeUTF8))
        self.label_33.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_33.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_33.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_33.setText(QtGui.QApplication.translate("DockWidget", "ToolButton", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButton.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButton.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButton.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButton.setText(QtGui.QApplication.translate("DockWidget", "Tool", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonDis.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonDis.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonDis.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonDis.setText(QtGui.QApplication.translate("DockWidget", "Tool", None, QtGui.QApplication.UnicodeUTF8))
        self.label_75.setText(QtGui.QApplication.translate("DockWidget", "RadioButton", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButton.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButton.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButton.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButton.setText(QtGui.QApplication.translate("DockWidget", "OK", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonDis.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonDis.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonDis.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonDis.setText(QtGui.QApplication.translate("DockWidget", "OK", None, QtGui.QApplication.UnicodeUTF8))
        self.label_73.setText(QtGui.QApplication.translate("DockWidget", "Disabled", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonCheckedDis.setText(QtGui.QApplication.translate("DockWidget", "Checked", None, QtGui.QApplication.UnicodeUTF8))
        self.label_26.setToolTip(QtGui.QApplication.translate("DockWidget", "This is a tool tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_26.setStatusTip(QtGui.QApplication.translate("DockWidget", "This is a status tip", None, QtGui.QApplication.UnicodeUTF8))
        self.label_26.setWhatsThis(QtGui.QApplication.translate("DockWidget", "This is \"what is this\"", None, QtGui.QApplication.UnicodeUTF8))
        self.label_26.setText(QtGui.QApplication.translate("DockWidget", "PushButton", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonUncheckedDis.setText(QtGui.QApplication.translate("DockWidget", "Unchecked", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonDots.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.label_74.setText(QtGui.QApplication.translate("DockWidget", "PushButton", None, QtGui.QApplication.UnicodeUTF8))
        self.pushButtonUnchecked.setText(QtGui.QApplication.translate("DockWidget", "Unchecked", None, QtGui.QApplication.UnicodeUTF8))
        self.label_72.setText(QtGui.QApplication.translate("DockWidget", "Enabled", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonCheckedIcon.setText(QtGui.QApplication.translate("DockWidget", "Icon", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonIcon.setText(QtGui.QApplication.translate("DockWidget", "Icon", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonDotsDis.setText(QtGui.QApplication.translate("DockWidget", "...", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonCheckedIconDis.setText(QtGui.QApplication.translate("DockWidget", "Icon", None, QtGui.QApplication.UnicodeUTF8))
        self.toolButtonIconDis.setText(QtGui.QApplication.translate("DockWidget", "Icon", None, QtGui.QApplication.UnicodeUTF8))

