l = ['+','-','*','/','(',')','{','}']
ls = []
lst = []
def expre(s):
    if s.isnumeric()==True:
        ls.append(s)
        return ls,lst
    else:
        for ele in s:
            if ele in l:
                i = s.index(ele)
                ls.append(s[:i])
                lst.append(ele)
                s = s[i+1:]
        return expre(s)
print(expre(1+2/(3+4)))