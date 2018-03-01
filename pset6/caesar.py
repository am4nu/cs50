import cs50
import sys

if len(sys.argv) < 2:
    print("no arguments")
    exit(1)

if len(sys.argv) > 2:
    print("error")
    exit(2)

key = int(sys.argv[1])
print("plaintext: ", end="")
str1 = cs50.get_string()
str2 = []
str1 = list(str1)
i = 0
while(i < len(str1)):
    if ord(str1[i]) >= 97 and ord(str1[i]) <= 122:
        tmp = ord(str1[i]) - 97
        tmp = tmp + key
        tmp = tmp % 26
        tmp = tmp + 97
        str1[i] = chr(tmp)

    elif ord(str1[i]) >= 65 and ord(str1[i]) <= 90:
        tmp = ord(str1[i]) - 65
        tmp = tmp + key
        tmp = tmp % 26
        tmp = tmp + 65
        str1[i] = chr(tmp)

    i = i + 1

str1 = ''.join(str1)
print("ciphertext: {}".format(str1))
