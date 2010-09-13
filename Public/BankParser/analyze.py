#!/usr/bin/python
# vim: fileencoding=cp949
# �� ���α׷��� �츮���� ���°ŷ������� �м��Ͽ�
# �� ���� ����/������ �����ִ� ���α׷��Դϴ�.
# ���������� ���� �Ѵ޿� 120�������̳� �� �� �ִٴ� 
# �� ������ �������ϴ�.
# �������� ���� �������� �� ���� �˾Ƽ� ������ ó���� �� �ֽ��ϴ�.
# exclude �Լ��� ������ ������ �߰����ָ� �˴ϴ�.
# �Է� �����ʹ� xls�� ������... ���� ������ ���� csv ��������
# ������ָ� �˴ϴ�. ���ڵ��� 3�ڸ����� comma�� ������ �ʰ� ���ּ���.
# ����)
# �ŷ�����,����,���系��,ã���űݾ�,�ñ�űݾ�,�ŷ����ܾ�,�����,�޸�
# 2009-12-31,üũī��,���֣�Ŀ�Ǻ��ڸ�,9800,0,336422,�������,
# 2009-12-31,üũī��,�����˿����ˣƣ�,3000,0,346222,�������,
# 2009-12-29,���ͳ�,���α�ȱ�,50000,0,349222,��������,
# 2009-12-29,üũī��,�ԣ���������,7100,0,399222,�������,

import csv
import sys
from datetime import datetime
import re

income = {}
expense = {}
smallexpense = {}

def exclude(row):
    if row[2] == '���̹��ڱ���ü':
        return True
    if re.match("^(B-)?Swing", row[1]):
        return True
    if re.match("^(BACK)|(AUTO)SWNG$", row[1]):
        return True
    if re.match("^EFX_", row[2]):
        return True
    if re.match(".*exclude", row[7]):
        return True
    if re.match(".*gibmom", row[7]):
        return True
    if re.match(".*special", row[7]):
        return True
    return False

def processrow(row):
    if(exclude(row)):
        for item in row:
            print item,
        print "Excluded"
        return
    YM = datetime.strptime(row[0],'%Y.%m.%d %H:%M').strftime('%Y-%m')
    if not YM in income:
        income[YM]=0
    if not YM in expense:
        expense[YM]=0
    if not YM in smallexpense:
        smallexpense[YM] = 0

    income[YM] = income[YM] + int(row[4])
    expense[YM] = expense[YM] + int(row[3])
    if int(row[3]) <= 10000:
        smallexpense[YM] = smallexpense[YM] + int(row[3])

if len(sys.argv) >= 2:
    fh = open(sys.argv[1], 'r')
else:
    fh = sys.stdin
	
csv_reader = csv.reader(fh, delimiter=',',quotechar='"')

head = csv_reader.next()

for row in csv_reader:
    processrow(row)

for YM in sorted(income.keys()):
    print YM,income[YM],expense[YM],smallexpense[YM]
