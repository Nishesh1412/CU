#!/usr/bin/python

print "Content - type: text/html"
print
print "<title>Test CGI</title>"
print "<p> Hello World! </p>"

import MySQLdb
# NEVER EVER STORE PASSWORDS IN A VCDS OR OTHER PUBLIC LOCATION
db = MySQLdb.connect (host="localhost", user="Nish", passwd="test", db="Lab5") #name of the access
#you must create a Cursor object.
#execute all queries
cur = db.cursor()

#user all the SQL you like
cur.execute("Select qty, price FROM store")
# print stuff
print "<table border=1>"
for row in cur.fetchall() :
	#print row[0]
	#print row[1]
	print "<tr><td>", row[0], "</td>"
	print "<td>", row[1], "</td></tr>"
print "</table>"

print "DONE"
