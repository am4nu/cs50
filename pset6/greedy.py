import cs50
count = 0

print('"O hai! How much change is owed?')

while(True):
    money = cs50.get_float()
    if(money >= 0):
        break

var = round(money * 100)

if var >= 25:
    count += var // 25
    var = var % 25
if var >= 10:
    count += var // 10
    var = var % 10
if var >= 5:
    count += var // 5
    var = var % 5
if var >= 0:
    count = count + var
    var = 0
    print(count)
