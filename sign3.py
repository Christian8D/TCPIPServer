import binascii
x=b'test'
x=binascii.hexlify(x)
x
b'74657374'
y=str(x,'ascii')
y
'74657374'
x=binascii.unhexlify(x)
x
b'test'
y=str(x,'ascii')
y
'test'