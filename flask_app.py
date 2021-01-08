from flask import Flask, make_response

app = Flask(__name__)


@app.route("/index/", methods=["GET"])
def index():
    response = make_response("here , take some cookie!")
    response.headers["Set-Cookie"] = "myfirstcookie=somecookievalue"
    return response
