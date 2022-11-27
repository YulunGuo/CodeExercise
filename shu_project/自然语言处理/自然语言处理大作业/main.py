import sys
from PyQt5.QtWidgets import QApplication, QMainWindow,QFileDialog,QGraphicsScene
from qt_material import apply_stylesheet
import Ui_main
import json
from PyQt5.QtGui import QPixmap
import Ui_welcome
from PyQt5 import QtCore
import Ui_maintwo
from CorrectWord import *
import collections
from PyQt5.QtGui import QTextDocument,QTextCursor,QTextCharFormat,QColor,QIcon
from CnnPredict import *
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg
from matplotlib.figure import Figure


# 重写一个matplotlib图像绘制类
class MyFigure(FigureCanvasQTAgg):
   def __init__(self,width=5,height=4,dpi = 100):
      # 1、创建一个绘制窗口Figure对象
      self.fig = Figure(figsize=(width,height),dpi=dpi)
      # 2、在父类中激活Figure窗口,同时继承父类属性
      super(MyFigure, self).__init__(self.fig)
 
   # 这里就是绘制图像、示例
   def plotSin(self,x,y):
      self.axes0 = self.fig.add_subplot(111)
      self.axes0.plot(x,y)


# 欢迎界面
class MyWelcome(QMainWindow,Ui_welcome.Ui_WelcomeWindow):
    def __init__(self, parent=None) :
        super(MyWelcome,self).__init__(parent=None)
        self.setupUi(self)
        # 图标
        self.setWindowIcon(QIcon('icon.ico'))



# 传统方法界面
class MyMainWindow(QMainWindow,Ui_main.Ui_MainWindow):
    def __init__(self, parent=None):
        super(MyMainWindow, self).__init__(parent)
        self.setupUi(self)
        self.setWindowIcon(QIcon('icon.ico'))
        # 打开文件夹关联函数
        self.open_file.triggered.connect(self.OpenFile)
        # 保存输出文本框中的内容
        self.save_file.triggered.connect(self.SaveFile)
        # 清空文本框
        self.clear_all.triggered.connect(self.ClearAll)
        # 标签箭头
        self.pic_label.setPixmap(QPixmap('arrow.png'))
        # main界面：将输入文本框中内容纠错后显示在输出文本框中(纠错按钮)
        self.correct.clicked.connect(self.Correct_1)
        # main界面：检查文本功能
        self.check.clicked.connect(self.Check_1)

    # 菜单栏打开文件夹
    def OpenFile(self):
        file_name = QFileDialog.getOpenFileName(self, "选取文件夹","./Desktop","All Files (*);;Text Files (*.txt)")[0]
        print(file_name)
        file = open(file_name,'r')
        fileContent = file.read()
        file.close()
        self.input_text.setText(fileContent)

    # 菜单栏保存文本框内容
    def SaveFile(self):
        output_str = self.output_text.toPlainText()
        print(output_str)
        filepath = QFileDialog.getSaveFileName(self, "文件保存", "./Desktop" ,'txt(*.txt)')[0]
        file=open(filepath,'w')
        print(filepath)
        file.write(output_str)
    
    # 菜单栏清空文本框所有内容
    def ClearAll(self):
        self.input_text.setText('')
        self.output_text.setText('')

    # main界面纠错按钮功能
    def Correct_1(self):
        input_text = self.input_text.toPlainText()
        correct_text = correct_text_generic('纠错结果为：{}'.format(input_text))
        print(correct_text)
        self.output_text.setText(correct_text)
    
    # main界面检查文本功能
    def Check_1(self):
        input_text = self.input_text.toPlainText()
        input_words = tokens(input_text) # text中所有单词转为小写形式并匹配
        print(input_words)
        # 统计语料库中每个单词的个数
        input_word_counts = collections.Counter(input_words)
        print(input_word_counts)
        possible_words = [] # 可能有错的单词
        correct_words = [] # 修改结果
        for word in input_words:
            correct_word = correct(word)
            if correct_word != word:
                possible_words.append(word)
                correct_words.append(correct_word)
                # 错误单词在输入文本框中高亮显示
                document=self.input_text.document()
                highlight_cursor=QTextCursor(document)
                cursor=QTextCursor(document)
                cursor.beginEditBlock()
 
                color_format=QTextCharFormat(highlight_cursor.charFormat())
                color_format.setBackground(QColor(255,211,6))
 
                while (not highlight_cursor.isNull()) and (not highlight_cursor.atEnd()):
 
                    highlight_cursor = document.find(word, highlight_cursor)
                    if not highlight_cursor.isNull():
                        highlight_cursor.mergeCharFormat(color_format)
                cursor.endEditBlock()

        self.output_text.setText('分词结果：{} \n可能有错的单词: {} \n修改结果: {}'.format(input_words,possible_words,correct_words))

