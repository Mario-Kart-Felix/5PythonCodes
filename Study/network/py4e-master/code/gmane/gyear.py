import sqlite3
import time
import urllib
import zlib

conn = sqlite3.connect('index.sqlite')
conn.text_factory = str
cur = conn.cursor()

# Determine the top ten organizations
cur.execute('''SELECT Messages.id, sender FROM Messages 
    JOIN Senders ON Messages.sender_id = Senders.id''')

sendorgs = dict()
for message_row in cur :
    sender = message_row[1]
    pieces = sender.split("@")
    if len(pieces) != 2 : continue
    dns = pieces[1]
    sendorgs[dns] = sendorgs.get(dns,0) + 1

# pick the top schools
orgs = sorted(sendorgs, key=sendorgs.get, reverse=True)
orgs = orgs[:10]
print "Top 10 Organizations"
print orgs
# orgs = ['total'] + orgs

# Read through the messages
counts = dict()
years = list()

cur.execute('''SELECT Messages.id, sender, sent_at FROM Messages 
    JOIN Senders ON Messages.sender_id = Senders.id''')

for message_row in cur :
    sender = message_row[1]
    pieces = sender.split("@")
    if len(pieces) != 2 : continue
    dns = pieces[1]
    if dns not in orgs : continue
    year = message_row[2][:4]
    if year not in years : years.append(year)
    key = (year, dns)
    counts[key] = counts.get(key,0) + 1
    tkey = (year, 'total')
    counts[tkey] = counts.get(tkey,0) + 1
    
years.sort()
print counts
print years

fhand = open('gline.js','w')
fhand.write("gline = [ ['Year'")
for org in orgs:
    fhand.write(",'"+org+"'")
fhand.write("]")

# for year in years[1:-1]:
for year in years:
    fhand.write(",\n['"+year+"'")
    for org in orgs:
        key = (year, org)
        val = counts.get(key,0)
        fhand.write(","+str(val))
    fhand.write("]");

fhand.write("\n];\n")
fhand.close()

print "Data written to gline.js"
print "Open gline.htm in a browser to view"
