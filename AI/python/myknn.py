#lista de amostras
amostras = []

with open( 'haberman.data', 'r' ) as f:
	for linha in f.readlines():
		atrib = linha.replace('\n', '').split(',')

		atrib_val = []
		for x in range(0,len(atrib)):
			atrib_val.append( int(atrib[x]) )

		# amostras.append( [int(atrib[0]), int(atrib[1]),
		# 	int(atrib[2]), int(atrib[3])] )
		amostras.append(atrib_val)

print( 'Dataset size: %d' % len(amostras) )
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
#print( rotulo1 )
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

print('Treinamento Info')
print(info_dataset(treinamento, verbose=False))
print('Teste Info')
print(info_dataset(teste, verbose=False))

import math

def dist_euclidiana(x1, x2):
	dim, soma = len(x1), 0
	for i in range(dim-1):
		soma += math.pow( x1[i] - x2[i], 2 )
	return math.sqrt(soma)

# Teste de dist_euclidiana
x1 = [1, 2, 3]
x2 = [2, 1, 3]

#print ( dist_euclidiana(x1, x2) )

def myknn(dados, nova_amostra, K):
	dists, tam_dados = {}, len(dados)
	for i in range(tam_dados):
		d = dist_euclidiana( dados[i], nova_amostra )
		dists[i] = d

	k_vizinhos = sorted(dists, key=dists.get)[:K]

	qtd_rotulo1, qtd_rotulo2 = 0, 0

	for indice in k_vizinhos:
		if dados[indice][-1] == 1:
			qtd_rotulo1 += 1
		else:
			qtd_rotulo2 += 1

	if qtd_rotulo2 < qtd_rotulo1 :
		return 1
	else:
		return 2

#print(teste[0])
#print( myknn(treinamento, teste[0], 13) )

acertos, K = 0, 13

error_vector = []

for k in range( 20 ):

	#print( k )

	for amostra in teste:
		classe = myknn(treinamento, amostra, k)
		if amostra[-1] == classe:
			acertos += 1

	#print('Total de treinamento: %d' % len(treinamento))
	#print('Total de teste: %d' % len(teste))
	#print('Total de acertos: %d' % acertos)
	#print('Porcentagem de acertos: %.2f%%' % (100 * acertos / len(teste)))

	error_vector.append( 100 * acertos / len(teste) )

	acertos = 0

print( error_vector )
print( min(error_vector) )
print( max(error_vector) )


import matplotlib.pyplot as plt
import numpy

fig = plt.figure()
ax = fig.gca()
ax.set_xticks(numpy.arange(0, 52, 2))
ax.set_yticks(numpy.arange(0, 150, 10))

plt.plot(error_vector)
plt.ylabel('\% acertos')
plt.xlabel('k')
plt.grid()
plt.show()

