def check(s, filename):
    strs = s.split()
    d=dict()
    for i in range(len(strs)):
      strs[i]=strs[i].lower()
    for i in strs:
      if i in d.keys():
        d[i]=d[i]+1
      else:
        d[i]=1
    

    d = dict(sorted(d.items()))


    f=open(filename, 'w')
    for i in d.keys():
      a=i+' '
      b=d.get(i,0)
      a=a+str(b)+'\n'
      f.write(a)
    f.close()