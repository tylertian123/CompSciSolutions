for c in input():print(c,(min((abs(ord(c)-ord(v)),v)for v in'aeiou')[1]+((chr(ord(c)+1)if chr(ord(c)+1)not in'aeiou'else chr(ord(c)+2))if c!='z'else'z'))if c not in('aeiou')else'',sep='',end='')