import sys

sys.path.append('/lib')

import clustering_methods_

class KMeans:
	def __init__(self, n_clusters=3):
		self.model = clustering_methods_.KMeans(n_clusters)
		self.n_clusters = n_clusters

	def fit(self, data):
		self.model.fit(data)

	def predict(self, data):
		return self.model.predict(data)

	def fit_predict(self, data):
		self.fit(data)
		return self.predict(data)