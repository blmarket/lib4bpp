#!/usr/bin/python
# vim: fileencoding=cp949
# 이 프로그램은 우리은행 계좌거래내역을 분석하여
# 매 달의 수입/지출을 보여주는 프로그램입니다.
# 개인적으로 내가 한달에 120만원씩이나 쓸 수 있다는 
# 게 참으로 놀라웠습니다.
# 개인적인 투자 목적으로 쓴 돈은 알아서 빼도록 처리할 수 있습니다.
# exclude 함수에 적절한 공식을 추가해주면 됩니다.
# 입력 데이터는 xls를 손으로... 합쳐 다음과 같은 csv 형식으로
# 만들어주면 됩니다. 숫자들은 3자리마다 comma가 찍히지 않게 해주세요.
# 예제)
# 거래일자,적요,기재내용,찾으신금액,맡기신금액,거래후잔액,취급점,메모
# 2009-12-31,체크카드,（주）커피빈코리,9800,0,336422,서울디지,
# 2009-12-31,체크카드,에스알에스ＫＦＣ,3000,0,346222,서울디지,
# 2009-12-29,인터넷,국민김안규,50000,0,349222,독립문지,
# 2009-12-29,체크카드,Ｔ－ｍｏｎｅｙ택,7100,0,399222,서울디지,

import csv
import sys
from datetime import datetime
import re

income = {}
expense = {}
smallexpense = {}

def exclude(row):
    if row[2] == '사이버자금이체':
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
