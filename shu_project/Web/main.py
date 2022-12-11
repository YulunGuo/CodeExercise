from WEB import creat_app,db
from flask_script import Manager
from flask_migrate import Migrate,MigrateCommand

from flask_socketio import SocketIO
import eventlet


app = creat_app()

# 使用Websocket方式，将客户端与服务端建立全双工通信
# 客户端使用socket.io.js,服务端使用flask-socketio扩展
# eventlet是服务器
socketio = SocketIO(app,async_mode='eventlet')

# 将钩子引入内存
from WEB.request_hook import *

manager = Manager(app=app)
# 数据库迁移
migrate = Migrate(app,db)
manager.add_command('db',MigrateCommand)

if __name__ == '__main__':
    # manager.run()
    socketio.run(app,host='0.0.0.0')
