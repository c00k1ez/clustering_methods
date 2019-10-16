#include "KMeans.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <random>
#include <chrono>  
#include <map>
#include <numeric>
#include <iostream>


namespace clustering 
{

	std::vector<float> &operator+ (std::vector<float> &a, std::vector<float> &b)
	{
		if(a.size() != b.size())
		{
			throw std::runtime_error{"Vectors have different shapes"};
		}

		for(int i = 0; i < a.size(); ++ i) 
			a[i] += b[i];
		return a;
	}

	std::vector<float> &operator- (std::vector<float> &a, std::vector<float> &b)
	{
		if(a.size() != b.size())
		{
			throw std::runtime_error{"Vectors have different shapes"};
		}

		for(int i = 0; i < a.size(); ++ i) 
			a[i] -= b[i];
		return a;
	}

	float KMeans::calcMAE(std::vector<float> a, std::vector<float> b)
	{
		a = a - b;
		for(size_t i = 0; i < a.size(); ++i) a[i] = std::abs(a[i]);
		return std::accumulate(a.begin(), a.end(), 0.0);
	}

	float KMeans::euclideanDistance(std::vector<float> t_u, std::vector<float> t_v)
	{
		float distance = 0.0;

		if(t_u.size() != t_v.size())
		{
			std::cout << t_u.size() << "  " << t_v.size() << std::endl;
			throw std::runtime_error{"Vector dimensions do not the same!"};
		}

		for(size_t i = 0; i < t_u.size(); ++ i)
		{
			distance += (t_u[i] - t_v[i]) * (t_u[i] - t_v[i]);		
		}

		return sqrt(distance);
	}

	std::vector< std::vector<float> > KMeans::getStartClusters(std::vector< std::vector<float> > t_data)
	{
		std::vector< std::vector<float> > centoids(m_num_clusters);
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  		shuffle(t_data.begin(), t_data.end(), std::default_random_engine(seed));
  		for(size_t i = 0; i < m_num_clusters; ++i)
  		{
  			centoids[i] = t_data[i];
  		}
  		return centoids;
	}

	long KMeans::getClosestCentroid(std::vector<float> t_data, 
												 std::vector< std::vector<float> > centroids)
	{
		long min_index = 0;
		float min_distance = euclideanDistance(t_data, centroids[0]);
		for(size_t i = 1; i < centroids.size(); ++ i)
		{
			float distance = euclideanDistance(t_data, centroids[i]);
			if(min_distance > distance)
			{
				min_distance = distance;
				min_index = i;
			}
		}
		return min_index;
	}

	template <typename T>
	void print(std::vector<T> f){for(int i = 0; i < f.size(); i ++) std::cout << f[i] << " "; std::cout << std::endl; }

	void KMeans::fit(std::vector< std::vector<float> > t_data)
	{
		std::vector< std::vector<float> > centroids = getStartClusters(t_data);

		std::vector< std::vector<float> > centroids_new(centroids.size(), std::vector<float>(centroids[0].size()));
		std::vector<long> clusterLengths(centroids.size(), 0);

		float eps = 0.0001;

		while(true)
		{
			for(size_t i = 0; i < t_data.size(); ++i)
			{
				long centroid = getClosestCentroid(t_data[i], centroids);
				clusterLengths[centroid] ++;
				centroids_new[centroid] = centroids_new[centroid] + t_data[i];
			}

			for(size_t i = 0; i < centroids_new.size(); ++ i)
			{
				for(size_t j = 0; j < centroids_new[i].size(); ++ j)
				{
					centroids_new[i][j] = (float)centroids_new[i][j] / clusterLengths[i];
				}
			}

			float max_mae = calcMAE(centroids[0], centroids_new[0]);

			for(size_t i = 1; i < centroids.size(); ++ i)
			{
				float mae = calcMAE(centroids[i], centroids_new[i]);
				if(mae > max_mae) max_mae = mae;
			}

			if(max_mae < eps)
			{
				break;
			} else
			{
				std::vector<long>(clusterLengths.size()).swap(clusterLengths);
				std::copy(centroids_new.begin(), centroids_new.end(), centroids.begin());
			}
		}
		for(size_t i = 0; i < centroids_new.size(); ++i) m_centroids.push_back(centroids_new[i]);
	}

	std::vector<long> KMeans::predict(std::vector< std::vector<float> > t_data)
	{
		std::vector<long> res(t_data.size(), 0);
		for(size_t i = 0; i < t_data.size(); ++ i)
		{
			res[i] = getClosestCentroid(t_data[i], m_centroids);
		}

		return res;
	}

	std::vector<long> KMeans::fit_predict(std::vector< std::vector<float> > t_data)
	{
		fit(t_data);
		return predict(t_data);
	}

}