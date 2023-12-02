import os
import datetime

from cs50 import SQL
from werkzeug.security import check_password_hash, generate_password_hash

db = SQL("sqlite:///finance.db")

a = 1
a = -a
print (a)
# user = 'dexter'

# user_db = db.execute('SELECT * FROM stocks WHERE id = ?', user)
# print(user_db)

# if user_db == [1]:
#     print("empty")

# password = 'abcd'

# digit = '1234'

# date = datetime.datetime.now()

# print (date)
# print (float(digit))
# print (int(float(digit)))

# if isinstance(digit, float):
#     print('ok')
# else:
#     print("not ok")

# print(digit)
# print(int(digit))


# hash = generate_password_hash(password)
# print (user_db)

# id = db.execute('select count(*) as n from users')
# id = id[0]['n']
# id += 1
# print (id)

# print (db.execute('select cash from users where id = 1')[0]['cash'])

# if user in user_db[0]['n']:

#     print(user_db)
#     print('false')
#     print(hash)
#     print(check_password_hash(hash, 'password'))