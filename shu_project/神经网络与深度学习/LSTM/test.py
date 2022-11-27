from audioop import add
from statistics import mode
from tarfile import FIFOTYPE
import tensorflow as tf




model = tf.keras.models.Sequential()

# 卷积层C1
model.add(tf.keras.layers.Conv2D(filters=6,kernel_size=(5,5),activation=tf.nn.relu,input_shape = (32,32,1)))
# 池化层S2
model.add(tf.keras.layers.MaxPool2D(strides=2))
# 卷积层C3
model.add(tf.keras.layers.Conv2D(filters=16,kernel_size=(5,5),activation=tf.nn.relu))
# 池化层S4
model.add(tf.keras.layers.MaxPool2D(strides=2))
# 卷积层C5
model.add(tf.keras.layers.Conv2D(filters=120,kernel_size=(5,5),activation=tf.nn.relu))
# 
model.add(tf.keras.layers.Flatten())
# 全连接层
model.add(tf.keras.layers.Dense(84,activation=tf.nn.relu))
model.add(tf.keras.layers.Dense(10,activation=tf.nn.softmax))
# 模型
model.summary()
