s = input("Enter the string: ")
n = len(s)

res = set()

for i in range(n):
    for j in range(1, min(i+1, n-i)):
        if s[i-j] == s[i+j] and s[i] != s[i-j]:
            res.add(s[i] + s[i-j:i+j+1])

print(len(res))
