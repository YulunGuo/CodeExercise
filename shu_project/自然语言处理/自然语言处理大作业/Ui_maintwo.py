# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'c:\Users\a'su's\Desktop\自然语言处理\Qt\maintwo.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindowTwo(object):
    def setupUi(self, MainWindowTwo):
        MainWindowTwo.setObjectName("MainWindowTwo")
        MainWindowTwo.resize(1729, 846)
        self.centralwidget = QtWidgets.QWidget(MainWindowTwo)
        self.centralwidget.setObjectName("centralwidget")
        self.verticalLayoutWidget = QtWidgets.QWidget(self.centralwidget)
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(30, 20, 171, 381))
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setContentsMargins(10, 10, 10, 10)
        self.verticalLayout.setObjectName("verticalLayout")
        self.start_train_button = QtWidgets.QPushButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(10)
        self.start_train_button.setFont(font)
        self.start_train_button.setObjectName("start_train_button")
        self.verticalLayout.addWidget(self.start_train_button)
        self.correct_2 = QtWidgets.QPushButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(10)
        self.correct_2.setFont(font)
        self.correct_2.setObjectName("correct_2")
        self.verticalLayout.addWidget(self.correct_2)
        self.check_2 = QtWidgets.QPushButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(10)
        self.check_2.setFont(font)
        self.check_2.setObjectName("check_2")
        self.verticalLayout.addWidget(self.check_2)
        self.back_welcome = QtWidgets.QPushButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setPointSize(10)
        self.back_welcome.setFont(font)
        self.back_welcome.setObjectName("back_welcome")
        self.verticalLayout.addWidget(self.back_welcome)
        self.verticalLayoutWidget_2 = QtWidgets.QWidget(self.centralwidget)
        self.verticalLayoutWidget_2.setGeometry(QtCore.QRect(30, 420, 801, 361))
        self.verticalLayoutWidget_2.setObjectName("verticalLayoutWidget_2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.verticalLayoutWidget_2)
        self.verticalLayout_2.setContentsMargins(8, 8, 8, 8)
        self.verticalLayout_2.setSpacing(14)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.display_train = QtWidgets.QTextEdit(self.verticalLayoutWidget_2)
        self.display_train.setObjectName("display_train")
        self.verticalLayout_2.addWidget(self.display_train)
        self.progressBar = QtWidgets.QProgressBar(self.verticalLayoutWidget_2)
        self.progressBar.setProperty("value", 24)
        self.progressBar.setObjectName("progressBar")
        self.verticalLayout_2.addWidget(self.progressBar)
        self.verticalLayoutWidget_3 = QtWidgets.QWidget(self.centralwidget)
        self.verticalLayoutWidget_3.setGeometry(QtCore.QRect(220, 20, 611, 381))
        self.verticalLayoutWidget_3.setObjectName("verticalLayoutWidget_3")
        self.verticalLayout_3 = QtWidgets.QVBoxLayout(self.verticalLayoutWidget_3)
        self.verticalLayout_3.setContentsMargins(5, 5, 5, 5)
        self.verticalLayout_3.setSpacing(12)
        self.verticalLayout_3.setObjectName("verticalLayout_3")
        self.input_text = QtWidgets.QTextEdit(self.verticalLayoutWidget_3)
        self.input_text.setObjectName("input_text")
        self.verticalLayout_3.addWidget(self.input_text)
        self.label = QtWidgets.QLabel(self.verticalLayoutWidget_3)
        self.label.setText("")
        self.label.setPixmap(QtGui.QPixmap("c:\\Users\\a\'su\'s\\Desktop\\自然语言处理\\Qt\\arrow.png"))
        self.label.setAlignment(QtCore.Qt.AlignCenter)
        self.label.setObjectName("label")
        self.verticalLayout_3.addWidget(self.label)
        self.output_text = QtWidgets.QTextEdit(self.verticalLayoutWidget_3)
        self.output_text.setObjectName("output_text")
        self.verticalLayout_3.addWidget(self.output_text)
        self.graphicsView = QtWidgets.QGraphicsView(self.centralwidget)
        self.graphicsView.setGeometry(QtCore.QRect(850, 25, 861, 751))
        self.graphicsView.setObjectName("graphicsView")
        MainWindowTwo.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindowTwo)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1729, 30))
        self.menubar.setObjectName("menubar")
        self.menu = QtWidgets.QMenu(self.menubar)
        self.menu.setObjectName("menu")
        self.menu_2 = QtWidgets.QMenu(self.menubar)
        self.menu_2.setObjectName("menu_2")
        MainWindowTwo.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindowTwo)
        self.statusbar.setObjectName("statusbar")
        MainWindowTwo.setStatusBar(self.statusbar)
        self.open_file_2 = QtWidgets.QAction(MainWindowTwo)
        self.open_file_2.setObjectName("open_file_2")
        self.save_file_2 = QtWidgets.QAction(MainWindowTwo)
        self.save_file_2.setObjectName("save_file_2")
        self.clear_text_2 = QtWidgets.QAction(MainWindowTwo)
        self.clear_text_2.setObjectName("clear_text_2")
        self.menu.addAction(self.open_file_2)
        self.menu.addAction(self.save_file_2)
        self.menu_2.addAction(self.clear_text_2)
        self.menubar.addAction(self.menu.menuAction())
        self.menubar.addAction(self.menu_2.menuAction())

        self.retranslateUi(MainWindowTwo)
        QtCore.QMetaObject.connectSlotsByName(MainWindowTwo)

    def retranslateUi(self, MainWindowTwo):
        _translate = QtCore.QCoreApplication.translate
        MainWindowTwo.setWindowTitle(_translate("MainWindowTwo", "Seq2Seq"))
        self.start_train_button.setText(_translate("MainWindowTwo", "开始训练"))
        self.correct_2.setText(_translate("MainWindowTwo", "纠错"))
        self.check_2.setText(_translate("MainWindowTwo", "检查文本"))
        self.back_welcome.setText(_translate("MainWindowTwo", "返回主页面"))
        self.menu.setTitle(_translate("MainWindowTwo", "文件"))
        self.menu_2.setTitle(_translate("MainWindowTwo", "编辑"))
        self.open_file_2.setText(_translate("MainWindowTwo", "打开"))
        self.save_file_2.setText(_translate("MainWindowTwo", "保存"))
        self.clear_text_2.setText(_translate("MainWindowTwo", "清空"))
