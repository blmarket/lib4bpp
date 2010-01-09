#!/usr/bin/python
# vim: fileencoding=utf-8
from datetime import datetime
import csv
import sys
import locale

if len(sys.argv) < 2:
    print "Usage : aa.py infile"
    sys.exit(-1)

infile = sys.argv[1]

locale.setlocale(locale.LC_ALL, '')

csv_reader = csv.reader(open(infile,'r'), delimiter=',', quotechar='"')

for row in csv_reader:
    if len(row)>0:
        date = row[0]
        category = row[1]
        name = row[2]
        outmoney = row[3]
        inmoney = row[4]
        curacct = row[5]
        note = row[6]
        memo = row[7]

        date = datetime.strptime(date, '%Y-%m-%d').strftime('%d/%m/%Y')
        inmoney = locale.atoi(inmoney)
        outmoney = locale.atoi(outmoney)
        print date + ";0;" + category + ";" + name + ";" + memo + ";" + str(inmoney - outmoney) + ";"

