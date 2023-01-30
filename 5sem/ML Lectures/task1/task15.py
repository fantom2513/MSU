def hello(s=None):
    if(s!=None and s!=' '):
        str="Hello, "+s+"!"
        return str
    else:
        return "Hello!"

def int_to_roman(x):
    res = ''
    for arabic, roman in zip((1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1),
                             'M CM D CD C XC L XL X IX V IV I'.split()):
        res += x // arabic * roman
        x %= arabic
    return res

def longest_common_prefix(x):
  strs=x

  rel = ""
  if len(strs)==0:
      return ""
  for i in range(len(strs)):
    strs[i]=" ".join(strs[i].split())
  for i in range(len(strs[0])):
      for j in strs:
          if len(j)>i:
              if strs[0][i] == j[i]:
                  continue
              else:
                  return rel
          else:
              return rel
      rel = rel+strs[0][i]
  return rel

def is_prime(n):
    if (n <= 1):
        return False
    if (n == 2):
        return True
    if (n % 2 == 0):
        return False

    i = 3
    while i*i <= n:
        if n % i == 0:
            return False
        i = i + 2

    return True
def primes():
    n = 1
    while True:
        n += 1
        if is_prime(n):
            yield n
