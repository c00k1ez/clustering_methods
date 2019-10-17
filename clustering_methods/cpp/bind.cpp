#include "KMeans.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace clustering;


namespace py = pybind11;

PYBIND11_MODULE(clustering_methods_, m) {
	m.doc() = "k-means example algorithm";

	py::class_<KMeans>(m, "KMeans")
		.def(py::init<const long &>())
		.def("fit", &KMeans::fit)
		.def("predict", &KMeans::predict)
		.def("fit_predict", &KMeans::fit_predict);
}