import os
import datetime
import re

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Global Variables
# CURRENT_USER_ID = None


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]["cash"]
    data = db.execute("SELECT * FROM stocks WHERE id = ?", session["user_id"])

    for row in data:
        row["price"] = usd(row["price"])
        row["total"] = usd(row["total"])
    return render_template("index.html", cash=usd(cash), stocks=data)
    # return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        if not shares.isdigit():
            return apology("invalid characters")
        shares = float(shares)

        data = lookup(symbol)

        if symbol == "" or data == None:
            return apology("invalid symbol")

        # if int(shares) <= 0 or isinstance(shares, float):
        #     return apology("shares not valid")

        # buy codes
        shares = int(shares)
        price = data["price"]
        session_info = db.execute(
            "SELECT * FROM balance WHERE id = ?", session["user_id"]
        )
        balance = session_info[0]["remaining"]
        purchase_datetime = datetime.datetime.now()
        symbol = symbol
        total = shares * price

        remaining = balance - (shares * price)

        if remaining <= 0:
            return apology("not enough balance to buy stocks")

        check = db.execute(
            "SELECT * FROM stocks WHERE id = ? AND symbol = ?",
            session["user_id"],
            symbol,
        )
        if check == []:
            stockId = db.execute("SELECT COUNT(*) AS n FROM stocks")
            stockId = stockId[0]["n"]
            stockId += 1
            db.execute(
                'INSERT INTO stocks ("id", "stockId", "symbol", "price", "shares", "total") VALUES (?,?,?,?,?,?)',
                session["user_id"],
                stockId,
                symbol,
                price,
                shares,
                total,
            )
        else:
            stockId = db.execute("SELECT stockId FROM stocks WHERE symbol = ?", symbol)
            stockId = stockId[0]["stockId"]
            existingShares = db.execute(
                "SELECT shares FROM stocks WHERE stockId = ?", stockId
            )
            existingShares = existingShares[0]["shares"]
            shares = existingShares + shares
            total = shares * price
            db.execute(
                "UPDATE stocks SET shares = ?, total = ? WHERE stockId = ?",
                shares,
                total,
                stockId,
            )

        # db.execute('INSERT INTO stocks ("id", "stockId", "symbol", "price", "shares", "total") VALUES (?,?,?,?,?)', session["user_id"], stockId, symbol, price, shares, total)
        db.execute(
            "UPDATE balance SET remaining = ? WHERE id = ?",
            remaining,
            session["user_id"],
        )
        db.execute(
            "UPDATE users SET cash = ? WHERE id = ?", remaining, session["user_id"]
        )
        db.execute(
            "INSERT INTO history ('id', 'symbol', 'shares', 'price') VALUES (?,?,?,?)",
            session["user_id"],
            symbol,
            shares,
            price,
        )

        return redirect("/")

    else:
        return render_template("buy.html")
    # return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute("SELECT * FROM history WHERE id = ?", session["user_id"])
    return render_template("history.html", history=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]
        # CURRENT_USER_ID = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # return apology("TODO")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        data = lookup(symbol)
        if data == None:
            return apology("stock does not exist")

        return render_template("quoted.html", userinput = symbol ,symbol = data["name"], value = usd(data["price"]))

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # return apology("NOTALLOWED")
        name = request.form.get('username')
        password = request.form.get('password')
        confirmPassword = request.form.get('confirmation')

        if name == '':
            return apology("name cannot be blank")

        nameDb = db.execute('SELECT username AS n FROM users WHERE username = ?', name)
        id = db.execute('select count(*) as n from users')
        id = id[0]['n']
        # passwordDb = db.execute('SELECT username AS p FROM users WHERE hash = ?', password)

        if len(nameDb) != 0:
            return apology("user already exists")

        if password == '' or confirmPassword == '':
            return apology("password cannot be blank")

        if not password == confirmPassword:
            return apology("password do not match")

        hash = generate_password_hash(password)
        id += 1
        db.execute("INSERT INTO users ('id', 'username', 'hash') VALUES (?,?,?)", id, name, hash)
        balance = db.execute('SELECT cash FROM users WHERE id = ?', id)
        balance = balance[0]['cash']
        db.execute("INSERT INTO balance ('id', 'total', 'remaining') VALUES (?,?,?)", id, balance, balance)

        return redirect("/")

    else:
        return render_template("register.html")
        # return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    data = db.execute('SELECT symbol, stockId, shares, price, total FROM stocks WHERE id = ?', session["user_id"])
    if request.method == "POST":
        symbol = request.form.get("symbol")
        sellingShares = request.form.get("shares")

        if symbol == '':
            return apology("please select a symbol")

        if not sellingShares.isdigit():
            return apology("invalid shares")
        if '-' in sellingShares or '/' in sellingShares:
            return apology("invalid shares")
        sellingShares = int(sellingShares)
        sharesCustomerHave = db.execute('SELECT shares FROM stocks WHERE id = ? AND symbol = ?', session["user_id"], symbol)
        sharesCustomerHave = sharesCustomerHave[0]['shares']
        if sellingShares > sharesCustomerHave:
            return apology("invalid number of shares")

        sharesCustomerHave = sharesCustomerHave - sellingShares
        refund = sellingShares * data[0]['price']
        remaining = db.execute('SELECT * from balance WHERE id = ?', session["user_id"])
        newBalance = refund + remaining[0]['remaining']
        total = sharesCustomerHave * data[0]['price']
        db.execute("INSERT INTO history ('id', 'symbol', 'shares', 'price') VALUES (?,?,?,?)", session['user_id'], symbol, -sellingShares, data[0]['price'])
        db.execute("UPDATE stocks SET shares = ?, total = ? WHERE id = ? AND symbol = ?", sharesCustomerHave, total, session["user_id"], symbol)
        db.execute("UPDATE balance SET remaining = ? WHERE id = ?", newBalance, session["user_id"])
        db.execute("UPDATE users SET cash = ? WHERE id = ?", newBalance, session["user_id"])

        # if sharesCustomerHave == 0:
        #     db.execute("DELETE FROM stocks WHERE id = ? AND symbol = ?", session["user_id"], data[0]['symbol'])
        return redirect("/")
    else:
        return render_template("sell.html", data = data)

    # return apology("TODO")


@app.route("/reset_password", methods = ["GET", "POST"])
@login_required
def reset():
    if request.method == "POST":
        oldPassword = request.form.get("password")
        newPassword = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        if oldPassword == '':
            return apology("type in the old password")
        if newPassword == '':
            return apology("type in the new password")
        if confirmation == '' or newPassword != confirmation:
            return apology("passwords do not match")

        data = db.execute ("SELECT * from users WHERE id = ?", session["user_id"])

        if not check_password_hash(data[0]['hash'], oldPassword):
            return apology("make sure your old password is correct")

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(newPassword), session["user_id"])
        return redirect("/")

    else:
        return render_template("reset_password.html")
