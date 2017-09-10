
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
max_rotulo1 = int(p * rotulo1)
max_rotulo2 = int(p * rotulo2)

num_rotulo1, num_rotulo2 = 0, 0

treinamento, teste = [], []
for amostra in amostras:
	if (num_rotulo1 + num_rotulo2) < (max_rotulo1 + max_rotulo2):
		if amostra[-1] == 1:
			num_rotulo1 += 1
			treinamento.append(amostra)
		else:
			num_rotulo2 += 1
			treinamento.append(amostra)
	else:
		teste.append(amostra)

print( info_dataset(treinamento) )

print( info_dataset(teste) )

import math

def dist_euclidiana(x1, x2):
	dim, soma = len(x1), 0
	for i in range(dim-1):
		soma += math.pow( x1[i] - x2[i]rmrm, 2 )
	return math.sqrt(soma)

x1 = [1, 2, 3]
x2 = [2, 1, 3]


print ( dist_euclidiana(x1, x2) )