# 神经网络界面
class MyMainTwoWindow(QMainWindow,Ui_maintwo.Ui_MainWindowTwo):
    def __init__(self, parent=None) :
        super(MyMainTwoWindow,self).__init__(parent=None)
        self.setupUi(self)
        self.setWindowIcon(QIcon('icon.ico'))
        # 打开文件夹关联函数
        self.open_file_2.triggered.connect(self.OpenFile_2)
        # 保存输出文本框中的内容
        self.save_file_2.triggered.connect(self.SaveFile_2)
        # 清空文本框
        self.clear_text_2.triggered.connect(self.ClearAll_2)
        # 开始训练按钮
        self.start_train_button.clicked.connect(self.start_train)
        # 纠错按钮
        self.correct_2.clicked.connect(self.Correct_2)
        # 检查文本按钮
        self.check_2.clicked.connect(self.Check_2)

    # 菜单栏打开文件夹
    def OpenFile_2(self):
        file_name = QFileDialog.getOpenFileName(self, "选取文件夹","./Desktop","All Files (*);;Text Files (*.txt)")[0]
        print(file_name)
        file = open(file_name,'r')
        fileContent = file.read()
        file.close()
        self.input_text.setText(fileContent)

    # 菜单栏保存文本框内容
    def SaveFile_2(self):
        output_str = self.output_text.toPlainText()
        print(output_str)
        filepath = QFileDialog.getSaveFileName(self, "文件保存", "./Desktop" ,'txt(*.txt)')[0]
        file=open(filepath,'w')
        print(filepath)
        file.write(output_str)
    
    # 菜单栏清空文本框所有内容
    def ClearAll_2(self):
        self.input_text.setText('')
        self.output_text.setText('')

    # 开始训练按钮绑定函数,并使进度条发生变化
    def start_train(self):
        start = time.time()
        n_iters = 200
        best_score = -1
        print_interval = 10
        all_training_loss, all_testing_score= [], []

        total_data = dataloader(x_train, y_train)
        training_pairs = [random.choice(total_data) for i in range(n_iters)]

        encoder_optimizer, decoder_optimizer = Optimizers(encoder1, decoder1, lr)
        encoder_optz_scheduler, decoder_optz_scheduler = Scheduler(encoder_optimizer, decoder_optimizer)

        criterion = nn.CrossEntropyLoss()

        for iter in tqdm(range(1, n_iters + 1)):
            encoder1.train()
            decoder1.train()

            training_pair = training_pairs[iter - 1]
            input_tensor = training_pair[0]
            target_tensor = training_pair[1]

            inputs, labels = embedding(input_tensor, target_tensor, alp_convert)
            inputs, labels = Variable(inputs.to(device)).long(), Variable(labels.to(device)).long()

            loss, word, score = train(inputs, labels, target_tensor, encoder1, decoder1, 
							encoder_optimizer, decoder_optimizer, encoder_optz_scheduler, 
							decoder_optz_scheduler, criterion)
            all_training_loss.append(loss)
		
            # evaluation every certain times using the testing set
            if iter % print_interval == 0:
                encoder1.eval()
                decoder1.eval()

                testing_score = 0.0
                testing_loss = 0.0

                # make prediction using testiing
                for i, (x, y) in enumerate(zip(x_test, y_test)):
                    inputs, labels = embedding(x, y, alp_convert)
                    inputs, labels = Variable(inputs.to(device)).long(), Variable(labels.to(device)).long()

                    loss, word, score = evaluate(inputs, labels, y, encoder1, decoder1, criterion)  
                    print('True word: %-20s || Predicted word: %-20s' %(y, word)) # print result
                    testing_score += score
                    testing_loss += loss
			
                testing_score = round(testing_score / len_test, 4)
                testing_loss = round(testing_loss / len_test, 4)

                # print testing lost and blue4 score
                print("\n>> testing's loss: %.4f \n>> bleu-4 score: %.4f \n" %(testing_loss, testing_score))

                all_testing_score.append(testing_score)
			    # update the best weights
                if testing_score > best_score:
                    best_encoder_weights = copy.deepcopy(encoder1.state_dict())
                    best_decoder_weights = copy.deepcopy(decoder1.state_dict())
                    best_score = testing_score
                print('iter:{} ; bleu-4 score:{}'.format(iter,testing_score))
                # 训练进度显示
                self.display_train.moveCursor(QTextCursor.End)
                self.display_train.append('iter: {} ; bleu-4 score: {}'.format(iter,testing_score))
            # 进度条开始
            self.progressBar.setValue(iter)
        
        # 绘制函数图像
        F1 = MyFigure(width=5, height=4, dpi=100)
        # 开始绘制
        score = np.load('weights/training_loss.npy')
        loss = np.load('weights/testing_bleu4.npy')
        # 图1
        F1.axes1 = F1.fig.add_subplot(211)
        F1.axes1.plot(loss)
        F1.axes1.set_xlabel('Number of iterations', fontsize=13)
        F1.axes1.set_ylabel('BLUE-4 score', fontsize=13)
        # 图2
        F1.axes2 = F1.fig.add_subplot(212)
        F1.axes2.plot(score)
        F1.axes2.set_xlabel('Number of iterations', fontsize=13)
        F1.axes2.set_ylabel('Training loss', fontsize=13)
        # 调整绘图
        width,height = self.graphicsView.width(),self.graphicsView.height()
        F1.resize(width,height)
        self.scene = QGraphicsScene()  # 创建一个场景
        self.scene.addWidget(F1)  # 将图形元素添加到场景中
        self.graphicsView.setScene(self.scene)  # 将创建添加到图形视图显示窗口
    
    # 纠错按钮
    def Correct_2(self):
        predict_str = ''
        input_text = self.input_text.toPlainText()
        input_words =  tokens(input_text) # 分词结果
        print(input_words)
        # 将分词结果输入模型中进行预测
        y_inputs = tokens(correct_text_generic(input_text))
        predict_words = predict(input_words,y_inputs,encoder1,decoder1)
        print(predict_words)
        for word in predict_words:
            predict_str = predict_str + word
            predict_str += ' '
        self.output_text.setText(predict_str)
    
    # 检查文本按钮
    def Check_2(self):
        input_text = self.input_text.toPlainText()
        input_words = tokens(input_text)
        print(input_words)
        # 将分词结果输入模型中进行预测
        y_inputs = tokens(correct_text_generic(input_text))
        print('****************************************')
        print(y_inputs)
        predict_words = predict(input_words,y_inputs,encoder1,decoder1) # 预测的单词
        possible_words = [] # 错误的单词
        print(predict_words)
        for word_index in range(0,len(input_words)):
            if input_words[word_index] != predict_words[word_index]:
                possible_words.append(input_words[word_index])
                # 错误单词在输入文本框中高亮显示
                document=self.input_text.document()
                highlight_cursor=QTextCursor(document)
                cursor=QTextCursor(document)
                cursor.beginEditBlock()
 
                color_format=QTextCharFormat(highlight_cursor.charFormat())
                color_format.setBackground(QColor(255,211,6))
 
                while (not highlight_cursor.isNull()) and (not highlight_cursor.atEnd()):
 
                    highlight_cursor = document.find(input_words[word_index], highlight_cursor)
                    if not highlight_cursor.isNull():
                        highlight_cursor.mergeCharFormat(color_format)
                cursor.endEditBlock()
        self.output_text.setText('分词结果：{} \n可能有错的单词: {} \n修改结果: {}'.format(input_words,possible_words,predict_words))


extra = {
    'font_size': '0.0',
}

if __name__ == '__main__':
    # QtCore.QCoreApplication.setAttribute(QtCore.Qt.AA_EnableHighDpiScaling)
    app = QApplication(sys.argv)
    apply_stylesheet(app,theme='dark_teal.xml',invert_secondary=True,extra=extra)  
    welcome = MyWelcome()
    welcome.show()
    mainwindow = MyMainWindow()
    maintwowindow = MyMainTwoWindow()
    welcome.traditonal_button.clicked.connect(
        lambda:{welcome.close(),mainwindow.show()}
    )
    welcome.cnn_button.clicked.connect(
        lambda:{welcome.close(),maintwowindow.show()}
    )
    mainwindow.back_welcome.clicked.connect(
        lambda:{mainwindow.close(),welcome.show()}
    )
    maintwowindow.back_welcome.clicked.connect(
        lambda:{maintwowindow.close(),welcome.show()}
    )
    sys.exit(app.exec_())
