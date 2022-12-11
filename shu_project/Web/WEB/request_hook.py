# 在客户端和服务器交互过程中，有些准备工作或者扫尾工作需要处理。比如：
# 1.在请求开始时，建立数据库连接；
# 2.在请求开始时，根据需求进行全年校验。
# 3.在请求你结束时，指定数据的交互格式。

# 为了让每个视图函数避免编写重复功能的代码，Flask提供了通用设置等功能，即请求钩子

from main import app

from flask_wtf.csrf import generate_csrf


# 在每次请求后执行（如果没有抛出错误）；
# 接收一个参数：视图函数做出的相应，在此函数中可以对响应值在返回之前做最后一步修改处理，需要将参数中的相应在此参数中进行返回。
@app.after_request
def after_request(response):
    # 调用函数生成csrf_token
    csrf_token = generate_csrf()
    # 通过cookie将值传给前端
    response.set_cookie("csrf_token",csrf_token)
    return response
