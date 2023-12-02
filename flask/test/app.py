from flask import Flask, render_template, request

app = Flask(__name__)

APPLICANTS = {}

SPORTS = ['basketball' , 'volleyball']

@app.route("/")

def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/greet", methods=["POST"])
def greet():
    name = request.form.get('name')
    sport = request.form.get('sport')
    if sport not in SPORTS:
        return render_template("fail.html")
    if name not in APPLICANTS.keys():
        APPLICANTS[name] = sport
    return render_template("greet.html")

@app.route("/applicants")
def applicants():
    return render_template("applicants.html", applicants=APPLICANTS)
