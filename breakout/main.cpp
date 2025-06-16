#include <string>
#include <vector>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

std::vector<int> EDM_multi(const std::vector<double>& Z, int min_size = 24, double beta = 0, int degree = 0);
std::vector<int> EDM_percent(const std::vector<double>& Z, int min_size = 24, double percent = 0, int degree = 0);
std::vector<int> EDM_tail(std::vector<double>& Z, int min_size = 24, double alpha = 2, double quant = 0.5);
std::vector<int> EDMX(const std::vector<double>& Z, int min_size = 24, double alpha = 2);

PYBIND11_MODULE(breakout, m) {
  m.def("breakout", [](std::vector<double>& z, int min_size, const std::string& method, double alpha, std::optional<double> beta, int degree, std::optional<double> percent, bool exact) {
    if (min_size < 2) {
      throw pybind11::value_error("min_size must be at least 2");
    }

    if (beta && percent) {
      throw pybind11::value_error("beta and percent cannot be passed together");
    }

    if (alpha < 0 || alpha > 2) {
      throw pybind11::value_error("alpha must be between 0 and 2");
    }

    if (degree != 0 && degree != 1 && degree != 2) {
      throw pybind11::value_error("degree must be 0, 1, or 2");
    }

    if (method != "amoc" && method != "multi") {
      throw pybind11::value_error("method must be amoc or multi");
    }

    std::vector<int> res;

    if (z.empty()) {
      return res;
    }

    auto minmax = std::minmax_element(z.begin(), z.end());
    auto min = *minmax.first;
    auto max = *minmax.second;
    auto diff = max - min;
    if (diff == 0) {
      // constant series
      return res;
    }
    for (size_t i = 0; i < z.size(); i++) {
      z[i] = (z[i] - min) / diff;
    }

    if (method == "amoc") {
      if (exact) {
        res = EDMX(z, min_size, alpha);
      } else {
        res = EDM_tail(z, min_size, alpha);
      }
    } else {
      if (percent.has_value()) {
        res = EDM_percent(z, min_size, *percent, degree);
      } else {
        res = EDM_multi(z, min_size, beta.value_or(0.008), degree);
      }
    }

    return res;
  }, py::arg("series"), py::kw_only(), py::arg("min_size") = 30, py::arg("method") = "multi", py::arg("alpha") = 2.0, py::arg("beta") = std::nullopt, py::arg("degree") = 1, py::arg("percent") = std::nullopt, py::arg("exact") = true);
}
