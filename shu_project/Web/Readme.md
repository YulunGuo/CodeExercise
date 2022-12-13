### 总体设计思路
#### 1.客户端
![客户端](https://img-blog.csdnimg.cn/20210621150115231.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzNTgxMTg4,size_16,color_FFFFFF,t_70)
#### 2.服务端
![服务端](https://img-blog.csdnimg.cn/20210621150127550.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzUzNTgxMTg4,size_16,color_FFFFFF,t_70)
#### 3.使用方法  
启动服务器：`python main.py runserver`  

**当创建并连接新的数据库时，需要进行数据库的初始化（仅开始时需要）：**  

数据库初始化: `python main.py db init`  

**此后对于数据库进行修改后，执行以下操作即可：**  

数据库迁移：`python main.py db migrate`  

数据库更新：`python main.py db upgrade`  

**如果出现更新失败的情况，使用如下命令查看版本：**  

```
python main.py db heads
python mian.py db current
```  

如果两者结果不一致，更新head即可，使用如下命令：    

`python main.py db stamp heads`  

#### 4.版本管理
见requirements.txt文件，使用如下命令安装此项目所需依赖项：  

`pip install -r ./requirements.txt`
