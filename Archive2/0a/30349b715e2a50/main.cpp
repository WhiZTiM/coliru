#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

double kThreshold = 0.1;
int kIterations = 10;


template <typename T>
const T& getRandomElement(const std::vector<T>& vec)
{
    std::size_t pos = std::rand() % vec.size();
    return vec.at(pos);
}

template <typename T>
T& getRandomElement(std::vector<T>& vec)
{
    std::size_t pos = std::rand() % vec.size();
    return vec.at(pos);
}


template <typename T>
struct Point3D
{
    T x, y, z;
    
    Point3D() : x(0), y(0), z(0)
    {
    }
    
    template <typename U>
    Point3D(U x, U y, U z) : x(x), y(y), z(z)
    {
    }
    
    template <typename U>
    Point3D(const Point3D<U>& rhs) : x(rhs.x), y(rhs.y), z(rhs.z)
    {
    }
    
    Point3D<T> operator+=(const Point3D<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    
    template <typename U>
    Point3D<T> operator/=(U divisor)
    {
        x /= divisor;
        y /= divisor;
        z /= divisor;
        return *this;
    }
    
    
};

using Pixel = Point3D<unsigned>;
using Cluster = Point3D<double>;


template <typename T, typename U>
double distance(const Point3D<T>& p, const Point3D<U>& q)
{
    double x = p.x - q.x;
    double y = p.y - q.y;
    double z = p.z - q.z;
    return std::sqrt(x*x + y*y + z*z);
}


std::vector<Cluster> initClusters(std::size_t numClusters, const std::vector<Pixel>& pixels)
{
    std::vector<Cluster> clusters;
    clusters.reserve(numClusters);
    for (std::size_t i = 0; i < numClusters; ++i)
    {
		clusters.push_back(getRandomElement(pixels));
	}
    return clusters;
}

bool checkClusters(const std::vector<Cluster>& rhs, const std::vector<Cluster>& lhs)
{
    return std::equal(rhs.begin(), rhs.end(), lhs.begin(), [](const Cluster& p, const Cluster& q){
        return std::abs(p.x - q.x) < kThreshold &&
               std::abs(p.y - q.y) < kThreshold &&
               std::abs(p.z - q.z) < kThreshold;
    });
}

std::vector<Cluster>::const_iterator closestCluster(const std::vector<Cluster>& clusters, const Pixel& p)
{
    std::vector<double> distances(clusters.size());
    std::transform(clusters.begin(), clusters.end(), distances.begin(), [&p](const Cluster& c){ return distance(c, p); });
    
    std::vector<double>::const_iterator closestDistanceIt = std::min_element(distances.begin(), distances.end());
    std::size_t closestPos = std::distance(distances.cbegin(), closestDistanceIt);
    
    std::vector<Cluster>::const_iterator closestClusterIt = clusters.cbegin();
    std::advance(closestClusterIt, closestPos);
    
    return closestClusterIt;
}

std::vector<Cluster> updateClusters(const std::vector<Pixel>& pixels, std::vector<Cluster>& clusters)
{
    std::vector<Cluster> newClusters(clusters.size());
    
    std::size_t numClusters = clusters.size();
    std::vector<int> count(numClusters, 0);
    
    for (const Pixel& pixel : pixels)
    {
    	std::size_t closesPos = std::distance(clusters.cbegin(), closestCluster(clusters, pixel));
		newClusters.at(closesPos) += pixel;
		++count.at(closesPos);
	}
    
    for (std::size_t i = 0; i < numClusters; ++i)
    {
        if (count.at(i) != 0)
        {
            newClusters.at(i) /= count.at(i);
        }
        else
        {
            clusters.at(i) = getRandomElement(pixels);
        }
    }
    
    return newClusters;
}

void updatePixels(const std::vector<Cluster>& clusters, std::vector<Pixel>& pixels) {
    for (Pixel& pixel : pixels)
    {
		pixel = *closestCluster(clusters, pixel);
	}
}

void kmeans(std::vector<Pixel>& pixels, std::size_t numClusters) {
    std::vector<Cluster> clustersOld;
	std::vector<Cluster> clustersNew = initClusters(numClusters, pixels);
    
	int iteration = 0;
	do {
        std::swap(clustersOld, clustersNew);
		std::cout << iteration << std::endl;
		clustersNew = updateClusters(pixels, clustersOld);
		++iteration;
	} while(iteration < kIterations /*&& !checkClusters(clustersOld, clustersNew)*/);
	
	updatePixels(clustersNew, pixels);
}

int main()
{
    std::vector<Pixel> pixels = {Pixel{1,1,1}, Pixel{2,2,2}, Pixel{3,3,3}, Pixel{4,4,4}, Pixel{5,5,5}};
    kmeans(pixels, 2);
    std::cout << "!" << std::endl;
    std::cout << pixels.at(0).x << pixels.at(0).y << pixels.at(0).z << pixels.at(1).x << pixels.at(1).y << pixels.at(1).z << std::endl;
}