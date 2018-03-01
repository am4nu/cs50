from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    stock=list()
    SeeTransaction=db.execute("SELECT  symbol,price,user,SUM(number) as sumC FROM transactions WHERE user=:uid GROUP BY symbol ",uid=session["user_id"])
    
    print(SeeTransaction)
    if not SeeTransaction:
        stocksbought=0
    else:
        stockbought=1
    if stockbought==1:
        i=0
        totalf=0
        
        for itr in SeeTransaction:
            tempdict={}
            tempdict["name"]=SeeTransaction[i]["symbol"]
            tempdict["symbol"]=SeeTransaction[i]["symbol"]
            datc=lookup(SeeTransaction[i]["symbol"])
            if not datc:
                return apology("sorry not data returned",403)
            print(datc)
            tempdict["price"]=datc["price"]
            tempdict["share"]=SeeTransaction[i]["sumC"]
            tempdict["total"]=tempdict["price"]*tempdict["share"]
            totalf=totalf+tempdict["total"]
            stock.append(tempdict)
            i=i+1
    
    #print (symbol,price,share )
            
    seeCash=db.execute("SELECT * FROM users where id=:uid",uid=session["user_id"])
    cash=seeCash[0]["cash"]
    #print(seeCash)

    totalf=cash+totalf
    
    #print(stock)
    return render_template("index.html",stock=stock,cash=cash,totalf=totalf)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        data= lookup(request.form.get("symbol"))
        number=request.form.get("number")
        if not data:
            return apology("sorry no symbol found",403)
        cashq=db.execute("SELECT * FROM users where id=:uid",uid=session["user_id"])
        
        if not cashq:
            return apology("some error in db",403)
        
        #check if the cash available to user is more thean the cost
        if  (cashq[0]["cash"])<float(number)*data["price"]:
            return apology("Not Enough Cash",403)
        
        updatecash=db.execute("UPDATE users SET cash=:cash WHERE id=:uid",cash=cashq[0]["cash"]-float(number)*data["price"],uid=session["user_id"])
        if not updatecash:
            return apology("sorry update cash failed",403)

        TStatus=db.execute("INSERT INTO transactions (date,symbol,price,user,number) VALUES(datetime('now'),:sym,:prc,:usr,:num)",sym=data["symbol"],prc=data["price"],usr=session["user_id"],num=number)
        if not TStatus:
            #rollback 1st query if 2nd one failed.
            updatecash=db.execute("UPDATE users SET cash=:cash WHERE id=:uid",cash=cashq[0]["cash"]+float(number)*data["price"],uid=session["user_id"])
            return apology("sorry insert failed",403)
            
            
        return redirect("/")
            
            
    else:
        return render_template("buy.html")
    """Buy shares of stock"""
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    if request.method == "POST":

        data= lookup(request.form.get("symbol"));
        if not data:
            return apology("sorry no symbol found",403)
        else:
            return render_template("quoted.html",dat=data)    
    
    else:
        return render_template("quote.html")
    


@app.route("/register", methods=["GET", "POST"])
def register():
    
    """Register user in"""

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
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation of password",403)
        elif request.form.get("password")!=request.form.get("confirmation"):
            return apology("must provide same password and confirmation",403)

        #hash the password before storing
        hashpass=generate_password_hash(request.form.get("password"))
    
        #insert into the db it retrurns the id of the user just inserted
        insertStatus = db.execute("INSERT INTO users (username,hash) VALUES(:usr,:hsh)",usr=request.form.get("username"),hsh=hashpass)
        print(insertStatus)

        # Remember which user has logged by copying into the session variable.
        session["user_id"] = insertStatus


        # Redirect user to regsiter Page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
