#include <stdio.h>
#include <vector>
#include <cassert>
#include <memory>
#include <fstream>

class Feature {
 public:
  virtual void read(std::istream& is) = 0;
  virtual void draw() = 0;

 protected:
  void drawCircle(double centerX, double centerY, double radius){};
  void drawPolygon(std::vector<double> const& points){};

  void read_(std::istream& is, std::size_t nelements) {
    points.resize(nelements);
    is.read(reinterpret_cast<char*>(&points), nelements * sizeof(double));
  }

  std::vector<double> points;
};

class Circle : public Feature {
  static constexpr std::size_t npoints = 3;

 public:
  void read(std::istream& is) override { read_(is, npoints); }

  void draw() override {
    assert(points.size() == npoints);
    drawCircle(points[0], points[1], points[2]);
  }
};

class Triangle : public Feature {
  static constexpr std::size_t npoints = 6;

 public:
  void read(std::istream& is) override { read_(is, npoints); }

  void draw() override {
    assert(points.size() == npoints);
    drawPolygon(points);
  }
};

class Square : public Feature {
  static constexpr std::size_t npoints = 8;

 public:
  void read(std::istream& is) override { read_(is, npoints); }

  void draw() override {
    assert(points.size() == npoints);
    drawPolygon(points);
  }
};

enum class FeatureType { eUnknown, eCircle, eTriangle, eSquare };

std::unique_ptr<Feature> read_feature(std::istream& is) {
  FeatureType type;
  is.read(reinterpret_cast<char*>(&type), sizeof(FeatureType));

  std::unique_ptr<Feature> feature;

  switch (type) {
    case FeatureType::eCircle:
      feature = std::make_unique<Circle>();
      break;
    case FeatureType::eTriangle:
      feature = std::make_unique<Triangle>();
      break;
    case FeatureType::eSquare:
      feature = std::make_unique<Square>();
      break;
    default:
      throw std::runtime_error("Unknown type");
  }
  feature->read(is);
  return feature;
}

int main(int argc, char* argv[]) {
  try {
    std::ifstream file("features.dat", std::fstream::in | std::fstream::binary);
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    auto feature = read_feature(file);
  } catch (...) {
    return 1;
  }
  return 0;
}
