from flask import Flask, request, render_template

app = Flask (__name__)

@app.route("/")

def index():
    # if "name" in request.args:
    #     name = request.args["name"]
    # else:
    #     name = "world"

    # name = request.args.get("name", "World!")

    # if "age" in request.args:
    #     age = request.args["age"]
    # else:
    #     age = 0
    return render_template("index.html")

@app.route("/greet")

def greet():
    age = request.args.get("age")
    if age == "":
        age = "not specified"
    return render_template("greet.html", placeholder = request.args.get("name","world"), age = age)