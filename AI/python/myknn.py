
#lista de amostras
amostras = []

with open( 'haberman.data', 'r' ) as f:
	for linha in f.readlines():
		atrib = linha.replace('\n', '').split(',')

		atrib_val = []
		for x in range(0,len(atrib)):
			atrib_val.append(int(atrib[x]))

		# amostras.append( [int(atrib[0]), int(atrib[1]),
		# 	int(atrib[2]), int(atrib[3])] )
		amostras.append(atrib_val)

print( len(amostras) )
#print( amostras[0:3] )

def info_dataset(amostras, verbose=True):
	if verbose:
		print('Total de amostras: %d' % len(amostras))
	rotulo1, rotulo2 = 0, 0
	for amostra in amostras:
		if amostra[-1] == 1:
			rotulo1 += 1
		else:
			rotulo2 += 1
	if verbose:
		print('Total rotulo 1: %d' % rotulo1)
		print('Total rotulo 2: %d' % rotulo2)
	return [ len(amostras), rotulo1, rotulo2 ]

#print( info_dataset(amostras) )

p = 0.6
_, rotulo1, rotulo2 = info_dataset(amostras, verbose=False)
print( rotulo1 )

treinamento, teste = [], []
for i in range(0,int(rotulo1*p)):
	treinamento.append( amostras[i] )

for i in range(int(rotulo1*p),int((rotulo1+rotulo2)*p,)):
	treinamento.append( amostras[i] )

print( info_dataset(treinamento) )