from flask import Blueprint
from flask import render_template
from flask import request

main_page = Blueprint('main',__name__)

# 主页面
@main_page.route('/')
def main():
    return render_template('main.html')




