# from cs50 import SQL

# db = SQL("sqlite:///birthdays.db")

# id = db.execute("SELECT COUNT(*) AS n FROM birthdays")
# id_int = id[0]['n']
# id_int += 1

# print(id_int)

import urllib.request, json
with urllib.request.urlopen("http://maps.googleapis.com/maps/api/geocode/json?address=google") as url:
    data = json.load(url)
    print(data)