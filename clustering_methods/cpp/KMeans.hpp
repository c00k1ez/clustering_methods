#ifndef KMEANS_HPP
#define KMEANS_HPP

#include <vector>


namespace clustering 
{

class KMeans 
{

public:
	KMeans(const long &t_num_clusters)
		: m_num_clusters(t_num_clusters)
	{

	}

	void fit(std::vector< std::vector<float> > t_data);

	std::vector<long> predict(std::vector< std::vector<float> > t_data);

	std::vector<long> fit_predict(std::vector< std::vector<float> > t_data);

private:
	long m_num_clusters;

	float euclideanDistance(std::vector<float> t_u, std::vector<float> t_v);

	std::vector< std::vector<float> > getStartClusters(std::vector< std::vector<float> > t_data);

	long getClosestCentroid(std::vector<float> t_data, std::vector< std::vector<float> > centroids);

	float calcMAE(std::vector<float> a, std::vector<float> b);

	std::vector< std::vector<float> > m_centroids;

};

}

#endif