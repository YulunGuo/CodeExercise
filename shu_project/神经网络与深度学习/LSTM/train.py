from re import S
from statistics import mode
from data import *

# 提取X y
X,y = data_preprocessing(data,time_step,num_letters,char_to_int)

print(X)

print(X.shape) # X.shape = (23308,20,41)
print(len(y)) # 23308


from sklearn.model_selection import  train_test_split
# x_train,shape = (20977,20,41) ; x_test.shape = (2331,20,41) ; X.shape = (23308,20,41)
X_train,X_test,y_train,y_test = train_test_split(X,y,test_size=0.1,random_state=10)
print(X_train.shape,X_test.shape,X.shape)


y_train_category = to_categorical(y_train,num_letters)
print(y_train_category)
print(y)


# 建立LSTM模型
from keras.models import Sequential
from keras.layers import Dense,LSTM
model = Sequential()
# input_shape 看样本的
model.add(LSTM(units=20,input_shape=(X_train.shape[1],X_train.shape[2]),activation="relu"))
#输出层 看样本有多少页
model.add(Dense(units=num_letters ,activation="softmax"))
model.compile(optimizer="adam",loss="categorical_crossentropy",metrics=["accuracy"])
model.summary()
#训练模型
model.fit(X_train,y_train_category,batch_size=1000,epochs=50)
# 保存模型
model_save_path = './model/model_save.h5'
model.save(filepath=model_save_path)


#预测
# y_train_predict = model.predict_classes(X_train)
y_train_predict = np.argmax(model.predict(X_train),axis=1)

#转换成文本
y_train_predict_char = [int_to_char[i] for i in y_train_predict ]
print(y_train_predict_char)


# 训练准确度
from sklearn.metrics import accuracy_score
accuracy = accuracy_score(y_train,y_train_predict)
print(accuracy)




# 测试集准确率
# y_test_predict = model.predict_classes(X_test)
y_test_predict = np.argmax(model.predict(X_test),axis = 1)

accuracy_test = accuracy_score(y_test,y_test_predict)
print(accuracy_test)
y_test_predict_char = [int_to_char[i] for i in y_test_predict ]





# 新文本
# new_letters = 'The United States continues to lead the world with more than '
new_letters = 'The United States continues to lead the world with more than 4 million cases of COVID-19, the disease caused by the virus. Johns Hopkins reports that Brazil is second, with more than 2 million cases, followed by India with more than 1 million.'

X_new,y_new = data_preprocessing(new_letters,time_step,num_letters,char_to_int) # 从第二十个字符开始预测
# y_new_predict = model.predict_classes(X_new)
y_new_predict = np.argmax(model.predict(X_new),axis=1)
print(y_new_predict)


y_new_predict_char = [int_to_char[i] for i in y_new_predict ]
print(y_new_predict_char)


print('输入文本：{}'.format(new_letters[:time_step]))
str = ''
for char in y_new_predict_char:
    str += char
print('预测的文本：{}'.format(new_letters[:time_step]+str))
print('正确的文本：{}'.format(new_letters))

# for i in range(0,X_new.shape[0]-20):
#     print(new_letters[i:i+20],'--predict next letter is --',y_new_predict_char[i])

pass